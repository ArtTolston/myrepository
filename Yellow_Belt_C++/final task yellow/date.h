#pragma once
#include <sstream>
#include <iostream>
#include <string>
using namespace std;
class Date {
public:
  Date();
  Date(const int& y, const int& m, const int& d);
  void SetValues(const int& a, const int& b, const int& c);
  int GetYear() const;
  int GetMonth() const;
  int GetDay() const;
private:
  int year;
  int month;
  int day;
};

bool operator ==(const Date& lhs, const Date& rhs);

bool operator >=(const Date& lhs, const Date& rhs);

bool operator <=(const Date& lhs, const Date& rhs);

bool operator !=(const Date& lhs, const Date& rhs);

bool operator <(const Date& lhs, const Date& rhs);

bool operator >(const Date& lhs, const Date& rhs);

Date ParseDate(istream& is);

ostream& operator <<(ostream& output, const Date& date);
