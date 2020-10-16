#include "airline_ticket.h"
#include "test_runner.h"

using namespace std;

#define UPDATE_FIELD(ticket, field, values) {            \
map<string, string>::const_iterator it = values.find(#field);                              \
  if (it != values.end()) {                             \
    stringstream ss(it->second);      \
    ss >> ticket.field;} \
}

bool operator ==(const Date& lhs, const Date& rhs) {
    return (lhs.day == rhs.day) && (lhs.month == rhs.month) && (lhs.year == rhs.year);
}

bool operator ==(const Time& lhs, const Time& rhs) {
    return (lhs.hours == rhs.hours) && (lhs.minutes == rhs.minutes);
}

ostream& operator <<(ostream& os, const Date& dt) {
    os << dt.year << " " << dt.month << " " << dt.day;
    return os;
}

stringstream& operator >>(stringstream& is, Date& dt) {
    is >> dt.year;
    is.ignore(1);
    is >> dt.month;
    is.ignore(1);
    is >> dt.day;
    return is;
}

ostream& operator <<(ostream& os, const Time& t) {
    os << t.hours << " " << t.minutes;
    return os;
}

stringstream& operator >>(stringstream& is, Time& t) {
    is >> t.hours;
    is.ignore(1);
    is >> t.minutes;
    return is;
}

bool operator <(const Date& lhs, const Date& rhs) {
    return lhs.year * 1000 + lhs.month * 50 + lhs.day < rhs.year * 1000 + rhs.month * 50 + rhs.day;
}

bool operator <(const Time& lhs, const Time& rhs) {
    return lhs.hours * 60 + lhs.minutes < rhs.hours * 60 + rhs.minutes;
}

void TestUpdate() {
  AirlineTicket t;
  t.price = 0;

  const map<string, string> updates1 = {
    {"departure_date", "2018-2-28"},
    {"departure_time", "17:40"},
  };
  UPDATE_FIELD(t, departure_date, updates1);
  UPDATE_FIELD(t, departure_time, updates1);
  UPDATE_FIELD(t, price, updates1);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 0);

  const map<string, string> updates2 = {
    {"price", "12550"},
    {"arrival_time", "20:33"},
  };
  UPDATE_FIELD(t, departure_date, updates2);
  UPDATE_FIELD(t, departure_time, updates2);
  UPDATE_FIELD(t, arrival_time, updates2);
  UPDATE_FIELD(t, price, updates2);

  // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
  // значения этих полей не должны измениться
  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 12550);
  ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestUpdate);
}
