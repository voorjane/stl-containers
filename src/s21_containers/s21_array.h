#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_ARRAY_H_

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace s21 {
template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

  array() = default;

  array(std::initializer_list<value_type> const &items) {
    auto iter = items.begin();
    for (std::size_t i = 0; i < N && iter != items.end(); ++i, ++iter) {
      arr_[i] = *iter;
    }
  }

  array(const array &a) {
    for (size_type i = 0; i < N; i++) arr_[i] = a.arr_[i];
  }

  array(array &&a) noexcept { std::move(a.begin(), a.end(), begin()); }

  ~array() = default;

  array &operator=(array &&a) noexcept {
    std::move(a.begin(), a.end(), begin());
    return *this;
  }

  reference at(size_type pos) {
    if (pos >= N) throw std::out_of_range("Index out of range");
    return arr_[pos];
  }

  reference operator[](size_type pos) { return at(pos); }

  const_reference front() { return arr_[0]; }

  const_reference back() { return arr_[N - 1]; }

  iterator data() noexcept { return arr_; }

  iterator begin() noexcept { return &arr_[0]; }
  const_iterator cbegin() const noexcept { return &arr_[0]; }
  iterator end() noexcept { return &arr_[N]; }
  const_iterator cend() const noexcept { return &arr_[N]; }

  bool empty() const noexcept { return N == 0; }

  size_type size() const noexcept { return N; }

  size_type max_size() const noexcept { return N; }

  void swap(array &other) { std::swap_ranges(begin(), end(), other.begin()); }

  void fill(const_reference value) {
    for (std::size_t i = 0; i < N; i++) arr_[i] = value;
  }

 private:
  value_type arr_[N]{};
};
}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_ARRAY_H_
