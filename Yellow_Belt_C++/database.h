#pragma once
#include "date.h"
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
using namespace std;

class Database {
public:
    void Add(const Date& date, const string& event);

	template <typename Func>
	int RemoveIf(Func predicat) {
		int cnt = 0;
		for (auto& item : dbase) {
			(item.second).remove_if([&](const string& ev) {
				if (predicat(item.first, ev)) {
					++cnt;
					return true;
				}
				return false;
				});
		}
		return cnt;
	}

    template <typename Func>
	vector<string> FindIf(Func predicat) const {
		vector<string> vec;
		stringstream ss;
		for (const auto& item : dbase) {
			for (const string& ev : item.second) {
				if (predicat(item.first, ev)) {
					ss << item.first << " " << ev;
					vec.push_back(ss.str());
				}
				ss.clear();
				ss.str("");
			}
		}
		return vec;
	}

    void Print(ostream& output) const;

    string Last(const Date& date) const;

private:
    map<Date, list<string>> dbase;
};
