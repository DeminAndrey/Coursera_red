#include "test_runner.h"
#include "profile.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <deque>
#include <cmath>

using namespace std;


template<typename T>
class PriorityCollection {
public:
    using Id = int;
    
    PriorityCollection() {
        data.reserve(1500000);
        valid.reserve(1500000);
    }
    
    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
    Id Add(T object) {
        Id index = idx;
        idx++;
        set<pair<int, Id>> e;
        e.insert({0, index});
        priority.insert(make_move_iterator(e.begin()), make_move_iterator(e.end()));
        auto *ptr = new pair<int, Id>;
        *ptr = make_pair(0, index);
        data.push_back({ move(object), ptr });
        valid[index] = true;
        return index;
    }
    
    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template<typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
             IdOutputIt ids_begin) {
        for (auto it = make_move_iterator(range_begin);
             it != make_move_iterator(range_end); ++it) {
            *(ids_begin++) = Add(*it);
        }
    }
    
    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const {
        if (id > data.size() - 1) {
            return false;
        }
        return valid[id];
    }
    
    // Получить объект по идентификатору
    const T &Get(Id id) const {
        return data[id].first;
    }
    
    // Увеличить приоритет объекта на 1
    void Promote(Id id) {
        auto *ptr = data[id].second;
        auto extra = priority.extract(*ptr);
        priority.insert({extra.value().first + 1, extra.value().second});
		data[id].second->first++;
		
    }
    
    // Получить объект с максимальным приоритетом и его приоритет
    pair<const T &, int> GetMax() const {
        return { data[prev(priority.end())->second].first,  prev(priority.end())->first };
    }
    
    // Аналогично GetMax, но удаляет элемент из контейнера
    pair<T, int> PopMax() {
        auto priority_rate = prev(priority.end());
        Id max_id = prev(priority.end())->second;
        priority.erase(priority_rate);
        data[max_id].second = nullptr;
        valid[max_id] = false;
        return { move(data[max_id].first), priority_rate->first };
    }
    
private:
    Id idx = 0;
    set<pair<int, Id>> priority;
    vector<pair<T, pair<int, Id>* >> data;
    vector<bool> valid;
};


class StringNonCopyable : public string {
public:
    using string::string;  // Позволяет использовать конструкторы строки
    StringNonCopyable(const StringNonCopyable &) = delete;
    
    StringNonCopyable(StringNonCopyable &&) = default;
    
    StringNonCopyable &operator=(const StringNonCopyable &) = delete;
    
    StringNonCopyable &operator=(StringNonCopyable &&) = default;
};

void TestNoCopy() {
    PriorityCollection<StringNonCopyable> strings;
    {
		 LOG_DURATION("Add")
		 for (int i = 0; i < 10000; ++i) {
			const auto blue_id = strings.Add("blue");
		 }
	}
		
	
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
