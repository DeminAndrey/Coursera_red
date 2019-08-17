#pragma once

#include <cstdlib>
#include <algorithm>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
    SimpleVector() :
        start_(new T[0]),
        end_(start_),
        finish_(start_) {}

    explicit SimpleVector(size_t size) {
        start_ = new T[size];
        end_ = start_ + size;
        finish_ = start_ + size;
    }

    ~SimpleVector() {
        delete[] start_;
    }

    T& operator[](size_t index) {
        return start_[index];
    }

    T* begin() {
        return start_;
    }
    T* end() {
        return end_;
    }

    const T* begin() const {
        return start_;
    }

    const T* end() const {
        return end_;
    }

    size_t Size() const {
        return end_ - start_;
    }
    size_t Capacity() const {
        return finish_ - start_;
    }
    void PushBack(const T& value) {
        if (Size() == 0) {
            start_ = new T[1];
            *start_ = value;
            end_ = start_ + 1;
            finish_ = start_ + 1;
        } else if (Size() != 0 && Size() == Capacity()) {
            size_t new_capacity = 2 * Capacity();
            size_t new_size = Size() + 1;
            T* new_start_ = new T[new_capacity];
            std::copy(begin(), end(), new_start_);
            delete[] start_;
            start_ = new_start_;
            finish_ = start_ + new_capacity;
            start_[new_size - 1] = value;
            end_ = start_ + new_size;
        } else {
            start_[Size()] = value;
            end_ = start_ + Size() + 1;
        }
    }

private:
    T* start_;
    T* end_;
    T* finish_;
};

