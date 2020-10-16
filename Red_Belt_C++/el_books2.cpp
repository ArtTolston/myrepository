#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class ReadingManager {
public:
    Read(const int& user_id, const int& page_number) {
        user_to_page[user_id] = page_number;
        page_to_user[page_number] = user_id;
    }
    double Cheer(const int& user_id) {
        if(user_to_page.count(user_id) == 0)
            return 0.0;
        const int page__for_user = user_to_page[user_id];
        if(prev(end(page_to_user)) -> second == user_id)
            return 1.0;

    }
private:
    map<int ,int> user_to_page;
    map<int ,int> page_to_user;
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
