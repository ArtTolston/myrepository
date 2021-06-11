#include <vector>
#include <stdexcept>
using namespace std;
template <typename T>
class Deque {
public:
    Deque() {}
    bool Empty() const {return frwd.empty() && bck.empty();}
    size_t Size() const {return frwd.size() + bck.size();}
    T& operator[](size_t index) {
        int sz = frwd.size();
        if(index > sz) {
            return bck[index - sz];
        } else if(index == sz) {
            return bck[0];
        } else {
            return frwd[sz - index - 1];
        }
    }
    const T& operator[](size_t index) const {
        int sz = frwd.size();
        if(index > sz) {
            return bck[index - sz];
        } else if(index == sz) {
            return bck[0];
        } else {
            return frwd[sz - index - 1];
        }
    }
    void PushFront(const T& el) {
        frwd.push_back(el);
    }
    void PushBack(const T& el) {
        bck.push_back(el);
    }

    const T& At(size_t index) const {
        int sz = frwd.size();
        if(index >= sz + bck.size()) {
            throw out_of_range("pzds");
        }
        if(index > sz) {
            return bck[index - sz];
        } else if(index == sz) {
            return bck[0];
        } else {
            return frwd[sz - index - 1];
        }
    }

    T& At(size_t index) {
        int sz = frwd.size();
        if(index >= sz + bck.size()) {
            throw out_of_range("pzds");
        }
        if(index > sz) {
            return bck[index - sz];
        } else if(index == sz) {
            return bck[0];
        } else {
            return frwd[sz - index - 1];
        }
    }

    const T& Front() const {
        if(frwd.empty()) {
            return bck.front();
        } else {
            return frwd.back();
        }
    }

    T& Front() {
        if(frwd.empty()) {
            return bck.front();
        } else {
            return frwd.back();
        }
    }

    const T& Back() const {
        if(bck.empty()) {
            return frwd.front();
        } else {
            return bck.back();
        }
    }

    T& Back() {
        if(bck.empty()) {
            return frwd.front();
        } else {
            return bck.back();
        }
    }



private:
    vector<T> frwd, bck;
};
