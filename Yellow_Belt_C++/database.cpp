#include "Database.h"
using namespace std;

void Database::Add(const Date& date, const string& event) {
    auto it = find(begin(dbase[date]), end(dbase[date]), event);
    if(it == end(dbase[date])) {
        dbase[date].push_back(event);
    }
}

void Database::Print(ostream& output) const { //какой аутпут
    for(const auto& item: dbase) {
        for(const string& s: item.second) {
            output << item.first << " " << s << endl;
        }
    }
}

string Database::Last(const Date& date) const {
    if(dbase.count(date) != 0) {
        auto lst = dbase.at(date);
		stringstream ss;
		ss << date << " " << lst.back();
        return ss.str();
    }
    auto it = find_if(begin(dbase), end(dbase), [date] (const auto& p) { //check
        return p.first > date;
    });
    if(it == begin(dbase)) {
		return "No entries";
    }

    auto lst = (*prev(it)).second;
	stringstream ss;
	ss << (*prev(it)).first << " " << lst.back();
    return ss.str();
}
