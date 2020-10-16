#include<iostream>
#include<algorithm>
#include<vector>
#include<iterator>
using namespace std;
void PrintVector(const vector<int>& v) {
    for(const int& i: v) {
        cout << i << " ";
    }
    cout << endl;
}

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if(range_end - range_begin > 1) {
        vector<typename RandomIt::value_type> elements(range_begin, range_end);
        int step = (end(elements) - begin(elements)) / 2;
        RandomIt it = begin(elements) + step;
        MergeSort(begin(elements), it);
        MergeSort(it, end(elements));
        merge(begin(elements) , it, it, end(elements), range_begin);
    }
}

/*int main() {
    vector<int> v = {5, 4 , 1, 2};
    MergeSort(begin(v), end(v));
    PrintVector(v);
}*/
