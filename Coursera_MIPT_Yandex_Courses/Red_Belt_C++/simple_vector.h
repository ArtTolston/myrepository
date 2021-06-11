#pragma once

#include <cstdlib>
#include <algorithm>
using namespace std;
// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
  SimpleVector() {begin_ = nullptr; end_ = nullptr; real_end_ = nullptr;}
  explicit SimpleVector(size_t size) {
    begin_ = new T[size];
    end_ = begin_ + size;
    real_end_ = end_;
  }
  void operator =(const SimpleVector& rhs) {
    delete[] begin_;
    T* ptr = new T[rhs.Capacity()];
    begin_ = ptr;
    end_ = begin_ + rhs.Capacity();
    real_end_ = begin_ + rhs.Size();
    copy(rhs.begin(), rhs.end(), begin_);
  }
  ~SimpleVector() {
    delete[] begin_;
  }

  T& operator[](size_t index) {
    return begin_[index];
  }

  T* begin() {return begin_;}
  T* end() {return real_end_;}

  const T* begin() const {return begin_;}
  const T* end() const {return real_end_;}

  size_t Size() const {return real_end_ - begin_;}
  size_t Capacity() const {return end_ - begin_;}
  void PushBack(const T& value) {
    size_t sz = Size(), cp = Capacity();
    if(cp == 0) {
        begin_ = new T[1];
        end_ = begin_ + 1;
        begin_[sz] = value;
        real_end_ = end_;
        return;
    }
    if(cp > sz) {
        begin_[sz] = value;
        real_end_ = begin_ + sz + 1;
    } else {
        T* new_begin_ = new T[2 * cp];
        copy(begin_, end_, new_begin_);
        delete[] begin_;
        begin_ = new_begin_;
        end_ = begin_ + 2 * cp;
        real_end_ = begin_ + sz;
        begin_[sz] = value;
        ++real_end_;
    }
  }

private:
  T* begin_;
  T* end_;
  T* real_end_;
};
