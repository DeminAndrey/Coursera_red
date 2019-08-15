#include "test_runner.h"
#include "profile.h"

#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <random>

using namespace std;

class ReadingManager {
public:
    ReadingManager()
        : pages_(MAX_USER_COUNT_ + 1, 0),
        page_index_(MAX_USER_COUNT_ + 1, 0),
        last_page(0) {};

    void Read(int user_id, int page_count) {
        if (users_.count(user_id) > 0)  {
            pages_[users_[user_id]]--;
        }
        users_[user_id] = page_count;
        pages_[page_count]++;
        if (last_page != 0) {
            if (users_.size() > 1 && page_count < last_page) {
                page_index_[last_page]++;
            }
        }
        last_page = page_count;
        int count = 0;
        for (int i = 1; i < page_count; ++i) {
            count += pages_[i];
        }
//        cout << count << endl;
        page_index_[page_count] = count;
    }

    double Cheer(int user_id) const {
        if (users_.count(user_id) == 0) {
            return 0;
        }
        if (users_.size() == 1) {
            return 1;
        }
        const int page_count = users_.at(user_id);

/*        cout << "user_id: " << user_id << endl;
        cout << "pages: " << pages_[users_.at(user_id)] << endl;
        cout << "index: " << page_index_[users_.at(user_id)] << endl;
        cout << "users size: " << users_.size() << endl;
        cout << "page count: " << page_count << endl;

        cout << endl;
        cout << "USERS" << endl;

        for (const auto i : users_) {
            cout << i.first << " " << i.second << '\n';
        }
        cout << endl;

        cout << "INDEX" << endl;

        for (int i = 0; i < page_index_.size(); ++i) {
            if (page_index_[i] != 0) {
                cout << i << " " << page_index_[i] << '\n';
            }
        }
        cout << endl;
        cout << "PAGES" << endl;

        for (int i = 0; i < pages_.size(); ++i) {
            if (pages_[i] != 0) {
                cout << i << " " << pages_[i] << '\n';
            }
        }*/

/*      for (auto i : users_) {
            cout << i.first << " " << i.second << endl;
        }
        cout << endl;*/

        return page_index_[page_count] * 1.0 / (users_.size() - 1);
    }

private:
    static const int MAX_USER_COUNT_ = 100'000;

    map<int, int> users_; // пользватели и страница до которой каждый из них прочитал
    vector<int> pages_; // страницы и сколько пользователей читает их
    vector<int> page_index_; // индекс каждой страницы, сколько пользователей читает меньше
    int last_page;
};



// Тесты



void TestRead() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> users(1, 100000);
    std::uniform_real_distribution<double> pages(1, 1000);

    int user = static_cast<int>(users(mt));
//    int page = static_cast<int>(pages(mt));

    for (int i = 1; i <= 11; ++i) {
        int page = static_cast<int>(pages(mt));
        manager.Read(i, page);
    }

    for (int i = 1; i < 11; ++i) {
        cout << manager.Cheer(i) << endl;
    }
}


int main() {

    TestRunner tr;
    TestRead();
//    RUN_TEST(tr, TestRead);
//    RUN_TEST(tr, TestCheer);


    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}