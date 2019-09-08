#include "test_runner.h"

#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>
#include <utility>
#include <deque>
#include <list>
#include <iterator>

using namespace std;



template<typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
/*    deque<typename RandomIt::value_type> pool(make_move_iterator(first), make_move_iterator(last));

    size_t cur_pos = 0;
    while (!pool.empty()) {
        *(first++) = move(pool[cur_pos]);
        pool.erase(pool.begin() + cur_pos);
        if (pool.empty()) {
            break;
        }
//        cout << cur_pos << " " << step_size << " " << pool.size() << " " << (last - first) << endl;
        cur_pos = (cur_pos + step_size - 1) % pool.size();
    }

    list<typename RandomIt::value_type> pool(make_move_iterator(first), make_move_iterator(last));
    list<typename RandomIt::value_type> pool;
    move(first,last,back_inserter(pool));

    auto it = pool.begin();

    while (!pool.empty()) {

        *(first++) = move(*it);
        it = pool.erase(it);
        if (pool.empty()) {
            break;
        }

        size_t dist = distance(it, pool.end());

        if (dist <= step_size - 1) {
            it = pool.begin();
            if (next(it) != pool.end()) {
                it = next(it, step_size - dist - 1);
            }
        } else {
            it = next(it, step_size - 1);
        }
    }*/

    /*list<typename RandomIt::value_type> pool;
    move(first, last, back_inserter(pool));
    size_t cur_pos = 0;
    size_t pred_pos = 0;

    auto it = pool.begin();

    while (!pool.empty())
    {
        *(first++) = move(*it);
        it = pool.erase(it);
        if (pool.empty()) break;
        for (size_t ind = pred_pos; ind < cur_pos; ++ind)
        {
            next(it);
            if (it == pool.end()) it = pool.begin();

        }

        pred_pos = cur_pos;
        cur_pos = (cur_pos + step_size - 1) % pool.size();
    }*/

    const uint32_t range_size = last - first;
    if (range_size <= 2) {
        return;
    }

    vector<uint32_t> next_alive_positions(range_size);
    iota(begin(next_alive_positions), end(next_alive_positions), 1);
    next_alive_positions.back() = 0;

    vector<typename RandomIt::value_type> permutation;
    uint32_t current_position = 0;
    uint32_t prev_alive_position = range_size - 1;

    for (uint32_t step_index = 0; step_index < range_size; ++step_index) {
        permutation.push_back(move(*(first + current_position)));
        next_alive_positions[prev_alive_position] = next_alive_positions[current_position];
        for (uint32_t i = 0; i < step_size; ++i) {
            if (i > 0) {
                prev_alive_position = current_position;
            }
            current_position = next_alive_positions[current_position];
        }
    }
//    for (uint32_t i = 0; i < range_size; ++i, ++first) {
//        *first = move(permutation[i]);
//    }

    move(begin(permutation), end(permutation), first);
}

vector<int> MakeTestVector() {
    vector<int> numbers(10);
    iota(begin(numbers), end(numbers), 0);
    return numbers;
}

void TestIntVector() {
    const vector<int> numbers = MakeTestVector();
    {
        vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
        ASSERT_EQUAL(numbers_copy, numbers);
    }
    {
        vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 3);
        ASSERT_EQUAL(numbers_copy, vector<int>({0, 3, 6, 9, 4, 8, 5, 2, 7, 1}));
    }
}

// Это специальный тип, который поможет вам убедиться, что ваша реализация
// функции MakeJosephusPermutation не выполняет копирование объектов.
// Сейчас вы, возможно, не понимаете как он устроен, однако мы расскажем,
// почему он устроен именно так, далее в блоке про move-семантику —
// в видео «Некопируемые типы»

struct NoncopyableInt {
    int value;

    NoncopyableInt(const NoncopyableInt &) = delete;

    NoncopyableInt &operator=(const NoncopyableInt &) = delete;

    NoncopyableInt(NoncopyableInt &&) = default;

    NoncopyableInt &operator=(NoncopyableInt &&) = default;
};

bool operator==(const NoncopyableInt &lhs, const NoncopyableInt &rhs) {
    return lhs.value == rhs.value;
}

ostream &operator<<(ostream &os, const NoncopyableInt &v) {
    return os << v.value;
}

void TestAvoidsCopying() {
    vector<NoncopyableInt> numbers;
    numbers.push_back({1});
    numbers.push_back({2});
    numbers.push_back({3});
    numbers.push_back({4});
    numbers.push_back({5});

    MakeJosephusPermutation(begin(numbers), end(numbers), 2);

    vector<NoncopyableInt> expected;
    expected.push_back({1});
    expected.push_back({3});
    expected.push_back({5});
    expected.push_back({4});
    expected.push_back({2});

    ASSERT_EQUAL(numbers, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    RUN_TEST(tr, TestAvoidsCopying);
    return 0;
}
