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
  using const_pointer = const value_type *;

  using iterator = value_type *;
  using const_iterator = const value_type *;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

public:
  explicit dynamic_array(std::size_t size) { allocate(size); }
  ~dynamic_array() { clear(); }

  dynamic_array(const dynamic_array &rhs) { assign(rhs); }
  dynamic_array &operator=(const dynamic_array &rhs) { assign(rhs); }
  
  // todo complete a move-ctor
  // dynamic_array(dynamic_array &&rhs) {
  //   clear();
  //   swap(rhs);
  // }
  // dynamic_array &operator=(dynamic_array &&rhs) {
  //   clear();
  //   swap(rhs);
  // }

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
  const_pointer data() const noexcept { return const_pointer(header_); }

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

  void swap(dynamic_array &rhs) {
    std::swap(header_, rhs.header_);
    std::swap(size_, rhs.size_);
  }

private:
  pointer header_{nullptr};
  std::size_t size_ = 0;

  /* allow new a array of which length is 0, and you must delete it */
  void allocate(std::size_t size) {
    clear();
    size_ = size;
    header_ = new value_type[size];
    return;
  }

  void assign(const dynamic_array &rhs) {
    allocate(rhs.size());
    std::copy(rhs.begin(), rhs.end(), begin());
  }
  void clear() {
    if (header_) {
      delete[] header_;
      header_ = nullptr;
    }
  }
};

template <typename _Tp>
inline bool operator==(const dynamic_array<_Tp> &lhs,
                       const dynamic_array<_Tp> &rhs) {
  return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename _Tp>
inline bool operator!=(const dynamic_array<_Tp> &lhs,
                       const dynamic_array<_Tp> &rhs) {
  return (!operator==<_Tp>(lhs, rhs));
}

// todo complete operator and swap
}; // namespace stl_complement