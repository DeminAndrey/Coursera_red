#include "test_runner.h"

#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <random>

using namespace std;

class ReadingManager {
public:
  ReadingManager()
      : user_page_counts_(MAX_USER_COUNT_ + 1, 0),
        sorted_users_(),
        user_positions_(MAX_USER_COUNT_ + 1, -1) {}

  void Read(int user_id, int page_count) { // 1
    if (user_page_counts_[user_id] == 0) {
      AddUser(user_id);
    }
    user_page_counts_[user_id] = page_count;

//    cout << "user page count: " << user_page_counts_[user_id] << endl;

    int& position = user_positions_[user_id];

//    cout << "position: " << position << endl;

//      cout << endl;


//      cout << "USER PAGE COUNTS" << endl;
//      for (int i = 0; i < user_page_counts_.size(); ++i) {
//          if (user_page_counts_[i] != 0) {
//              cout << i << " " << user_page_counts_[i] << '\n';
//          }
//      }
//
//      cout << endl;
//
//      cout << "SORTED USERS" << endl;
//      for (int i = 0; i < sorted_users_.size(); ++i) {
//          if (sorted_users_[i] != 0) {
//              cout << i << " " << sorted_users_[i] << '\n';
//          }
//      }
//
//      cout << endl;
//
//      cout << "USER POSITIONS" << endl;
//      for (int i = 0; i < user_positions_.size(); ++i) {
//          if (user_positions_[i] != -1) {
//              cout << i << " " << user_positions_[i] << '\n';
//          }
//      }
//
//      cout << endl;
//
    while (position > 0 && page_count > user_page_counts_[sorted_users_[position - 1]]) {
      SwapUsers(position, position - 1);
    }
//
//      cout << "AFTER SORTING" << endl;
//
//
//      cout << "USER PAGE COUNTS" << endl;
//      for (int i = 0; i < user_page_counts_.size(); ++i) {
//          if (user_page_counts_[i] != 0) {
//              cout << i << " " << user_page_counts_[i] << '\n';
//          }
//      }
//
//      cout << endl;
//
//      cout << "SORTED USERS" << endl;
//      for (int i = 0; i < sorted_users_.size(); ++i) {
//          if (sorted_users_[i] != 0) {
//              cout << i << " " << sorted_users_[i] << '\n';
//          }
//      }
//
//      cout << endl;
//
//      cout << "USER POSITIONS" << endl;
//      for (int i = 0; i < user_positions_.size(); ++i) {
//          if (user_positions_[i] != -1) {
//              cout << i << " " << user_positions_[i] << '\n';
//          }
//      }
//
//      cout << endl;
  }

  double Cheer(int user_id) const {
    if (user_page_counts_[user_id] == 0) {
      return 0;
    }
    const int user_count = GetUserCount();

    if (user_count == 1) {
      return 1;
    }
    const int page_count = user_page_counts_[user_id];


    int position = user_positions_[user_id];


    while (position < user_count &&
      user_page_counts_[sorted_users_[position]] == page_count) {
      ++position;
    }
    if (position == user_count) {
//        cout << "ok" << endl;
        return 0;
    }
    // По умолчанию деление целочисленное, поэтому
    // нужно привести числитель к типу double.
    // Простой способ сделать это — умножить его на 1.0.

//    cout << "user id: " << user_id << endl;
//    cout << "user count: " << user_count << endl;
//    cout << "page count: " << page_count << endl;
//
//    cout << endl;
//
//
//    cout << "USER PAGE COUNTS" << endl;
//    for (int i = 0; i < user_page_counts_.size(); ++i) {
//        if (user_page_counts_[i] != 0) {
//            cout << i << " " << user_page_counts_[i] << '\n';
//        }
//    }
//
//    cout << endl;
//
//    cout << "SORTED USERS" << endl;
//    for (int i = 0; i < sorted_users_.size(); ++i) {
//        if (sorted_users_[i] != 0) {
//            cout << i << " " << sorted_users_[i] << '\n';
//        }
//    }
//
//    cout << endl;
//
//      cout << "USER POSITIONS" << endl;
//      for (int i = 0; i < user_positions_.size(); ++i) {
//          if (user_positions_[i] != -1) {
//              cout << i << " " << user_positions_[i] << '\n';
//          }
//      }
//
//      cout << endl;
//
//      cout << "user_count: " << user_count << endl;
//      cout << "position: " << position << endl;
//      cout << "user_count - 1: " << user_count - 1 << endl;

//    for (auto i = 0; i < sorted_users_.size(); ++i) {
//        cout << i << " " << sorted_users_[i] << endl;
//    }
//    cout << endl;

    return (user_count - position) * 1.0 / (user_count - 1);
  }

private:
  // Статическое поле не принадлежит какому-то конкретному
  // объекту класса. По сути это глобальная переменная,
  // в данном случае константная.
  // Будь она публичной, к ней можно было бы обратиться снаружи
  // следующим образом: ReadingManager::MAX_USER_COUNT.
  static const int MAX_USER_COUNT_ = 100'000;

  vector<int> user_page_counts_;
  vector<int> sorted_users_;   // отсортированы по убыванию количества страниц
  vector<int> user_positions_; // позиции в векторе sorted_users_

  int GetUserCount() const { // 1
    return sorted_users_.size();
  }
  void AddUser(int user_id) { // 1
    sorted_users_.push_back(user_id);
    user_positions_[user_id] = sorted_users_.size() - 1;
  }
  void SwapUsers(int lhs_position, int rhs_position) { // 1
    const int lhs_id = sorted_users_[lhs_position];
    const int rhs_id = sorted_users_[rhs_position];
    swap(sorted_users_[lhs_position], sorted_users_[rhs_position]);
    swap(user_positions_[lhs_id], user_positions_[rhs_id]);
  }
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

//    TestRunner tr;
//    TestRead();
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