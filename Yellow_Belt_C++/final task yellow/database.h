#pragma once
#include "date.h"
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <set>
#include <iterator>
using namespace std;

class Database {
public:
    void Add(const Date& date, const string& event);

	template <typename Func>
	int RemoveIf(Func predicat) {
		int cnt = 0;
		for (auto it = begin(dbase); it != end(dbase); ) {
			auto& vec = (*it).second;
			auto dat = (*it).first;
			auto iter = stable_partition(begin(vec), end(vec), [&](const string& ev) {
				if (!predicat(dat, ev)) {
					return true;
				}
				++cnt;
				unique[dat].erase(ev);
				return false;
			});
			if (iter == begin(vec)) {
				dbase.erase(it++);
				unique.erase(dat);
			}
			else {
				vec.erase(iter, end(vec));
				++it;
			}
		}
		return cnt;
	}

    template <typename Func>
	vector<string> FindIf(Func predicat) const {
		vector<string> vec;
		stringstream ss;
		for (const auto& item : dbase) {
			for (const auto& ev : item.second) {
				if (predicat(item.first, ev)) {
					ss << item.first << " " << ev;
					vec.push_back(ss.str());
					//mb clear
					ss.str("");
				}
			}
		}
		return vec;
	}

    void Print(ostream& output) const;

    string Last(const Date& date) const;

private:
    map<Date, vector<string>> dbase;
	map<Date, set<string>> unique;
};

