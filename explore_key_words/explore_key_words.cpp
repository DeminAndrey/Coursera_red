#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <future>
#include <sstream>
#include <functional>
using namespace std;

struct Stats {
    map<string, int> word_frequences;

    void operator += (const Stats& other) {
        for (const auto& [word, freq] : other.word_frequences) {
            word_frequences[word] += freq;
        }
    }
};


vector<string> SplitIntoWords(const string& line) {
    vector<string> result;
    string word;
    bool word_end = false;
    auto start = line.begin();
    for (;start != line.end(); ++start) {
        if (*start != ' ') {
            if (word_end) {
                result.push_back(word);
                word_end = false;
                word = "";
            }
            word += *start;
        } else {
            word_end = true;
            continue;
        }
    }
    result.push_back(word);
    return result;
}

Stats ExploreLine(const set<string>& key_words, const string& line) {
    Stats st;
    for (const auto& word : SplitIntoWords(line)) {
        if (key_words.count(word) > 0) {
            st.word_frequences[word]++;
        }
    }
    return st;
}

Stats ExploreKeyWordsSingleThread(const set<string>& key_words, istream& input) {
    Stats result;
    for (string line; getline(input, line); ) {
        result += ExploreLine(key_words, line);
    }
    return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    // Реализуйте эту функцию
    Stats result;
    vector<future<Stats>> futures;
    vector<stringstream> streams;
    stringstream ss;
    int count = 0;
    for (string line; getline(input, line);) {
        ++count;
        ss << line << " ";
        if (count == 1000) {
            streams.push_back(move(ss));
            count = 0;
        }
    }

    if (ss) {
        streams.push_back(move(ss));
    }

    for (auto& s : streams) {
        futures.push_back(async(ExploreKeyWordsSingleThread, ref(key_words), ref(s)));
    }

    for (auto& f : futures) {
        result += f.get();
    }

    return result;
}

void TestBasic() {
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

//		stringstream ss;
//		for (int i = 0; i < 50; ++i) {
//			ss << "this new yangle service really rocks this new yangle service really rocks this new yangle service really rocks\n";
//			ss << "It sucks when yangle isn't available It sucks when yangle isn't available It sucks when yangle isn't available\n";
//			ss << "10 reasons why yangle is the best IT company 10 reasons why yangle is the best IT company 10 reasons why yangle is the best IT company\n";
//			ss << "yangle rocks others suck yangle rocks others suck yangle rocks others suck yangle rocks others suck yangle rocks others suck\n";
//			ss << "Goondex really sucks, but yangle rocks. Use yangle Goondex really sucks, but yangle rocks. Use yangle Goondex really sucks, but yangle rocks. Use yangle\n";
//		}

    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {
            {"yangle", 6},
            {"rocks", 2},
            {"sucks", 1}
    };
    ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
}
