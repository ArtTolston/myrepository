#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <future>
#include <functional>
using namespace std;

template <typename Iterator>
class IteratorRange {
public:
	IteratorRange(Iterator begin, Iterator end)
		: first(begin)
		, last(end)
		, size_(distance(first, last))
	{
	}

	Iterator begin() const {
		return first;
	}

	Iterator end() const {
		return last;
	}

	size_t size() const {
		return size_;
	}

private:
	Iterator first, last;
	size_t size_;
};

template <typename Iterator>
class Paginator {
private:
	vector<IteratorRange<Iterator>> pages;

public:
	Paginator(Iterator begin, Iterator end, size_t page_size) {
		for (size_t left = distance(begin, end); left > 0; ) {
			size_t current_page_size = min(page_size, left);
			Iterator current_page_end = next(begin, current_page_size);
			pages.push_back({ begin, current_page_end });

			left -= current_page_size;
			begin = current_page_end;
		}
	}

	auto begin() const {
		return pages.begin();
	}

	auto end() const {
		return pages.end();
	}

	size_t size() const {
		return pages.size();
	}
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
	return Paginator(begin(c), end(c), page_size);
}

template <typename ContainerOfVectors>
int64_t SumSingleThread(const ContainerOfVectors& matrix) {
	int64_t sum = 0;
	for (const auto& row : matrix) {
		for (auto item : row) {
			sum += item;
		}
	}
	return sum;
}

struct Stats {
	map<string, int> word_frequences;

	void operator += (const Stats& other) {
		for (const auto& [key, value] : other.word_frequences) {
			word_frequences[key] += value;
		}
	}
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
	Stats result;
	stringstream ss(line);
	string s;
	while (ss >> s) {
		if (key_words.find(s) != end(key_words)) {
			++result.word_frequences[s];
		}
	}
	return result;
}

Stats ExploreKeyWordsSingleThread(
	const set<string>& key_words, istream& input
) {
	Stats result;
	for (string line; getline(input, line); ) {
		result += ExploreLine(key_words, line);
	}
	return result;
}

Stats ExploreKeyWordsSingleThread2(const set<string>& key_words, const vector<string>& page) {
	Stats result;
	{
		LOG_DURATION("cycle")
		for (const string& line : page) {
			result += ExploreLine(key_words, line);
		}
	}
	return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
	Stats result;
	string s;
	vector<string> lines;
	auto itb = lines.begin();
	vector<future<Stats>> futures;
		while (getline(input, s)) {
			lines.push_back(move(s));
		}
	int aux = 0;
	int step = lines.size() / 4, step1 = step;
	vector<vector<string>> pages;
	while (step <= lines.size()) {
		pages.push_back({ lines.begin() + aux, lines.begin() + step});
		if (step == lines.size())
			break;
		aux = step;
		step = (step + step1 >= lines.size()) ? lines.size() : step + step1;
	}
	for (auto& page : pages) {
		futures.push_back(async(ExploreKeyWordsSingleThread2,ref(key_words), ref(page)));
	}
	for (auto& f : futures) {
		result += f.get();
	}
	return result;
}

void TestBasic() {
	const set<string> key_words = { "yangle", "rocks", "sucks", "all" };

	stringstream ss;
	ss << "this new yangle service really rocks\n";
	ss << "It sucks when yangle isn't available\n";
	ss << "10 reasons why yangle is the best IT company\n";
	ss << "yangle rocks others suck\n";
	ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

	const auto stats = ExploreKeyWords(key_words, ss);
	const map<string, int> expected = {
	  {"yangle", 6},
	  {"rocks", 2},
	  {"sucks", 1}
	};
	ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestBasic);
}
