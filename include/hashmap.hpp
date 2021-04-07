#include <functional>
#include <stdexcept>
#include <utility>
#include <vector>

template <typename Key, typename Value, typename Iter, typename ValidityIter>
struct HashMapIter {
  Iter current;
  Iter end;
  ValidityIter validity;

  HashMapIter(Iter current, Iter end, ValidityIter validity)
      : current(current), end(end), validity(validity) {}

  auto &operator*() { return *current; }

  auto *operator->() { return current.operator->(); }

  HashMapIter &operator++() {
    if (current == end) {
      return *this;
    }
    do {
      current++;
      validity++;
    } while (!*validity && current != end);
    return *this;
  }

  bool operator==(const HashMapIter &other) { return current == other.current; }

  bool operator!=(const HashMapIter &other) { return current != other.current; }
};

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class HashMap {

public:
  HashMap(size_t size)
      : table(size), validity(size, false), fullness(0), size(size) {}
  HashMap() : table(2), validity(2), fullness(0), size(2) {}

  auto begin() {
    size_t i = 0;
    for (; i < table.size() && !validity[i]; i++)
      ;
    return HashMapIter<Key, Value, typename decltype(HashMap::table)::iterator,
                       typename decltype(HashMap::validity)::iterator>(
        table.begin() + i, table.end(), validity.begin() + i);
  }
  auto end() {
    return HashMapIter<Key, Value, typename decltype(HashMap::table)::iterator,
                       typename decltype(HashMap::validity)::iterator>(
        table.end(), table.end(), validity.end());
  }

  template <typename K, typename V>
  std::pair<Key, Value> &insert(K &&key, V &&value) {
    if (fullness + 1 > table.size() / 2) {
      resize_table();
    } else {
      size_t index = hash(key) % table.size();
      for (size_t i = 0; i < 3; i++) {
        auto cur_index = (index + i) % table.size();
        if (!validity[cur_index] || table[cur_index].first == key) {
          fullness++;
          validity[cur_index] = true;
          return table[cur_index] = {key, value};
        }
      }
      resize_table();
    }
    return insert(key, value);
  }

  template <typename K> Value &get(K &&key) {
    size_t index = hash(key) % table.size();
    for (size_t i = 0; i < 3; i++) {
      auto cur_index = (index + i) % table.size();
      if (validity[cur_index] && table[cur_index].first == key)
        return table[cur_index].second;
    }
    throw std::runtime_error("No souch key");
  }

  template <typename K> bool remove(K &&key) {
    size_t index = hash(key) % table.size();
    for (size_t i = 0; i < 3; i++) {
      auto cur_index = (index + i) % table.size();
      if (validity[cur_index] && table[cur_index].first == key) {
        fullness--;
        validity[cur_index] = false;
        return true;
      }
    }
    return false;
  }

private:
  void resize_table() {
    auto old_table = table;
    auto old_validity = validity;

    size = size * 2;
    table = std::vector<std::pair<Key, Value>>(size);
    validity = std::vector<char>(size, false);

    for (int i = 0; i < old_table.size(); i++) {
      if (old_validity[i]) {
        insert(old_table[i].first, old_table[i].second);
      }
    }
  }

  size_t size;
  size_t fullness;
  Hash hash;
  std::vector<std::pair<Key, Value>> table;
  std::vector<char> validity;
};