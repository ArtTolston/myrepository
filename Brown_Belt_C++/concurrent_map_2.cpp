#include "B:\test_runner.h"
#include "B:\C++\Red_C++\profile.h"

#include <future>
#include <mutex>
#include <unordered_map>
#include <vector>
#include <utility>
#include <algorithm>
#include <random>
#include <numeric>
using namespace std;
/*
#include <mutex>
#include <unordered_map>
#include <vector>
#include <utility>
using namespace std;

template <typename K, typename V, typename Hash = std::hash<K>>
class ConcurrentMap {
public:
	using MapType = unordered_map<K, V, Hash>;

private:
	struct Bucket {
		MapType data;
		mutable mutex m;
	};

	Hash hasher;
	vector<Bucket> buckets;

public:
	// Выполняем наследование от lock_guard<mutex>, чтобы гарантировать, что мьютекс
	// будет захвачен до модификации bucket'а. Вместо наследования можно было бы
	// просто объявить поле типа lock_guard<mutex>, но такой подход полагается
	// на порядок инициализации полей и не гарантирует, что в будущем он случайно не поменяется
	struct WriteAccess : lock_guard<mutex> {
		V& ref_to_value;

		WriteAccess(const K& key, Bucket& bucket)
			: lock_guard(bucket.m)
			, ref_to_value(bucket.data[key])
		{
		}
	};

	struct ReadAccess : lock_guard<mutex> {
		const V& ref_to_value;

		ReadAccess(const K& key, const Bucket& bucket)
			: lock_guard(bucket.m)
			, ref_to_value(bucket.data.at(key))
		{
		}
	};

	explicit ConcurrentMap(size_t bucket_count)
		: buckets(bucket_count)
	{
	}

	WriteAccess operator[](const K& key) {
		return { key, buckets[GetIndex(key)] };
	}

	ReadAccess At(const K& key) const {
		return { key, buckets[GetIndex(key)] };
	}

	bool Has(const K& key) const {
		auto& bucket = buckets[GetIndex(key)];
		lock_guard g(bucket.m);
		return bucket.data.count(key) > 0;
	}

	MapType BuildOrdinaryMap() const {
		MapType result;
		for (auto& [data, mtx] : buckets) {
			lock_guard g(mtx);
			result.insert(begin(data), end(data));
		}
		return result;
	}

private:
	size_t GetIndex(const K& key) const {
		return hasher(key) % buckets.size();
	}
};
*/


template <typename K, typename V, typename Hash = std::hash<K>>
class ConcurrentMap {
public:
  using MapType = unordered_map<K, V, Hash>;

  struct WriteAccess : lock_guard<mutex> {
    V& ref_to_value;
	WriteAccess(V& ref, mutex& m) : lock_guard(m), ref_to_value(ref) {}
  };

  struct ReadAccess : lock_guard<mutex> {
    const V& ref_to_value;
	ReadAccess(const V& ref, mutex& m) : lock_guard(m), ref_to_value(ref) {}
  };

  explicit ConcurrentMap(size_t bucket_count) : maps(bucket_count), mutexes(bucket_count) {}

  WriteAccess operator[](const K& key) {
	  size_t bucket_number = hasher(key) % maps.size();
	  //cout << "[] bucket_number" << bucket_number << endl;
	  return {maps[bucket_number][key], mutexes[bucket_number]};
  }
  ReadAccess At(const K& key) const {
	  size_t bucket_number = hasher(key) % maps.size();
	  //cout << "At bucket_number" << bucket_number << endl;
	  return { maps.at(bucket_number).at(key) , mutexes[bucket_number] };
  }

    bool Has(const K& key) const {
	  size_t bucket_number = hasher(key) % maps.size();
	  //cout << "Has bucket_number" << bucket_number << endl;
	  return maps.at(bucket_number).find(key) == maps.at(bucket_number).end() ? false : true;
  }

  MapType BuildOrdinaryMap() const {
	  MapType result;
	  for (int i = 0; i < maps.size(); ++i) {
		  lock_guard<mutex> g(mutexes[i]);
		  result.insert(maps[i].begin(), maps[i].end());
	  }
	  return result;
  }

private:
  Hash hasher;
  vector<MapType> maps;
  mutable vector<mutex> mutexes;
};



void RunConcurrentUpdates(
    ConcurrentMap<int, int>& cm, size_t thread_count, int key_count
) {
  auto kernel = [&cm, key_count](int seed) {
    vector<int> updates(key_count);
    iota(begin(updates), end(updates), -key_count / 2);
    shuffle(begin(updates), end(updates), default_random_engine(seed));

    for (int i = 0; i < 2; ++i) {
	  
      for (auto key : updates) {
        cm[key].ref_to_value++;
		//cout << "end\n";
      }
    }
  };

  vector<future<void>> futures;
  for (size_t i = 0; i < thread_count; ++i) {
    futures.push_back(async(kernel, i));
  }
}

