#include "simple_vector.h"
#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void TestConstruction() {
    SimpleVector<int> empty;
    ASSERT_EQUAL(empty.Size(), 0u);
    ASSERT_EQUAL(empty.Capacity(), 0u);
    ASSERT(empty.begin() == empty.end());

    SimpleVector<string> five_strings(5);
    ASSERT_EQUAL(five_strings.Size(), 5u);
    ASSERT(five_strings.Size() <= five_strings.Capacity());
    for (auto& item : five_strings) {
        ASSERT(item.empty());
    }
    five_strings[2] = "Hello";
    ASSERT_EQUAL(five_strings[2], "Hello");
}

void TestPushBack() {
    SimpleVector<int> v;
    for (int i = 10; i >= 1; --i) {
        v.PushBack(i);
        ASSERT(v.Size() <= v.Capacity());
    }
    sort(begin(v), end(v));
    const vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_EQUAL(v.Size(), expected.size());
    ASSERT(equal(begin(v), end(v), begin(expected)));
}


class Logger {
public:
    Logger() { cout << "Default ctor\n"; }
//    Logger(const Logger&) { cout << "Copy ctor\n"; }
    Logger(const Logger&) = delete;
    Logger(Logger&&) { cout << "Move ctor\n"; }

    void operator=(const Logger&) { cout << "Coppy assignment\n"; }
};

Logger MakeLogger() {
    // copy elision
    return Logger();
}


int main() {
//    TestRunner tr;
//    RUN_TEST(tr, TestConstruction);
//    RUN_TEST(tr, TestPushBack);

    // copy elision
    Logger logger = MakeLogger();

//    Logger other_logger;
//    Logger logger = move(other_logger);

//    SimpleVector<int> source(1);
//    source[0] = 8;
//    SimpleVector<int> target = source;
//
//    cout << source[0] << " " << target[0] << endl;
//    SimpleVector<int> source(1);
//    SimpleVector<int> target(1);
//    target = move(source);
//    cout << source.Size() << " " << target.Size() << endl;
    return 0;
}