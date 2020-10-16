#include "test_runner.h"
#include <vector>
#include <future>
using namespace std;

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
  int64_t sum = 0, part = 0;
  vector<future<int>> f;
  size_t step = matrix.size() / 2;
  f.push_back(async([&] {
     for(int i = 0; i < step; i++) {
        for(int k: matrix[i]) {
            part += k;
        }
     }
  }));
  part = 0;
    f.push_back(async([&] {
     for(int i = step; i < matrix.size(); i++) {
        for(int k: matrix[i]) {
            part += k;
        }
     }
  }));
  for(auto fut: f) {
    sum += fut.get();
  }
  return sum;
}

void TestCalculateMatrixSum() {
  const vector<vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);
}
