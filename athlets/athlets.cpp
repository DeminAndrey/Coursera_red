#include <iostream>
#include <list>
using namespace std;

struct Athlet {
    size_t current_number;
    Athlet* next;
};

int main() {
    int n;
    cin >> n;
    size_t current;
    size_t next;
    list<Athlet*> athlets(n);
    for (size_t i = 0; i < n; ++i) {
        cin >> current >> next;
        auto athlet = new Athlet;
        auto next_athlet = new Athlet;
        athlet->current_number = current;
        next_athlet->current_number = next;
        athlet->next = next_athlet;
        athlets.push_back(athlet);
    }

    Athlet* first = athlets.front();

    for (auto i = first; first; first->next) {
        cout << first->current_number << " ";
    }

    return 0;
}