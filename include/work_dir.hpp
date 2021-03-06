// Copyright 2022 roflanpotsan l1sZ@ya.ru
#ifndef INCLUDE_WORK_DIR_HPP_
#define INCLUDE_WORK_DIR_HPP_
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <unordered_map>
#include <utility>
template <class Key, class T, class Hash = std::hash<Key>,
          class EqualKey = std::equal_to<Key>>  // Hash = hash_func, EqualKey =
                                                // check whether items
                                                // with identical hash are same
class unordered_map {
  std::list<std::pair<Key, T>> *hash_table;
  size_t table_size = 0, el_count = 0;
  void rehash() {
    size_t new_size = table_size * 2;
    auto *new_table = new std::list<std::pair<Key, T>>[new_size + 1];
    for (size_t i = 0; i <= new_size; i++) {
      new_table[i] = std::list<std::pair<Key, T>>();
    }
    for (size_t i = 0; i < table_size; i++) {
      for (const auto &value : hash_table[i]) {
        new_table[Hash{}(value.first) % new_size].push_back(value);
      }
    }
    delete[] hash_table;
    hash_table = new_table;
    table_size = new_size;
  }

 public:
  class iterator {
    typename std::list<std::pair<Key, T>>::iterator::pointer ptr;
    std::list<std::pair<Key, T>> *array, *begin;
    size_t max_size = 0;

   public:
    using difference_type = std::ptrdiff_t;
    using value_type = std::pair<Key, T>;
    using pointer = const std::pair<Key, T> *;
    using reference = const std::pair<Key, T> &;
    using iterator_category = std::forward_iterator_tag;
    explicit iterator(std::list<std::pair<Key, T>> *new_begin,
                      std::list<std::pair<Key, T>> *arr, size_t new_size) {
      begin = new_begin;
      array = arr;
      max_size = new_size;
      if (max_size == 0) {
        ptr = nullptr;
      } else {
        if ((*array).empty() && array != begin + max_size) {
          while (std::next(array) != begin + max_size &&
                 (*std::next(array)).empty()) {
            array = std::next(array);
          }
          array = std::next(array);
        }
      }
      if (array == begin + max_size) {
        if ((*array).empty())
          ptr = nullptr;
        else
          ptr = &(*((*array).begin()));
      } else {
        ptr = &(*((*array).begin()));
      }
    }

    ~iterator() = default;

    std::pair<Key, T> operator*() { return *ptr; }

    iterator &operator++() {
      if (ptr == nullptr) {  //????????, ???? ??????????????
        ++ptr;
      } else {
        while (std::next(array) != begin + max_size &&
               (*std::next(array)).empty()) {
          array = std::next(array);
        }
        array = std::next(array);
        if (array == begin + max_size) {
          if ((*array).empty()) {
            ptr = nullptr;
          } else {
            ptr = &(*((*array).begin()));
          }
        } else {
          ptr = &(*((*array).begin()));
        }
      }
      return *this;
    }

    const iterator operator++(int) {
      iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    friend bool operator==(const iterator &a, const iterator &b) {
      return a.ptr == b.ptr;
    }

    friend bool operator!=(const iterator &a, const iterator &b) {
      return a.ptr != b.ptr;
    }
  };

  unordered_map() { hash_table = nullptr; }

  unordered_map(std::initializer_list<std::pair<Key, T>> const &values) {
    table_size = values.size();
    hash_table = new std::list<std::pair<Key, T>>[table_size + 1];
    for (const auto &value : values) {
      this->insert(value);
    }
  }

  unordered_map(const unordered_map &values) {
    table_size = values.capacity();
    hash_table = new std::list<std::pair<Key, T>>[table_size + 1];
    for (auto i : values) {
      std::pair<Key, T> b = i;
      this->insert(b);
    }
  }

  ~unordered_map() {
    delete[] hash_table;
    table_size = 0;
    el_count = 0;
  }

  unordered_map &operator=(const unordered_map<Key, T> &values) {
    table_size = values.capacity();
    el_count = 0;
    delete[] hash_table;
    hash_table = new std::list<std::pair<Key, T>>[table_size + 1];
    for (auto i = values.begin(); i != values.end(); ++i) {
      this->insert(*i);
    }
    return *this;
  }
  unordered_map &operator=(std::initializer_list<std::pair<Key, T>> values) {
    table_size = values.size();
    el_count = 0;
    delete[] hash_table;
    hash_table = new std::list<std::pair<Key, T>>[table_size + 1];
    for (const auto &value : values) {
      this->insert(value);
    }
    return *this;
  }
  bool operator==(const unordered_map<Key, T> &new_set) {
    for (auto i = new_set.begin(); i != new_set.end(); ++i) {
      if (!(this->has(*i))) return false;
    }
    return true;
  }

