#include<set>
#include<iostream>
using namespace std;
set<int>::const_iterator FindNearestElement(
    const set<int>& numbers,
    int border) {
    if(numbers.empty())
        return end(numbers);
    auto it = numbers.find(border);
    if(it != end(numbers))
        return it;
    auto up = numbers.upper_bound(border);
    if(up == end(numbers))
        return prev(up);
    else if(up == begin(numbers)) {
        return up;
    } else if(*up - border == border - *prev(up)) {
        return prev(up);
    } else {
        return *up - border > border - *prev(up)? prev(up) : up;
    }
}

/*int main() {
    set<int> q;
    cout << *(FindNearestElement(q, 5));
}*/
