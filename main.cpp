#include "test.h"
#include <iostream>

using namespace std;



void NS2::hello_world() {
    cout << "Hello, world!" << endl;
}
namespace NS2 {
    void Test() {
        cout << "Test" << endl;
    }
}

void Loyalty::Events::Start() {

}

int main() {
    NS2::hello_world();
    NS2::Test();
    return 0;
}