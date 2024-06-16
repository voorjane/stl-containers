#ifndef CPP2_S21_CONTAINERS_1_S21_VECTOR_H
#define CPP2_S21_CONTAINERS_1_S21_VECTOR_H

#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <utility>
// #include <algorithm>

namespace s21 {
template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using pointer = T *;
  using const_reference = const value_type &;
  using size_type = std::size_t;

 private:
  class VectorIterator {
   public:
    explicit VectorIterator(pointer ptr) : ptr_(ptr) {}

    reference operator*() const noexcept { return *ptr_; }
    value_type *operator->() const noexcept { return ptr_; }

    bool operator!=(const VectorIterator &rhs) const noexcept {
      return ptr_ != rhs.ptr_;
    }
    bool operator==(const VectorIterator &rhs) const noexcept {
      return ptr_ == rhs.ptr_;
    }

    bool operator<(const VectorIterator &rhs) const noexcept {
      return ptr_ < rhs.ptr_;
    }
    bool operator<=(const VectorIterator &rhs) const noexcept {
      return ptr_ <= rhs.ptr_;
    }
    bool operator>(const VectorIterator &rhs) const noexcept {
      return ptr_ > rhs.ptr_;
    }
    bool operator>=(const VectorIterator &rhs) const noexcept {
      return ptr_ >= rhs.ptr_;
    }

    VectorIterator operator++(int) noexcept {
      VectorIterator temp = *this;
      ++ptr_;
      return temp;
    }
    VectorIterator &operator++() noexcept {
      ++ptr_;
      return *this;
    }
    VectorIterator operator--(int) noexcept {
      VectorIterator temp = *this;
      --ptr_;
      return temp;
    }
    VectorIterator &operator--() noexcept {
      --ptr_;
      return *this;
    }

   private:
    pointer ptr_ = nullptr;
  };

 public:
  using iterator = VectorIterator;
  using const_iterator = const VectorIterator;

  vector() : data_(nullptr), size_(0), capacity_(0){};

  explicit vector(size_type n)
      : data_(new value_type[n]), size_(n), capacity_(n){};

  vector(std::initializer_list<value_type> const &items)
      : data_(nullptr), size_(0), capacity_() {
    reserve(items.size());
    for (value_type item : items) push_back(item);
  }

  vector(const vector &v) : size_(v.size_), capacity_(v.size_) {
    data_ = new value_type[capacity_];
    for (size_type i = 0; i < size_; ++i)
      new (&data_[i]) value_type(v.data_[i]);
  }

  vector(vector &&v) noexcept
      : data_(v.data_), size_(v.size_), capacity_(v.capacity_) {
    v.data_ = nullptr;
    v.size_ = v.capacity_ = 0;
  }

  ~vector() noexcept {
    delete[] data_;
    data_ = nullptr;
    size_ = capacity_ = 0;
  }

  vector &operator=(vector &&v) noexcept {
    if (this != &v) {
      delete[] data_;
      data_ = v.data_;
      size_ = v.size_;
      capacity_ = v.capacity_;

      v.data_ = nullptr;
      v.size_ = v.capacity_ = 0;
    }
    return *this;
  }

  reference at(size_type pos) const {
    if (pos >= this->size_) throw std::out_of_range("Index out of bounds");
    return data_[pos];
  }

  reference operator[](size_type pos) { return at(pos); }
  const_reference front() noexcept { return data_[0]; }
  const_reference back() noexcept { return data_[size_ - 1]; }
  pointer data() noexcept { return data_; }

  iterator begin() noexcept { return iterator(data_); }
  iterator end() noexcept { return iterator(data_ + size_); }

  bool empty() const noexcept { return size_ == 0; }
  size_type size() const noexcept { return size_; }
  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
  }

  void reserve(size_type size) {
    if (size > max_size())
      throw std::length_error("Size is bigger than max size");
    if (size <= capacity_) return;

    value_type *new_data = new value_type[size];
    try {
      std::copy(data_, data_ + size_, new_data);
    } catch (...) {
      delete[] new_data;
      throw;
    }

    delete[] data_;
    data_ = new_data;
    capacity_ = size;
  }

  size_type capacity() const noexcept { return capacity_; }

  void shrink_to_fit() noexcept {
    if (size_ == capacity_) return;
    if (size_ == 0) {
      delete[] data_;
      data_ = nullptr;
      capacity_ = 0;
    } else {
      value_type *new_data = new value_type[size_];
      for (size_type i = 0; i < size_; ++i) new_data[i] = std::move(data_[i]);

      delete[] data_;
      data_ = new_data;
      capacity_ = size_;
    }
  }

  void clear() noexcept { size_ = 0; }

  void insert(iterator pos, const_reference value) noexcept {
    if (size_ >= capacity_) {
      size_type new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
      reserve(new_capacity);
    }

    size_type index = 0;
    iterator it = begin();
    while (it <= pos) {
      ++it;
      ++index;
    }

    for (size_type i = size_; i > index; --i)
      new (&data_[i]) value_type(std::move(data_[i - 1]));

    new (&data_[index]) value_type(value);
    ++size_;
  }

  void erase(iterator pos) {
    size_type index = 0;
    iterator it = begin();
    while (it != pos) {
      ++it;
      ++index;
    }

    if (index >= size_) throw std::out_of_range("Index out of bounds");

    for (size_type i = index; i < size_ - 1; ++i)
      data_[i] = std::move(data_[i + 1]);

    data_[size_ - 1].~value_type();
    --size_;
  }

  void push_back(const_reference value) noexcept {
    if (size_ >= capacity_) {
      size_type new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
      reserve(new_capacity);
    }
    data_[size_] = value;
    ++size_;
  }

  void pop_back() noexcept {
    if (size_ > 0) {
      data_[size_ - 1].~value_type();
      --size_;
    }
  }

  void swap(vector &other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    (this->push_back(std::forward<Args>(args)), ...);
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    iterator iter(pos);
    for (auto elem : {std::forward<Args>(args)...}) insert(iter, elem);
    return iter--;
  }

 private:
  value_type *data_;
  size_type size_;
  size_type capacity_;
};
}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_1_S21_VECTOR_H
