// simple_vector.cpp
// A simple implementation of a vector.

#include <algorithm>
#include <iostream>
#include <memory>

template <class T> class SimpleVector {
public:
  typedef T *iterator;
  typedef const T *const_iterator;
  typedef size_t size_type;
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;

  SimpleVector() { create(); }
  explicit SimpleVector(size_type n, const T &t = T()) { create(n, t); }
  SimpleVector(const SimpleVector &v) { create(v.begin(), v.end()); }
  SimpleVector(const_iterator b, const_iterator e) { create(b, e); }
  SimpleVector &operator=(const SimpleVector &other);
  ~SimpleVector() { uncreate(); }

  T &operator[](size_type i) { return begin_[i]; }
  const T &operator[](size_type i) const { return begin_[i]; }

  void push_back(const T &t) {
    if (end_ == buffer_end_) {
      grow();
    }
    unchecked_append(t);
  }

  size_type size() const { return end_ - begin_; }
  size_type capacity() const { return buffer_end_ - begin_; }

  iterator begin() { return begin_; }
  const_iterator begin() const { return begin_; }

  iterator end() { return end_; }
  const_iterator end() const { return end_; }

  void clear();
  void erase(const_iterator pos);
  void erase(const_iterator first, const_iterator last);

  void assign(T arr[], size_t n);

private:
  void create();
  void create(size_type n, const T &t);
  void create(const_iterator begin, const_iterator end);
  void uncreate();
  void grow();
  void unchecked_append(const T &t);

  iterator begin_;
  iterator end_;
  iterator buffer_end_;
  std::allocator<T> allocator_;
};

template <class T>
SimpleVector<T> &SimpleVector<T>::operator=(const SimpleVector &other) {
  if (&other != this) {
    uncreate();
    create(other.begin(), other.end());
  }
  return *this;
}

template <class T> void SimpleVector<T>::create() {
  begin_ = end_ = buffer_end_ = nullptr;
}

template <class T> void SimpleVector<T>::create(size_type n, const T &val) {
  begin_ = allocator_.allocate(n);
  end_ = buffer_end_ = begin_ + n;
  std::uninitialized_fill(begin_, buffer_end_, val);
}

template <class T>
void SimpleVector<T>::create(const_iterator i, const_iterator j) {
  begin_ = allocator_.allocate(j - i);
  end_ = buffer_end_ = std::uninitialized_copy(i, j, begin_);
}

template <class T> void SimpleVector<T>::uncreate() {
  if (begin_) {
    iterator it = end_;
    while (it != begin_) {
      --it;
      allocator_.destroy(it);
    }
    allocator_.deallocate(begin_, buffer_end_ - begin_);
  }
  begin_ = end_ = buffer_end_ = nullptr;
}

template <class T> void SimpleVector<T>::grow() {
  size_type new_size = std::max(2 * (buffer_end_ - begin_), std::ptrdiff_t(1));

  iterator new_begin_ = allocator_.allocate(new_size);
  iterator new_end_ = std::uninitialized_copy(begin_, end_, new_begin_);

  uncreate();

  begin_ = new_begin_;
  end_ = new_end_;
  buffer_end_ = begin_ + new_size;
}

template <class T> void SimpleVector<T>::unchecked_append(const T &val) {
  allocator_.construct(end_, val);
  ++end_;
}

template <class T> void SimpleVector<T>::clear() {
  iterator it = end_;
  while (it != begin_) {
    --it;
    allocator_.destroy(it);
  }
  end_ = begin_;
}

template <class T> void SimpleVector<T>::erase(const_iterator pos) {
  const_iterator it = pos;
  while (it != end_) {
    allocator_.destroy(it);
    allocator_.construct(it, it[1]);
    ++it;
  }
  allocator_.destroy(end_);
  --end_;
}

template <class T>
void SimpleVector<T>::erase(const_iterator first, const_iterator last) {
  const_iterator it = first, jt = last;
  while (it != last) {
    allocator_.destroy(it);
    allocator_.construct(it, *jt);
    allocator_.destroy(jt);
    ++it;
    ++jt;
  }
  end_ -= (last - first);
}

template <class T> void SimpleVector<T>::assign(T arr[], size_t n) {
  clear();
  for (size_t i = 0; i < n; ++i) {
    push_back(arr[i]);
  }
}

enum class VectorAction {
  Invalid,
  Print,
  PushBack,
  Update,
  Erase,
  EraseRange,
  Clear,
  Quit
};

VectorAction get_action();
void simple_vector_print(const SimpleVector<int> &v);
void simple_vector_push_back(SimpleVector<int> &v);
void simple_vector_update(SimpleVector<int> &v);
void simple_vector_erase(SimpleVector<int> &v);
void simple_vector_erase_range(SimpleVector<int> &v);
void simple_vector_clear(SimpleVector<int> &v);
