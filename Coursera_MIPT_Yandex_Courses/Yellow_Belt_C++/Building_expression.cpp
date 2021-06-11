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

int main() {
    int n = 0;
    deque<string> expression;
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
        expression.push_back(")");
        expression.push_front("(");
        getline(cin, sign, ' ');
        getline(cin, num);
        expression.push_back(" ");
        expression.push_back(sign);
        expression.push_back(" ");
        expression.push_back(num);
    }
    PrintDeque(expression);
    return 0;
}
