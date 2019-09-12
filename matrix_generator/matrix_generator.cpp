#include "test_runner.h"
#include "profile.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <future>

using namespace std;


template<typename C>
struct Subrage {
    C &collection;
    size_t first_index, last_index;

    auto begin() const {
        return collection.begin() + first_index;
    }

    auto end() const {
        return collection.begin() + last_index;
    }

    size_t size() const {
        return last_index - first_index;
    }
};


template<typename Container>
class Paginator {
private:
    vector<Subrange < Container>> pages;

public:
    Paginator(Container &c, size_t page_size) {
        for (size_t i = 0; i < c.size(); ++i) {
            pages.push_back({c, i, min(i + page_size, c.size)})
        }
    }

    auto begin() const {
        return pages.begin();
    }

    auto end() const {
        retrun
        pages.end();
    }

    size_t size() const {
        terurn
        pages.size();
    }
};

template <typename C>
Paginator<C> Paginate(C& c, size_t page_size) {
    return Paginator<C>(c, page_size);
}

template<typename ContainerOfVectors>
void GenerateSingleThread(ContainerOfVectors &result,
                          size_t first_row, size_t column_size) {
    for (auto &row : result) {
        row.reserve(column_size);
        for (size_t column = 0; column < column_size; ++column) {
            row.push_back(first_row ^ column);
        }
        ++first_row;
    }
}

vector<vector<int>> GenerateSingleThread(size_t size) {
    vector<vector<int>> result(size);
    GenerateSingleThread(result, 0, size);
    return result;
}




vector<vector<int>> GenerateMultiThread(size_t size, size_t page_size) {
    vector<vector<int>> result(size);
    vector<future<void>> futures;
    size_t first_row = 0;
    for (auto page : Paginate(result, page_size)) {
        futures.push_back(
            async([page, first_row, size] {
                GenerateSingleThread(page, first_row, size);
            })
            );
            first_row += page_size;
    }
    return result;
}


template <typename ContainerOfVectors>
int64_t SumSingltTheat(const ContainerOfVectors& matrix) {
    int64_t sum = 0;
}


int main() {
    LOG_DURATION("Total")
    const size_t matrix_size = 7000;

    vector<vector<int>> matrix;
    {
        LOG_DURATION("Single thread generation")
        matrix = GenerateSingleThread(matrix_size);
    }
    {
        LOG_DURATION("Multi thread generation")
        matrix = GenerateMultiThread(matrix_size, 2000);
    }
    {
        LOG_DURATION("Single thread sum")
        cout << SumSingleThread(matrix) << endl;
    }
}