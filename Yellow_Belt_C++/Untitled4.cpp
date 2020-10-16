#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
using namespace std;
void PrintVector(const vector<string>& v) {
    for(const string& i: v) {
        cout << i << " ";
    }
    cout << endl;
}
bool operator ==(const string& s1, const string& s2) {
    return s1[0] == s2[0];
}
bool operator <(const string& s1, const string& s2) {
    return s1[1] < s2[1];
}

bool comp(const string& s1, const string& s2) {
    return s1[0] < s2[0];
}

using namespace std;
int main() {
    string s1 = "w";
    string s2 = "wcd";
    vector<string> v = {"we", "were", "dfdf", "vdccss", "opip", "qwerrt", "xxsssw"};
    sort(begin(v), end(v));
    auto it = upper_bound(begin(v), end(v), "w", comp);
    PrintVector(v);
    cout << *it;

}
