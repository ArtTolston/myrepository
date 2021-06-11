#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>
#include <deque>
using namespace std;

void PrintDeque(const deque<string>& deq) {
    for(const auto& str: deq) {
        cout << str;
    }
}

enum class Priority {
    ADDITION_SUBSTITUTION,
    MULTIPLICATION_DIVISION
};

int main() {
    int n = 0;
    deque<string> expression;
    vector<Priority> primary;
    string str, sign, num, tmp;
    cin >> str;
    expression.push_back(str);
    cin >> n;
    cin.ignore(1);
    if(n == 0) {
        cout << expression[0];
        return 0;
    }
    for(int i = 0; i < n; ++i) {
        getline(cin, sign, ' ');
        if(sign == "+" || sign == "-") {
            primary.push_back(Priority::ADDITION_SUBSTITUTION);
        } else {
            primary.push_back(Priority::MULTIPLICATION_DIVISION);
        }
        if(primary.size() > 1) {
            if(*prev(prev(end(primary))) < *prev(end(primary))) {
                expression.push_back(")");
                expression.push_front("(");
            }
        }
        getline(cin, num);
        expression.push_back(" ");
        expression.push_back(sign);
        expression.push_back(" ");
        expression.push_back(num);
    }
    PrintDeque(expression);
    return 0;
}

