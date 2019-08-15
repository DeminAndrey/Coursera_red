#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>

using namespace std;

class ReadingManager {
public:
    ReadingManager()
        : pages_(MAX_USER_COUNT_ + 1, 0),
        last_page(0) {};

    void Read(int user_id, int page_count) {
        if (users_.count(user_id) > 0)  {
            pages_[users_[user_id]]--;
        }
        users_[user_id] = page_count;
        pages_[page_count]++;
    }

    double Cheer(int user_id) const {
        if (users_.count(user_id) == 0) {
            return 0;
        }
        if (users_.size() == 1) {
            return 1;
        }
        const int page_count = users_.at(user_id);

        int count = 0;
        for (int i = 1; i < page_count; ++i) {
            count += pages_[i];
        }

        return count * 1.0 / (users_.size() - 1);
    }

private:
    static const int MAX_USER_COUNT_ = 100'000;

    map<int, int> users_; // пользватели и страница до которой каждый из них прочитал
    vector<int> pages_; // страницы и сколько пользователей читает их
    int last_page;
};


int main() {
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