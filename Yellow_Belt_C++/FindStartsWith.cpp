#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>

using namespace std;
void PrintVector(const vector<string>& v) {
    for(const string& i: v) {
        cout << i << " ";
    }
    cout << endl;
}

bool comp(const string& s1, const string& s2) {
    return s1[0] < s2[0];
}

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    char prefix)
{
     stringstream ss;
     ss << prefix;
     string str;
     ss >> str;
     //RandomIt it1 = lower_bound(range_begin, range_end, str, comp);
     //RandomIt it2 = upper_bound(range_begin, range_end, str, comp);

    return equal_range(range_begin, range_end, str, comp);
}

int main() {
    vector<string> v = {"we", "were", "dfdf", "vdccss", "opip", "qwerrt", "xxsssw"};
    sort(begin(v), end(v));
    PrintVector(v);
    auto para = FindStartsWith(begin(v), end(v), 'o');
    cout << para.first - begin(v) << endl << para.second - begin(v) << endl;
}