  void insert(const std::pair<Key, T> &value) {
    if (table_size == 0) {
      hash_table = new std::list<std::pair<Key, T>>[2];
      table_size++;
      hash_table[0].push_back(value);
      el_count++;
    } else {
      if (this->has(value)) {
        return;
      }
      if (el_count == table_size) {
        rehash();
      }
      hash_table[std::hash<Key>()(value.first) % table_size].push_back(value);
      el_count++;
    }
  }

  void insert(std::initializer_list<std::pair<Key, T>> values) {
    for (const auto &value : values) {
      if (table_size == 0) {
        hash_table = new std::list<std::pair<Key, T>>[values.size() + 1];
        table_size++;
        hash_table[0].push_back(value);
        el_count++;
      } else {
        //        if (this->has(value)) {
        //          value.second++;
        //          return;
        //        }
        if (el_count == table_size) {
          rehash();
        }
        hash_table[std::hash<Key>()(value.first) % table_size].push_back(value);
        el_count++;
      }
    }
  }

  const std::pair<Key, T> operator[](const std::pair<Key, T> &value) {
    if (!hash_table[std::hash<Key>()(value.first) % table_size].empty()) {
      for (auto el : hash_table[std::hash<Key>()(value.first) % table_size]) {
        if (EqualKey{}(el.first, value.first)) {
          return std::make_pair(el.first, el.second);
        }
      }
    }
    this->insert(value);
    // return std::make_pair(value.first, value.second);
    return value;
  }

  const std::pair<Key, T> &at(const std::pair<Key, T> &value) const {
    if (!hash_table[std::hash<Key>()(value.first) % table_size].empty()) {
      for (auto el : hash_table[std::hash<Key>()(value.first) % table_size]) {
        if (EqualKey{}(el.first, value.first)) {
          return value;
        }
      }
    }
    throw std::exception();
  }

  bool has(const std::pair<Key, T> &value) const {
    if (!hash_table[std::hash<Key>()(value.first) % table_size].empty()) {
      for (auto el : hash_table[std::hash<Key>()(value.first) % table_size]) {
        if (EqualKey{}(el.first, value.first)) {
          return true;
        }
      }
    }
    return false;
  }

  void clear() {
    delete[] hash_table;
    hash_table = nullptr;
    table_size = 0;
    el_count = 0;
  }

  [[nodiscard]] size_t size() const { return el_count; }
  [[nodiscard]] size_t capacity() const { return table_size; }
  bool empty() { return el_count == 0; }

  void erase(const std::pair<Key, T> &value) {
    if (this->has(value)) {
      hash_table[Hash{}(value.first) % table_size].clear();
      el_count--;
    }
  }

  void erase(iterator pos) {
    if (this->has(*pos)) {
      hash_table[Hash{}((*pos).first) % table_size].clear();
      el_count--;
    }
  }

  iterator begin() const {
    return iterator(hash_table, hash_table, table_size);
  }
  iterator end() const {
    return iterator(hash_table, hash_table + table_size, table_size);
  }

  iterator find(const std::pair<Key, T> &value) {
    if (this->has(value)) {
      iterator it(hash_table,
                  hash_table + std::hash<Key>()(value.first) % table_size,
                  table_size);
      while (!std::equal_to<Key>{}((*(it)).first, value.first)) ++it;
      return it;
    } else {
      return this->end();
    }
  }
};

template <class T, class Key>
void swap(unordered_map<T, Key> &a, unordered_map<T, Key> &b) {
  unordered_map<T, Key> temp = a;
  a = std::move(b);
  b = std::move(temp);
}
template <class T, class Key>
bool operator==(const unordered_map<T, Key> &new_set,
                const unordered_map<T, Key> &old_set) {
  for (auto i = new_set.begin(); i != new_set.end(); ++i) {
    if (!(old_set.has(*i))) return false;
  }
  return true;
}

template <class T, class Key>
bool operator!=(const unordered_map<Key, T> &new_set,
                const unordered_map<Key, T> &old_set) {
  return !(new_set == old_set);
}

#endif  // INCLUDE_WORK_DIR_HPP_
