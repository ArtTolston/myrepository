#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  if(range_end - range_begin < 2) {
    return;
  }
  vector<typename RandomIt::value_type> vec(make_move_iterator(range_begin), make_move_iterator(range_end));
  int step = (range_end - range_begin) / 3;
  RandomIt it1 = begin(vec) + step;
  RandomIt it2 = begin(vec) + 2 * step;
  MergeSort(begin(vec) , it1);
  MergeSort(it1 , it2);
  MergeSort(it2 , end(vec));
  vector<typename RandomIt::value_type> temp;
  merge(make_move_iterator(begin(vec)), make_move_iterator(it1), make_move_iterator(it1), make_move_iterator(it2), back_inserter(temp));
  merge(make_move_iterator(begin(temp)), make_move_iterator(end(temp)), make_move_iterator(it2), make_move_iterator(end(vec)), range_begin);
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
