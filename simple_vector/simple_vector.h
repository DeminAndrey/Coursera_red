#pragma once

#include <algorithm>
using namespace std;

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
    SimpleVector() = default;

    explicit SimpleVector(size_t size) :
        data(new T[size]),
        size(size),
        capacity(size) {
    }

    SimpleVector(const SimpleVector& other) :
        data(new T[other.capacity]),
        size(other.size),
        capacity(other.capacity) {
        copy(other.begin(), other.end(), begin());
    }

    SimpleVector(SimpleVector&& other) :
        data(other.data),
        size(other.size),
        capacity(other.capacity) {
        other.data = nullptr;
        other.size = other.capacity = 0;
    }

    void operator=(const SimpleVector& other) {
        auto new_data = new T[other.capacity];
        copy(other.begin(), other.end(), new_data);
        delete[] data;
        data = new_data;
        size = other.size;
        capacity = other.capacity;
    }

    void operator=(SimpleVector&& other) {
        delete[] data;
        data = other.data;
        size = other.size;
        capacity = other.capacity;
        other.data = nullptr;
        other.size = other.capacity = 0;
    }

    ~SimpleVector() {
        delete[] data;
    }

    T& operator[](size_t index) {
        return data[index];
    }

    T* begin() {
        return data;
    }
    T* end() {
        return data + size;
    }

    const T* begin() const {
        return data;
    }

    const T* end() const {
        return data + size;
    }

    size_t Size() const {
        return size;
    }
    size_t Capacity() const {
        return capacity;
    }
    void PushBack(const T& value) {
        if (size >= capacity) {
            auto new_cap = capacity == 0 ? 1 : 2 * capacity;
            auto new_data = new T[new_cap];
            copy(begin(), end(), new_data);
            delete[] data;
            data = new_data;
            capacity = new_cap;
        }
        data[size++] = value;
    }

private:
    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
};

