#include <iostream>
#include <list>
#include <vector>
using namespace std;

int main() {
    list<int> row_of_sportsmen;
    vector<list<int>::iterator> auxulary_vec;
    int n = 0;
    cin >> n;
    auto it_end = end(row_of_sportsmen);
    auxulary_vec.resize(100000 + 1, it_end);
    for(int i = 0; i < n; ++i) {
        int sp_num = 0, num_after_which = 0;
        cin >> sp_num >> num_after_which;
        if(auxulary_vec[num_after_which] == it_end) {
            row_of_sportsmen.push_back(sp_num);
            auxulary_vec[sp_num] = prev(end(row_of_sportsmen));
        } else {
            auto it = auxulary_vec[num_after_which];
            row_of_sportsmen.insert(it, sp_num);
            auxulary_vec[sp_num] = prev(it);
        }
    }
    for(auto it = begin(row_of_sportsmen), ite = end(row_of_sportsmen); it != ite; ++it) {
        cout << *it << " ";
    }
    return 0;
}
