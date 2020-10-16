#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
void PrintVectorPart(const vector<int>& numbers) {
    auto it = find_if(begin(numbers), end(numbers), [](const int& num) {
        return num < 0;
    });
    while(it != begin(numbers)) {
        it--;
        cout << *it << " ";
    }
}
