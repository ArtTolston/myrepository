#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class ReadingManager {
public:
  ReadingManager()
      : user_page_counts_(MAX_USER_COUNT_ + 1, 0),
        page_rate_(MAX_PAGE_COUNT + 1, 0), number_of_users_(0) {}

  void Read(const int& user_id, const int& page_count) {
    if(user_page_counts_[user_id] == 0) {
        ++number_of_users_;
        for(int i = page_count + 1; i <= MAX_PAGE_COUNT; i++)
            ++page_rate_[i];
    } else {
        for(int i = user_page_counts_[user_id] + 1; i <= page_count; i++)
            --page_rate_[i];
    }
    user_page_counts_[user_id] = page_count;
  }

  double Cheer(const int& user_id) const {
     if(user_page_counts_[user_id] == 0)
        return 0;
     if(number_of_users_ == 1) {
        return 1;
     }
     int num = page_rate_[user_page_counts_[user_id]];
     return num * 1.0 / (number_of_users_ - 1);
  }

private:
  // Статическое поле не принадлежит какому-то конкретному
  // объекту класса. По сути это глобальная переменная,
  // в данном случае константная.
  // Будь она публичной, к ней можно было бы обратиться снаружи
  // следующим образом: ReadingManager::MAX_USER_COUNT.
  static const int MAX_PAGE_COUNT = 1000;
  static const int MAX_USER_COUNT_ = 100'000;

  vector<int> user_page_counts_;
  vector<int> page_rate_;

  int number_of_users_;
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
