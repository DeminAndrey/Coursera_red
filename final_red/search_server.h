#pragma once

#include "synhronized.h"

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <utility>
#include <future>
#include <deque>
using namespace std;

class InvertedIndex {
public:
    struct Entry {
        size_t docid;
        size_t hitcount;
    };

    InvertedIndex() = default;
    explicit InvertedIndex(istream& document_input);

//    void Add(const string& document);
    const vector<Entry>& Lookup(string_view word) const;

    const deque<string>& GetAll() const {
        return docs;
    }

private:
    deque<string> docs;
    map<string_view, vector<Entry>> index;
};

class SearchServer {
public:
    SearchServer() = default;
    explicit SearchServer(istream& document_input)
        : index(InvertedIndex(document_input)) {}

    void UpdateDocumentBase(istream& document_input);
    void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
    Synchronized<InvertedIndex> index;
    vector<future<void>> async_tasks;
};
