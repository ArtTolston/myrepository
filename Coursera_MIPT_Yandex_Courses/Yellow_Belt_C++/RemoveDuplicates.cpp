#include<algorithm>
#include<vector>
template <typename T>
void RemoveDuplicates(vector<T>& elements) {
    sort(begin(elements), end(elements));
    auto it = unique(begin(elements), end(elements));
    elements.erase(it, end(elements));
}
