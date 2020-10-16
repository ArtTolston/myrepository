#include "database.h"
using namespace std;

void Database::Add(const Date& date, const string& event) {
	auto& st = unique[date];
    auto it = st.find(event);
    if(it == end(st)) {
        dbase[date].push_back(event);
		st.insert(event);
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
        auto vec = dbase.at(date);
		stringstream ss;
		ss << date << " " << vec.back();
        return ss.str();
    }
	auto it = dbase.upper_bound(date);

    if(it == begin(dbase)) {
		return "No entries";
    }

    auto vec = (*prev(it)).second;
	stringstream ss;
	ss << (*prev(it)).first << " " << vec.back();
    return ss.str();
}
