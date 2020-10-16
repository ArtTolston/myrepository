#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
void PrintStats(vector<Person> persons) {
    string s("Median age");
    cout << s <<  " = " << ComputeMedianAge(begin(persons), end(persons)) << endl;
    vector<Person>::iterator it = partition(begin(persons), end(persons), [](const Person& p) {
        return p.gender == Gender::FEMALE;
    });
    cout << s << " for females = " << ComputeMedianAge(begin(persons), it) << endl;
    cout << s << " for males = " << ComputeMedianAge(it, end(persons)) << endl;
    auto it2 = partition(begin(persons), it, [](const Person& p) {
        return p.is_employed;
    });
    cout << s << " for employed females = " << ComputeMedianAge(begin(persons), it2) << endl;
    cout << s << " for unemployed females = " << ComputeMedianAge(it2, it) << endl;
    auto it3 = partition(it, end(persons), [](const Person& p) {
        return p.is_employed;
    });
    cout << s << " for employed males = " << ComputeMedianAge(it, it3) << endl;
    cout << s << " for unemployed males = " << ComputeMedianAge(it3, end(persons)) << endl;
}
