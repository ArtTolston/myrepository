#include "test_runner.h"
#include <iostream>
#include <set>
#include <map>
#include <string>
#include <string_view>

using namespace std;

class Translator {
public:
	void Add(string_view source, string_view target) {
		all_words.insert(string(source));
		all_words.insert(string(target));
		auto it1 = all_words.find(string(source));
		auto it2 = all_words.find(string(target));
		dict_to[string_view(*it1)] = string_view(*it2);
		dict_back[string_view(*it2)] = string_view(*it1);
	}

	string_view TranslateForward(string_view source) const {
		if (dict_to.find(source) == end(dict_to))
			return "";
		return dict_to.at(source);
	}
	string_view TranslateBackward(string_view target) const {
		if (dict_back.find(target) == end(dict_back))
			return "";
		return dict_back.at(target);
	}

private:
	set<string> all_words;
	map<string_view, string_view> dict_to, dict_back;
};

void TestSimple() {
	Translator translator;
	translator.Add(string("okno"), string("window"));
	translator.Add(string("stol"), string("table"));

	ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
	ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
	ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestSimple);
	return 0;
}
