#include<iostream>

template <typename T> struct cl {
    int k;
    template <typename U> cl(const cl<U>& c2) {
        std::cout << "copy-ctor";
        k = c2.k;
    }
    cl(const cl& c2){

    }
    cl() {}
};

int main() {
   cl<int> c2;
   cl<char> c3{c2};
}
