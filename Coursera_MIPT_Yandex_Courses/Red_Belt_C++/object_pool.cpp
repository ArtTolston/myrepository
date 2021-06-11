#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate() {
    if(pool_queue.size() == 0) {
        T* obj = new T;
        used.insert(obj);
        return obj;
    } else {
        auto obj = pool_queue.front();
        used.insert(obj);
        pool_queue.pop();
        return obj;
    }
  }
  T* TryAllocate() {
    if(pool_queue.size() == 0) {
        return nullptr;
    } else {
        auto obj = pool_queue.front();
        used.insert(obj);
        pool_queue.pop();
        return obj;
    }
  }

  void Deallocate(T* object) {
    if(used.find(object) == used.end()) {
        throw invalid_argument("pizdes");
    }
    used.erase(object);
    pool_queue.push(object);
  }

  ~ObjectPool() {
    while(pool_queue.size() != 0) {
        delete pool_queue.front();
        pool_queue.pop();
    }
    for(auto ptr: used)
        delete ptr;
  }

private:
  queue<T*> pool_queue;
  set<T*> used;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
