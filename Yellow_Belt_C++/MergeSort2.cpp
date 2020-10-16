#include<algorithm>
#include<vector>
#include<iterator>
#include<iostream>
using namespace std;
/*void PrintVector(const vector<int>& v) {
    for(const int& i: v) {
        cout << i << " ";
    }
    cout << endl;
}*/

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if(range_end - range_begin > 2) {
        vector<typename RandomIt::value_type> elements(range_begin, range_end);
        vector<typename RandomIt::value_type> v;
        int step = (end(elements) - begin(elements)) / 3;
        RandomIt it = begin(elements) + step;
        RandomIt it2 = it + step;
        MergeSort(begin(elements), it);
        MergeSort(it, it2);
        MergeSort(it2, end(elements));
        //PrintVector(elements);
        merge(begin(elements) , it, it, it2, back_inserter(v));
        merge( begin(v), end(v) ,it2, end(elements), range_begin);
        //PrintVector(v);
    }
}

/*int main() {
    vector<int> v = {5, 4 , 1, 5,3, 7,0, -2 ,3};
    MergeSort(begin(v), end(v));
    PrintVector(v);
}*/
