#include "search_server.h"
#include "iterator_range.h"
//#include "synhronized.h"
#include "parse.h"

#include <algorithm>
//#include <iterator>
//#include <sstream>
#include <numeric>

//vector<string> SplitIntoWords(const string& line) {
//    istringstream words_input(line);
//    return {istream_iterator<string>(words_input), istream_iterator<string>()};
//}

void UpdateIndex(istream& document_input, Synchronized<InvertedIndex>& index) {
    InvertedIndex new_index(document_input);
    swap(index.GetAccess().ref_to_value, new_index);
}

void Search(istream& query_input, ostream& search_results_output, Synchronized<InvertedIndex>& index_handle) {
    vector<size_t> docid_count;
    vector<int64_t> doc_ids;

    for (string current_query; getline(query_input, current_query);) {
//        const auto words = SplitIntoWords(current_query);
        const auto words = SplitIntoWordsView(current_query);

        {
            auto access = index_handle.GetAccess();

            const size_t doc_count = access.ref_to_value.GetAll().size();
            docid_count.assign(doc_count, 0);
            doc_ids.resize(doc_count);

            auto& index = access.ref_to_value;
            for (const auto& word : words) {
                for (const auto& [doc_id, hitcount] : index.Lookup(word)) {
                    docid_count[doc_id] += hitcount;
                }
            }
        }

        iota(doc_ids.begin(), doc_ids.end(), 0);
        {
            partial_sort(
                begin(doc_ids),
                Head(doc_ids, 5).end(),
                end(doc_ids),
                [&docid_count](int64_t lhs, int64_t rhs) {
                  return pair(docid_count[lhs], -lhs) > pair(docid_count[rhs], -rhs);
                }
            );
        }

        search_results_output << current_query << ':';
        for (size_t doc_id : Head(doc_ids, 5)) {
            const size_t hitcount = docid_count[doc_id];
            if (hitcount == 0) break;

            search_results_output << " {"
                                  << "docid: " << doc_id << ", "
                                  << "hitcount: " << hitcount << '}';
        }
        search_results_output << '\n';
    }
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
    async_tasks.push_back(async(UpdateIndex, ref(document_input), ref(index)));
}

void SearchServer::AddQueriesStream(
    istream& query_input, ostream& search_results_output
) {
    async_tasks.push_back(async(Search, ref(query_input), ref(search_results_output), ref(index)));
}

InvertedIndex::InvertedIndex(istream& document_input) {
    for (string current_document; getline(document_input, current_document);) {
//        Add(move(current_document));
        docs.push_back(move(current_document));

        size_t docid = docs.size() - 1;
//        for (auto& word : SplitIntoWords(docs.back())) {
        for (string_view word : SplitIntoWordsView(docs.back())) {
            auto& tmp = index[word];
            if (!tmp.empty() && tmp.back().docid == docid) {
                ++tmp.back().hitcount;
            } else {
                tmp.push_back({docid, 1});
            }
        }
    }
}

//void InvertedIndex::Add(const string& document) {
//    docs.push_back(move(document));
//
//    const size_t docid = docs.size() - 1;
//    for (auto& word : SplitIntoWords(docs.back())) {
//        auto& tmp = index[word];
//
//        if (!tmp.empty() && tmp.back().docid == docid) {
//              ++tmp.back().hitcount;
//        } else {
//            tmp.push_back({docid, 1});
//        }
//    }
//}

const vector<InvertedIndex::Entry>& InvertedIndex::Lookup(string_view word) const {
    static const vector<Entry> res;
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return res;
    }
}
