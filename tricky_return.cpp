#include <fstream>

using namespace std;

pair<ifstream, ofstream> MakeStreams(const string& prefix) {
    return {ifstream(prefix + ".in"), ofstream(prefix + ".out")};
}

ifstream MakeInputStream(const string& prefix) {
    return MakeStreams(prefix).first;
}

int main() {

    return 0;
}