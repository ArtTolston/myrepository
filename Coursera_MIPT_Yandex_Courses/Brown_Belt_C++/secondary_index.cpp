#include "B:\test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Record {
	string id;
	string title;
	string user;
	int timestamp = 0;
	int karma = 0;
};

bool operator==(const Record& lhs, const Record& rhs) {
	return lhs.id == rhs.id && lhs.karma == rhs.karma && lhs.timestamp == rhs.timestamp && lhs.title == rhs.title && lhs.user == rhs.user;
}

// Реализуйте этот класс
class Database {
public:
	bool Put(const Record& record) {
		if (hash_table.find(record.id) == hash_table.end()) {
			Add(record);
			return true;
		}
		return false;
  }
	const Record* GetById(const string& id) const {
		if (hash_table.find(id) != hash_table.end()) {
			return &hash_table.at(id);
		}
		return nullptr;
  }
	bool Erase(const string& id) {
		if (hash_table.find(id) == hash_table.end()) {
			return false;
		}

		Delete(hash_table[id]);
		return true;
  }

  template <typename Callback>
  void RangeByTimestamp(int low, int high, Callback callback) const {
	  auto it = timestamp_table.lower_bound(low);
	  auto it_end = timestamp_table.upper_bound(high);
	  while (it != it_end) {
		  callback((*it).second);
		  ++it;
	  }
  }

  template <typename Callback>
  void RangeByKarma(int low, int high, Callback callback) const {
	  auto it = karma_table.lower_bound(low);
	  auto it_end = karma_table.upper_bound(high);
	  while (it != it_end) {
		  callback((*it).second);
		  ++it;
	  }
  }

  template <typename Callback>
  void AllByUser(const string& user, Callback callback) const {
	  auto range = user_table.equal_range(user);
	  auto it = range.first;
	  while (it != range.second) {
		  cout << (*it).second.user << endl;
		  callback((*it).second);
		  ++it;
	  }
  }

private:
	unordered_map<string, Record, hash<string>> hash_table;
	multimap<int, Record> timestamp_table;
	multimap<int, Record> karma_table;
	multimap<string, Record> user_table;

	void Add(const Record& r) {
		cout << r.id << " " << r.user << " " << r.timestamp << endl;
		hash_table[r.id] = r;
		timestamp_table.insert({r.timestamp, r});
		karma_table.insert(decltype(karma_table)::value_type(r.karma, r));
		user_table.insert({ r.user, r });
	}

	void Delete(const Record& r) {
		hash_table.erase(r.id);
		cout << "here1" << endl;
		{
			auto range = timestamp_table.equal_range(r.timestamp);
			for (auto it = range.first; it != range.second; it++) {
				if (it->second == r) {
					timestamp_table.erase(it);
					break;
				}				
			}
		}
		cout << "here2" << endl;

		
		{
			cout << "here_blyat" << endl;
			auto it = user_table.find(r.user);
			cout << "looool" << endl;
			auto range = user_table.equal_range(r.user);
			cout << "here3.3" << endl;
			for (auto it = range.first; it != range.second; it++) {
				cout << "here3.5" << endl;
				if (it->second == r) {
					cout << "here4" << endl;
					user_table.erase(it);
					break;
				}
			}
		}
		cout << "here3" << endl;
		{
			auto range = karma_table.equal_range(r.karma);
			for (auto it = range.first; it != range.second; it++) {
				if (it->second == r) {
					karma_table.erase(it);
					break;
				}					
			}
		}
	}
};

void TestRangeBoundaries() {
  const int good_karma = 1000;
  const int bad_karma = -10;

  Database db;
  db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
  db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

  int count = 0;
  db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestSameUser() {
  Database db;
  db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
  db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

  int count = 0;
  db.AllByUser("master", [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestReplacement() {
  const string final_body = "Feeling sad";

  Database db;
  db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
  db.Erase("id");
  cout << "After erase" << endl;
  db.Put({"id", final_body, "not-master", 1536107260, -10});

  auto record = db.GetById("id");
  ASSERT(record != nullptr);
  ASSERT_EQUAL(final_body, record->title);
}

int main() {
	Database db;
	db.Put({ "id1", "Hello there", "master", 1536107260, 10 });
	db.Put({ "id1", "Hello", "massa", 1536107260, 10 });
	db.Erase("id1");
  TestRunner tr;
  RUN_TEST(tr, TestRangeBoundaries);
  RUN_TEST(tr, TestSameUser);
  RUN_TEST(tr, TestReplacement);
  return 0;
}
