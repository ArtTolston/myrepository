#include <date.h>



class Date::Date() {year = 0; month = 0; day = 0;};
class Date::Date(int y, int m, int d) {
    year = y;
    month = m;
    day = d;
};
class Date::void SetValues(int a, int b, int c) {
    year = a;
    month = b;
    day = c;
};
class Date::int GetYear() const {
    return year;
  };
class Date::int GetMonth() const {
    return month;
  };
class Date::int GetDay() const {
    return day;
  };

