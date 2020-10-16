#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
using namespace std;

void PrintVector(const vector<int>& v) {
    for(const int& i: v) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    vector<vector<int>> permutes;
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++) {
        v[i] = i + 1;
    }
    while(true) {
        permutes.push_back(v);
        if(!next_permutation(begin(v), end(v)))
            break;
    }
    sort(begin(permutes), end(permutes), [](const vector<int>& lhs, const vector<int>& rhs) {
        int i = 0;
        while(i < lhs.size()) {
            if(lhs[i] != rhs[i])
                return lhs[i] > rhs[i];
            else
                ++i;
         }
        return false;
    });
    for(const vector<int>& vec: permutes) {
        PrintVector(vec);
    }
}
