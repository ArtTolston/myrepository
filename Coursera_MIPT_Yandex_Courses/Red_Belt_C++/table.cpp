#include "test_runner.h"

using namespace std;

template <typename T>
class Table {
public:
    Table(size_t h, size_t w) {
        height = h;
        width = w;
        Resize(height, width);
    }
    void Resize(size_t h, size_t w) {
        height = h;
        width = w;
        tbl.resize(h);
        for(auto& t : tbl)
            t.resize(w);
    }
    const vector<T>& operator[] (const int& i) const {
        return tbl[i];
    }
    vector<T>& operator [] (const int& j) {
        return tbl[j];
    }
    pair<size_t, size_t> Size() const {
        return make_pair(height, width);
    }

private:
    size_t height;
    size_t width;
    vector<vector<T>> tbl;
};

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
