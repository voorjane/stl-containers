#ifndef CPP2_S21_CONTAINERS_1_S21_SET_H
#define CPP2_S21_CONTAINERS_1_S21_SET_H

#include <initializer_list>
#include <limits>

#include "../binary_tree/s21_binary_tree.h"
#include "s21_vector.h"

namespace s21 {
template <typename Key>
class set {
 public:
  using key_type = Key;
  using value_type = key_type;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename RedBlackTree<value_type>::iterator;
  using const_iterator = typename RedBlackTree<value_type>::const_iterator;
  using size_type = std::size_t;

  set() noexcept = default;

  set(std::initializer_list<value_type> const &items) {
    for (const auto &item : items) tree_.insert(item);
  }

  set(const set &s) {
    for (const auto &pair : s) tree_.insert(pair);
  }

  set(set &&s) noexcept {
    tree_.clear();
    swap(s);
  }

  ~set() noexcept = default;

  set &operator=(set &&s) noexcept {
    if (this != &s) tree_ = std::move(s.tree_);
    return *this;
  }

  iterator begin() const noexcept { return tree_.begin(); }
  iterator end() const noexcept { return tree_.end(); }

  bool empty() const noexcept { return tree_.empty(); }
  size_type size() const noexcept { return tree_.size(); }
  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(value_type);
  }

  void clear() noexcept { tree_.clear(); }

  std::pair<iterator, bool> insert(const value_type &value) noexcept {
    iterator it = find(value);

    if (it != end()) return {it, false};
    return tree_.insert(value);
  }

  void erase(iterator pos) noexcept {
    iterator it = find(*pos);
    if (it != end()) tree_.erase(*pos);
  }

  void swap(set &other) noexcept { tree_.swap(other.tree_); }

  void merge(set &other) noexcept {
    for (const auto &pair : other) tree_.insert(pair);
    other.clear();
  }

  iterator find(const Key &key) const noexcept {
    iterator it = begin();

    while (it != end()) {
      if (*it == key) return it;
      ++it;
    }
    return end();
  }

  bool contains(const Key &key) const noexcept {
    iterator it = find(key);
    if (it != end()) return true;
    return false;
  }

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    s21::vector<std::pair<iterator, bool>> results;
    results.reserve(sizeof...(Args));

    ((results.push_back(insert(std::forward<Args>(args)))), ...);

    return results;
  }

 private:
  RedBlackTree<value_type> tree_;
};
}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_1_S21_SET_H
