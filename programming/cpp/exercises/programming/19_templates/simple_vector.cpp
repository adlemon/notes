// simple_vector.cpp
// Simple implementation of a vector.

#include <iostream>

template <class T> class SimpleVector {
public:
  SimpleVector() : size_(0), capacity_(0), data_(nullptr) {}
  SimpleVector(const SimpleVector &other)
      : size_(other.size_), capacity_(size_), data_(new T[capacity_]) {
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = other.data_[i];
    }
  }
  SimpleVector &operator=(const SimpleVector &other) {
    if (this == &other) {
      return;
    }

    size_ = other.size_;
    capacity_ = size_;
    delete[] data_;
    data_ = new T[capacity_];
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = other.data_[i];
    }

    return *this;
  }
  SimpleVector(SimpleVector &&other) {
    if (this == &other) {
      return;
    }

    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = other.data_;

    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
  }
  SimpleVector &operator=(const SimpleVector &&other) {
    if (this == &other) {
      return;
    }

    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = other.data_;

    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
  }
  SimpleVector(size_t n, T value)
      : size_(n), capacity_(size_), data_(new T[capacity_]) {
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = value;
    }
  }
  ~SimpleVector() { delete[] data_; }

  T operator[](size_t i) const { return data_[i]; }
  size_t size() const { return size_; }

  void push_back(T value) {
    if (size_ == capacity_) {
      capacity_ = (capacity_ == 0) ? 1 : 2 * capacity_;
      T *newdata = new T[capacity_];
      for (size_t i = 0; i < size_; ++i) {
        newdata[i] = data_[i];
      }
      delete[] data_;
      data_ = newdata;
    }

    data_[size_] = value;
    ++size_;
  }

private:
  size_t size_;
  size_t capacity_;
  T *data_;
};

int main() {
  SimpleVector<int> v(5, 0);
  for (int i = 1; i <= 10; ++i) {
    v.push_back(i);
  }

  std::cout << "{";
  for (size_t i = 0; i < v.size(); ++i) {
    if (i > 0) {
      std::cout << ", ";
    }
    std::cout << v[i];
  }
  std::cout << "}\n";
}
