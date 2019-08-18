#include "profile.h"
#include <iostream>
#include <vector>

using namespace std;

/*void LogVectorParams(const vector<int>& v) {
    cout << "Length = " << v.size() << ", " <<
    "capacity = " << v.capacity() << "\n";
    const int* data = v.data();
    for (size_t i = 0; i < v.capacity(); ++i) {
        cout << data[i] << " ";
    }
    cout << "\n";
}*/

int main() {
    vector<int> v = {1, 2, 3};
    int& first = v[0];
    cout << first << "\n";
    v.push_back(4);
    cout << first << "\n";

    /*int size;
    cin >> size;

    {
        LOG_DURATION("push_back");
        vector<int> v;
        for (int i = 0; i < size; ++i) {
            v.push_back(i);
        }
    }
    {
        LOG_DURATION("push_back");
        vector<int> v;
        v.reserve(size);
        for (int i = 0; i < size; ++i) {
            v.push_back(i);
        }
    }*/

    /*vector<int> v = {1, 2, 3};
    LogVectorParams(v);
    v.push_back(4);
    LogVectorParams(v);
    v.shrink_to_fit();
    LogVectorParams(v);*/
    return 0;
}