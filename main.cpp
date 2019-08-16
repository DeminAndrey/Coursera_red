#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class SimpleVector {
public:
    explicit SimpleVector(size_t size) {
        data = new T[size];
    }

    ~SimpleVector() {
        delete[] data;
    }

    T& operator[] (size_t index) {
        return *(data + index);
    }

private:
    T* data;
};

int main() {
    SimpleVector<int> sv(5);
    for (int i = 0; i < 5; ++i) {
        sv[i] = 5 - i;
    }

    for (int i = 0; i < 5; ++i) {
        cout << sv[i] << " ";
    }
    return 0;
}