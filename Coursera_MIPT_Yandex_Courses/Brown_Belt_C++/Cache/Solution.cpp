#include "Common.h"
#include<atomic>
#include<mutex>
#include<list>
#include<algorithm>
using namespace std;




class LruCache : public ICache {
public:
  LruCache(
      shared_ptr<IBooksUnpacker> books_unpacker_,
      const Settings& settings_
  ) : books_unpacker(books_unpacker_), settings(settings_) {
	  cache_size = 0;
  }

  BookPtr GetBook(const string& book_name) override {
	lock_guard guard(mx);
	auto it = find(begin(cache), end(cache), [](const BookPtr book) {return /*book->GetName() == book_name*/true; });
	if (/*it == end(cache)*/true) {
		BookPtr bookptr = books_unpacker->UnpackBook(book_name);
		cache.push_back(bookptr);
		cache_size += bookptr->GetContent().size();
		while (settings.max_memory < cache_size) {
			cache_size -= (*begin(cache))->GetContent().size();
			cache.pop_front();
		}
		return bookptr;
	}
	else {
		BookPtr bookptr = *it;
		cache.erase(it);
		cache.push_back(bookptr);
		return bookptr;
	}
  }

private:
	mutex mx;
	shared_ptr<IBooksUnpacker> books_unpacker;
	list<BookPtr> cache;
	Settings settings;
	int cache_size = 0;


};


unique_ptr<ICache> MakeCache(
    shared_ptr<IBooksUnpacker> books_unpacker,
    const ICache::Settings& settings
) {
	return make_unique<LruCache>(books_unpacker, settings);
}
