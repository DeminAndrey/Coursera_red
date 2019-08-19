#include "profile.h"

#include <algorithm>
#include <string_view>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<string_view> SplitIntoWordsView(const string& s) {
    string_view str = s;

    vector<string_view> result;

    while (true) {
        size_t space = str.find(' ');
        result.push_back(str.substr(0, space));

        if (space == str.npos) {
            break;
        } else {
            str.remove_prefix(space + 1);
        }
    }
    return result;
}

string GenerateText() {
    const int SIZE = 10000000;
    string text(SIZE, 'a');
    for (int i = 100; i < SIZE; i += 100) {
        text[i] = ' ';
    }
    return text;
}

int main() {
    const string text = GenerateText();
    {
        LOG_DURATION("string");
        const auto words = SplitIntoWordsView(text);
        cout << words[0] << "\n";
    }
    {
        LOG_DURATION("string_view");
        const auto words = SplitIntoWordsView(text);
        cout << words[0] << "\n";
    }
    return 0;
}