void TestConcurrentUpdate() {
  const size_t thread_count = 3;
  const size_t key_count = 500;

  ConcurrentMap<int, int> cm(thread_count);
  RunConcurrentUpdates(cm, thread_count, key_count);
  const auto result = std::as_const(cm).BuildOrdinaryMap();
  ASSERT_EQUAL(result.size(), key_count);
  for (auto& [k, v] : result) {
    AssertEqual(v, 6, "Key = " + to_string(k));
  }
}

void TestReadAndWrite() {
  ConcurrentMap<size_t, string> cm(5);

  auto updater = [&cm] {
    for (size_t i = 0; i < 50; ++i) {
      cm[i].ref_to_value += 'a';
	  //cout << "blyat" << endl;
    }
  };
  auto reader = [&cm] {
    vector<string> result(50);
    for (size_t i = 0; i < result.size(); ++i) {
      result[i] = cm[i].ref_to_value;
    }
    return result;
  };

  auto u1 = async(updater);
  auto r1 = async(reader);
  auto u2 = async(updater);
  auto r2 = async(reader);
  u1.get();
  u2.get();
  for (auto f : {&r1, &r2}) {
    auto result = f->get();
    ASSERT(all_of(result.begin(), result.end(), [](const string& s) {
      return s.empty() || s == "a" || s == "aa";
    }));
  }
}

void TestSpeedup() {
  {
    ConcurrentMap<int, int> single_lock(1);

    LOG_DURATION("Single lock");
    RunConcurrentUpdates(single_lock, 4, 50000);
  }
  {
    ConcurrentMap<int, int> many_locks(4);

    LOG_DURATION("100 locks");
    RunConcurrentUpdates(many_locks, 4, 50000);
  }
}

void TestConstAccess() {
  const unordered_map<int, string> expected = {
    {1, "one"},
    {2, "two"},
    {3, "three"},
    {31, "thirty one"},
    {127, "one hundred and twenty seven"},
    {1598, "fifteen hundred and ninety eight"}
  };

  const ConcurrentMap<int, string> cm = [&expected] {
    ConcurrentMap<int, string> result(3);
    for (const auto& [k, v] : expected) {
      result[k].ref_to_value = v;
    }
    return result;
  }();

  vector<future<string>> futures;
  for (int i = 0; i < 10; ++i) {
    futures.push_back(async([&cm, i] {
      try {
        return cm.At(i).ref_to_value;
      } catch (exception&) {
        return string();
      }
    }));
  }
  futures.clear();

  ASSERT_EQUAL(cm.BuildOrdinaryMap(), expected);
}

void TestStringKeys() {
  const unordered_map<string, string> expected = {
    {"one", "ONE"},
    {"two", "TWO"},
    {"three", "THREE"},
    {"thirty one", "THIRTY ONE"},
  };

  const ConcurrentMap<string, string> cm = [&expected] {
    ConcurrentMap<string, string> result(2);
    for (const auto& [k, v] : expected) {
      result[k].ref_to_value = v;
    }
    return result;
  }();

  ASSERT_EQUAL(cm.BuildOrdinaryMap(), expected);
}

struct Point {
  int x, y;
};

struct PointHash {
  size_t operator()(Point p) const {
    std::hash<int> h;
    return h(p.x) * 3571 + h(p.y);
  }
};

bool operator==(Point lhs, Point rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

void TestUserType() {
  ConcurrentMap<Point, size_t, PointHash> point_weight(5);

  vector<future<void>> futures;
  for (int i = 0; i < 1000; ++i) {
    futures.push_back(async([&point_weight, i] {
      point_weight[Point{i, i}].ref_to_value = i;
    }));
  }

  futures.clear();

  for (int i = 0; i < 1000; ++i) {
    ASSERT_EQUAL(point_weight.At(Point{i, i}).ref_to_value, i);
  }

  const auto weights = point_weight.BuildOrdinaryMap();
  for (int i = 0; i < 1000; ++i) {
    ASSERT_EQUAL(weights.at(Point{i, i}), i);
  }
}

void TestHas() {
  ConcurrentMap<int, int> cm(2);
  cm[1].ref_to_value = 100;
  cm[2].ref_to_value = 200;

  const auto& const_map = std::as_const(cm);
  ASSERT(const_map.Has(1));
  ASSERT(const_map.Has(2));
  ASSERT(!const_map.Has(3));
}

int main() {
	//ConcurrentMap<int, int> cm(5);
	//cm.BuildOrdinaryMap();
	//cm[8].ref_to_value = 10;
	//cout << cm.Has(4) << endl;
	//cout << cm.At(8).ref_to_value;
  TestRunner tr;
  RUN_TEST(tr, TestConcurrentUpdate);
  RUN_TEST(tr, TestReadAndWrite);
  RUN_TEST(tr, TestSpeedup);
  RUN_TEST(tr, TestConstAccess);
  RUN_TEST(tr, TestStringKeys);
  RUN_TEST(tr, TestUserType);
  RUN_TEST(tr, TestHas);
}
