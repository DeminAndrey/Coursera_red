#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<ofstream> streams;
    for (int i = 0; i < 5; ++i) {
        ofstream stream(to_string(i) + ".txt");
        stream << "File #" << i << "\n";
        streams.push_back(move(stream));
    }
    for (auto& stream : streams) {
        stream << "Vector is ready!" << endl;
    }
    return 0;
}