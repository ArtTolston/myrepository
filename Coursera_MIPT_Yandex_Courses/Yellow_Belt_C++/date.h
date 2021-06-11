#pragma once
#include <iostream>
#include <sstream>
class Date {
public:
  Date();

  Date(int y, int m, int d);

  void SetValues(int a, int b, int c);

  int GetYear() const;

  int GetMonth() const;

  int GetDay() const;

private:
  int year;
  int month;
  int day;
};

Date ParseDate(istringstream& is);

ostringstream& operator <<(ostringstream& output, const Date& date);
