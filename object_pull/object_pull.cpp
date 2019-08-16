#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
    T* Allocate() {
        if (!deallocated.empty()) {
            T* alloc = new T(*deallocated.front());
            allocated.insert(alloc);
            deallocated.pop_front();
            return *allocated.find(alloc);
        } else {
            T* alloc = new T;
            allocated.insert(alloc);
            return *allocated.find(alloc);
        }
    }

    T* TryAllocate() {
        if (!deallocated.empty()) {
            T* alloc = new T(*deallocated.front());
            allocated.insert(alloc);
            deallocated.pop_front();
            return *allocated.find(alloc);
        } else {
            return nullptr;
        }
    }

    void Deallocate(T* object) {
        auto it = allocated.find(object);
        if (it != allocated.end()) {
            deallocated.push_back(*it);
            allocated.erase(it);
        } else {
            throw invalid_argument{""};
        }
    }

    ~ObjectPool() {
        for (auto i : allocated) {
            delete i;
        }
        for (auto i : deallocated) {
            delete i;
        }
    }

private:
    deque<T*> deallocated;
    set<T*> allocated;
};

void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}