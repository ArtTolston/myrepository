#include <vector>
#include <set>
template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
    auto it = find_if(begin(elements), end(elements), [border](const T& elem) {
        return elem > border;
    });
    vector<T> out;
    while(it != end(elements)) {
        out.push_back(*it);
        it++;
    }
    return out;
}
