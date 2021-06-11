#include <vector>
#include <string>
#include <algorithm>
using namespace std;
vector<string> SplitIntoWords(const string& s) {
    vector<string> str;
    string word;
    auto it = find(begin(s), end(s), ' ');
    auto it_beg = begin(s);
    while(it_beg != end(s)) {
        while(it_beg != it) {
            word += (*it_beg);
            ++it_beg;
        }
        str.push_back(word);
        word.clear();
        if(it != end(s))
            ++it_beg;
        it = find(it_beg, end(s), ' ');
    }
    return str;
}
