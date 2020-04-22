// managed_pointer.h
// Public interface and private implementation for a managed pointer.

#include <cstddef>
#include <stdexcept>

template <class T> class ManagedPointer {
public:
  ManagedPointer() : data_(nullptr), reference_count_(new std::size_t(1)) {}
  ManagedPointer(T *data) : data_(data), reference_count_(new std::size_t(1)) {}
  ManagedPointer(const ManagedPointer &other)
      : data_(other.data_), reference_count_(other.reference_count_) {
    ++(*reference_count_);
  }
  ManagedPointer &operator=(const ManagedPointer &other);
  ~ManagedPointer();

  void make_unique();

  operator bool() const { return data_; }
  T &operator*() const {
    if (data_) {
      return data_;
    }
    throw std::runtime_error("* called on unbound ManagedPointer");
  }
  T *operator->() const {
    if (data_) {
      return data_;
    }
    throw std::runtime_error("-> called on unbound ManagedPointer");
  }

private:
  T *data_;
  std::size_t *reference_count_;
};

template <class T>
ManagedPointer<T> &ManagedPointer<T>::operator=(const ManagedPointer &other) {
  --(*reference_count_);
  ++(*other.reference_count_);

  if (*reference_count_ == 0) {
    delete data_;
    delete reference_count_;
  }

  data_ = other.data_;
  reference_count_ = other.reference_count_;
  return *this;
}

template <class T> ManagedPointer<T>::~ManagedPointer<T>() {
  --(*reference_count_);
  if (reference_count_ == 0) {
    delete data_;
    delete reference_count_;
  }
}

template <class T> void ManagedPointer<T>::make_unique() {
  if (*reference_count_ != 1) {
    --(*reference_count_);
    data_ = data_ ? clone(data_) : nullptr;
    reference_count_ = new size_t(1);
  }
}

template <class T> T *clone(const T *t) { return t->clone(); }
