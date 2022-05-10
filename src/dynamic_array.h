#pragma once
#include <stdexcept>
#include <utility>

namespace stl_complement {
template <typename _Tp> struct dynamic_array {
  using value_type = _Tp;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

  using reference = value_type &;
  using const_reference = const value_type &;

  using pointer = value_type *;
  using const_pointer = const pointer *;

  using iterator = value_type *;
  using const_iterator = const value_type *;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

public:
  explicit dynamic_array(std::size_t size)
      : size_(size), header_(new value_type[size]) {}
  ~dynamic_array() {
    if (header_) {
      delete[] header_;
    }
  }

  dynamic_array(const dynamic_array &rhs) = default;
  dynamic_array &operator=(const dynamic_array &rhs) = default;
  dynamic_array(dynamic_array &&rhs) = default;
  dynamic_array &operator=(dynamic_array &&rhs) = default;

  /* element access */
  const_reference at(std::size_t index) const {

    if (index >= size()) {
      std::__throw_out_of_range_fmt(
          __N("dynamic_array::at: index (which is %zu) "
              ">= size (which is %zu)"),
          index, size());
    }
    return header_[index];
  }
  reference at(std::size_t index) {
    if (index >= size()) {
      std::__throw_out_of_range_fmt(
          __N("dynamic_array::at: index (which is %zu) "
              ">= size (which is %zu)"),
          index, size());
    }
    return header_[index];
  }

  const value_type &operator[](size_t index) const { return header_[index]; }
  value_type &operator[](size_t index) { return header_[index]; }

  reference front() noexcept { return *begin(); }
  const_reference front() const noexcept { return *begin(); }

  reference back() noexcept { return *(end() - 1); }
  const_reference back() const noexcept { return *(end() - 1); }

  pointer data() noexcept { return header_; }
  const_pointer data() const noexcept { return header_; }

  /* iterators */
  iterator begin() noexcept { return iterator(data()); }
  const_iterator begin() const noexcept { return const_iterator(data()); }

  iterator end() noexcept { return iterator(data() + size()); }
  const_iterator end() const noexcept {
    return const_iterator(data() + size());
  }
  reverse_iterator rbegin() noexcept { return reverse_iterator(end()); };
  const_reverse_iterator rbegin() const noexcept {
    return const_reverse_iterator(end());
  };

  reverse_iterator rend() noexcept { return reverse_iterator(begin()); };
  const_reverse_iterator rend() const noexcept {
    return const_reverse_iterator(begin());
  };

  const_iterator cbegin() const noexcept { return begin(); }

  const_iterator cend() const noexcept { return end(); }

  const_reverse_iterator crbegin() const noexcept { return rbegin(); }

  const_reverse_iterator crend() const noexcept { return rend(); }

  /* capacity */
  bool empty() const { return size_ == 0; }
  std::size_t max_size() const { return size(); }
  std::size_t size() const { return size_; }

  /* operation */
  void fill(const value_type &u) { std::fill_n(begin(), size(), u); }

private:
  pointer header_{nullptr};
  std::size_t size_ = 0;
};

// todo complete operator and swap
}; // namespace stl_complement