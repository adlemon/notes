// managed_pointer_counter.cpp
// Define a counter class and use it to implement a managed pointer.

#include <cstddef>
#include <iostream>
#include <stdexcept>

class Counter {
public:
  Counter() : count_(0) {}
  std::size_t count() const { return count_; }
  std::size_t increment() {
    ++count_;
    return count_;
  }
  std::size_t decrement() {
    --count_;
    return count_;
  }

private:
  std::size_t count_;
};

template <class T> class ManagedPointer {
public:
  ManagedPointer() : counter_(new Counter()), data_(nullptr) {}
  ManagedPointer(T *t) : counter_(new Counter()), data_(t) {
    counter_->increment();
  }
  ManagedPointer(const ManagedPointer &other)
      : counter_(other.counter_), data_(other.data_) {
    counter_->increment();
  }
  ManagedPointer &operator=(const ManagedPointer &other);
  ~ManagedPointer();

  operator bool() const { return data_; }
  T &operator*() const;
  T *operator->() const;

  void make_unique() {
    if (counter_->count() != 1) {
      counter_->decrement();
      counter_ = new Counter();
      counter_->increment();
      data_ = data_ ? clone(data_) : nullptr;
    }
  }

private:
  Counter *counter_;
  T *data_;
};

template <class T>
ManagedPointer<T> &ManagedPointer<T>::operator=(const ManagedPointer &other) {
  other.counter_->increment();
  counter_->decrement();

  if (counter_->count() == 0) {
    delete counter_;
    delete data_;
  }

  counter_ = other.counter_;
  data_ = other.data_;

  return *this;
}

template <class T> ManagedPointer<T>::~ManagedPointer() {
  counter_->decrement();
  if (counter_->count() == 0) {
    delete counter_;
    delete data_;
  }
}

template <class T> T &ManagedPointer<T>::operator*() const {
  if (data_) {
    return *data_;
  }
  throw std::runtime_error("* called on unbound ManagedPointer");
}

template <class T> T *ManagedPointer<T>::operator->() const {
  if (data_) {
    return data_;
  }
  throw std::runtime_error("-> called on unbound ManagedPointer");
}

template <class T> T *clone(const T *data) { return data->clone(); }

template <> int inline *clone(const int *data) { return new int(*data); }

int main() {
  ManagedPointer<int> p1(new int(22));
  std::cout << "*p1 = " << *p1 << "\n";

  {
    ManagedPointer<int> p2(p1);
    std::cout << "*p2 = " << *p2 << "\n";
    *p2 = 23;
  }

  std::cout << "*p1 = " << *p1 << "\n";
}
