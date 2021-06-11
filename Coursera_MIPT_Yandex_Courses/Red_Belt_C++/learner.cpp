#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <sstream>
using namespace std;

class Learner {
 private:
  set<string> dict;

 public:
  int Learn(const vector<string>& words) {
    int newWords = 0;
    for (const auto& word : words) {
      if (dict.find(word) == end(dict)) {
        ++newWords;
        dict.insert(word);
      }
    }
    return newWords;
  }

  vector<string> KnownWords() {
    vector<string> vec;
    for(const auto& s: dict)
        vec.push_back(s);
    return vec;
  }
};

