#include "date.h"
#include <iomanip>
using namespace std;
Date::Date() {year = 0; month = 0; day = 0;};

Date::Date(const int& y, const int& m, const int& d) {
    year = y;
    month = m;
    day = d;
};

void Date::SetValues(const int& y, const int& m, const int& d) {
    year = y;
    month = m;
    day = d;
};

int Date::GetYear() const { return year;};

int Date::GetMonth() const { return month;};

int Date::GetDay() const { return day;};

bool operator ==(const Date& lhs, const Date& rhs) {
    if(lhs.GetDay() == rhs.GetDay() && lhs.GetMonth() == rhs.GetMonth() && lhs.GetYear() == rhs.GetYear())
        return true;
    return false;
}

bool operator !=(const Date& lhs, const Date& rhs) {
	if (lhs.GetDay() == rhs.GetDay() && lhs.GetMonth() == rhs.GetMonth() && lhs.GetYear() == rhs.GetYear())
		return false;
	return true;
}

bool operator >(const Date& lhs, const Date& rhs) {
    return lhs.GetYear() *1000 + lhs.GetMonth() * 50 + lhs.GetDay() > rhs.GetYear() * 1000 + rhs.GetMonth() * 50 + rhs.GetDay();
}

bool operator >=(const Date& lhs, const Date& rhs) {
	return lhs.GetYear() * 1000 + lhs.GetMonth() * 50 + lhs.GetDay() >= rhs.GetYear() * 1000 + rhs.GetMonth() * 50 + rhs.GetDay();
}

bool operator <=(const Date& lhs, const Date& rhs) {
	return lhs.GetYear() * 1000 + lhs.GetMonth() * 50 + lhs.GetDay() <= rhs.GetYear() * 1000 + rhs.GetMonth() * 50 + rhs.GetDay();
}

bool operator <(const Date& lhs, const Date& rhs) {
	return lhs.GetYear() * 1000 + lhs.GetMonth() * 50 + lhs.GetDay() < rhs.GetYear() * 1000 + rhs.GetMonth() * 50 + rhs.GetDay();
}

Date ParseDate(istream& is) {
    int y = 0, m = 0, d = 0;
	is >> y;
	is.ignore(1);
	is >> m;
	is.ignore(1);
	is >> d;
	is.ignore(1);
    Date date(y, m, d);
    return date;
}

ostream& operator <<(ostream& output, const Date& date) {
    output << setfill('0') << setw(4) << date.GetYear() << "-" << setw(2) << date.GetMonth() << "-" << setw(2) << date.GetDay();
    return output;
    return output;
}
