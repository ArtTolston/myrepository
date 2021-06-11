#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>
using namespace std;

/*void PrintVector(const vector<string>& v) {
    for(const string& i: v) {
        cout << i << " ";
    }
    cout << endl;
}*/

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    const string& prefix)
{
    int n = prefix.size();
    return equal_range(range_begin, range_end, prefix, [n](const string& lhs, const string& rhs) {
        for(int i = 0; i < n; i++) {
            if(lhs[i] == rhs[i])
                continue;
            return lhs[i] < rhs[i];
        }
        return false;
    });
}

/*int main() {
    vector<string> v = {"we", "were", "dfdf", "vdccss", "opip", "qwerrt", "xxsssw", "qderr"};
    sort(begin(v), end(v));
    PrintVector(v);
    auto para = FindStartsWith(begin(v), end(v), "qwe");
    cout << para.first - begin(v) << endl << para.second - begin(v) << endl;
    cout << *para.first << " " << *para.second;
}*/
