#ifndef _MANAGED_POINTER_H
#define _MANAGED_POINTER_H
// managed_pointer.cpp
// A class to manage pointers.

#include <cstddef>
#include <stdexcept>
#include <vector>

template <class T> class ManagedPointer {
public:
  ManagedPointer() : pointer_(nullptr), count_(new std::size_t(1)) {}
  ManagedPointer(T *t) : pointer_(t), count_(new std::size_t(1)) {}
  ManagedPointer(const ManagedPointer &other)
      : pointer_(other.pointer_), count_(other.count_) {
    ++(*count_);
  }
  ManagedPointer &operator=(const ManagedPointer &other);
  ~ManagedPointer();

  operator bool() const { return pointer_; }
  T &operator*() const;
  T *operator->() const;

  void make_unique() {
    if (*count_ != 1) {
      --(*count_);
      pointer_ = pointer_ ? clone(pointer_) : nullptr;
      count_ = new std::size_t(1);
    }
  }

private:
  T *pointer_;
  std::size_t *count_;
};

template <class T>
ManagedPointer<T> &ManagedPointer<T>::operator=(const ManagedPointer &other) {
  ++(*(other.count_));
  --(*count_);
  if (*count_ == 0) {
    delete pointer_;
    delete count_;
  }

  pointer_ = other.pointer_;
  count_ = other.count_;

  return *this;
}

template <class T> ManagedPointer<T>::~ManagedPointer() {
  --(*count_);
  if (*count_ == 0) {
    delete pointer_;
    delete count_;
  }
}

template <class T> T &ManagedPointer<T>::operator*() const {
  if (pointer_) {
    return *pointer_;
  }
  throw std::runtime_error("* called on unbound ManagedPointer");
}

template <class T> T *ManagedPointer<T>::operator->() const {
  if (pointer_) {
    return pointer_;
  }
  throw std::runtime_error("-> called on unbound ManagedPointer");
}

template <class T> T *clone(const T *pointer_) { return pointer_->clone(); }

template <> int inline *clone(const int *pointer_) {
  return new int(*pointer_);
}

#endif
