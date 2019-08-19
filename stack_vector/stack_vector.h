#pragma once

#include <array>
#include <stdexcept>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
    explicit StackVector(size_t a_size = 0) : size_(a_size) {
        if (size_ > N) {
            throw invalid_argument("");
        }
    }

    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }

    auto begin() {
        return data.begin();
    }

    auto end() {
        data.begin() + size_;
    }

    auto begin() const {
        return data.begin();
    }

    auto end() const {
        data.begin() + size_;
    }

    size_t Size() const {
        return size_;
    }

    size_t Capacity() const {
        return N;
    }

    void PushBack(const T& value) {
        if (size_ >= N) {
            throw overflow_error("Full");
        } else {
            data[size_++] = value;
        }
    }

    T PopBack() {
        if (size_ == 0) {
            throw underflow_error("Empty");
        } else {
            --size_;
            return data[size_];
        }
    }

private:
    array<T,N> data;
    size_t size_ = 0;
};
