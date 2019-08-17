#pragma once

#include <cstdlib>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
    SimpleVector() = default;

    explicit SimpleVector(size_t size) {
        data = new T[size];
        end_ = data + size;
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
        return end_;
    }

    const T* begin() const {
        return data;
    }

    const T* end() const {
        return end_;
    }

    size_t Size() const {
        return end_ - data;
    }
    size_t Capacity() const {

    }
    void PushBack(const T& value) {

    }

private:
    T* data;
    T* end_;
};

