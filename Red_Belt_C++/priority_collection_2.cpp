// tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <map>
#include <tuple>
using namespace std;



template <typename T>
class PriorityCollection {
public:
	using Id = uint32_t;

	// Добавить объект с нулевым приоритетом
	// с помощью перемещения и вернуть его идентификатор
	Id Add(T object) {
		Id id = get_id;
		++get_id;
		id_obj[id] = { move(object), 0 };
		prior_id[0].insert(id);
		return id;
	}

	// Добавить все элементы диапазона [range_begin, range_end)
	// с помощью перемещения, записав выданные им идентификаторы
	// в диапазон [ids_begin, ...)
	template <typename ObjInputIt, typename IdOutputIt>
	void Add(ObjInputIt range_begin, ObjInputIt range_end,
		IdOutputIt ids_begin) {
		while (range_begin != range_end) {
			Id id = get_id;
			++get_id;
			id_obj[id] = { move(*range_begin), 0 };
			++range_begin;
			prior_id[0].insert(id);
			*ids_begin = id;
			++ids_begin;
		}
	}

	// Определить, принадлежит ли идентификатор какому-либо
	// хранящемуся в контейнере объекту
	bool IsValid(Id id) const {
		return static_cast<bool>(id_obj.count(id));
	}

	// Получить объект по идентификатору
	const T& Get(Id id) const {
		return id_obj.at(id).first;
	}

	// Увеличить приоритет объекта на 1
	void Promote(Id id) {
		int priority = id_obj[id].second;

		++id_obj[id].second;
		prior_id[priority].erase(id);
		if (prior_id[priority].empty()) {
			prior_id.erase(priority);
		}
		prior_id[priority + 1].insert(id);
	}

	// Получить объект с максимальным приоритетом и его приоритет
	pair<const T&, int> GetMax() const {
		int max_priority = (*prev(end(prior_id))).first;
		Id temp = *prev(end(prior_id.at(max_priority)));
		return id_obj.at(temp);
	}

	// Аналогично GetMax, но удаляет элемент из контейнера
	pair<T, int> PopMax() {
		int max_priority = (*prev(end(prior_id))).first;
		Id temp = *prev(end(prior_id[max_priority]));
		prior_id[max_priority].erase(temp);
		if (prior_id[max_priority].empty()) {
			prior_id.erase(max_priority);
		}
		pair<T, int> tmp = move(id_obj[temp]);
		id_obj.erase(temp);
		return tmp;
	}

private:
	Id get_id = 0;
	map<Id, pair<T, int>> id_obj;
	map<int, set<Id>> prior_id;
};


class StringNonCopyable : public string {
public:
	using string::string;  // Позволяет использовать конструкторы строки
	StringNonCopyable(const StringNonCopyable&) = delete;
	StringNonCopyable(StringNonCopyable&&) = default;
	StringNonCopyable& operator=(const StringNonCopyable&) = delete;
	StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
	PriorityCollection<StringNonCopyable> strings;
	const auto white_id = strings.Add("white");
	const auto yellow_id = strings.Add("yellow");
	const auto red_id = strings.Add("red");
	strings.Promote(yellow_id);
	for (int i = 0; i < 2; ++i) {
		strings.Promote(red_id);
	}
	strings.Promote(yellow_id);
	{
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "red");
		ASSERT_EQUAL(item.second, 2);
	}
	{
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "yellow");
		ASSERT_EQUAL(item.second, 2);
	}
	{
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "white");
		ASSERT_EQUAL(item.second, 0);
	}
}


int main() {
	TestRunner tr;
	RUN_TEST(tr, TestNoCopy);
	return 0;
}
