// fixed_size_vector.cpp
// Implementation of a simple fixed size vector.

#include <iostream>

class FixedSizeVector {
public:
  FixedSizeVector(size_t size) : size_(size), data_{new int[size]} {}
  ~FixedSizeVector() { delete[] data_; }

  size_t size() const { return size_; }

  void _check_bounds(size_t i) const {
    if (i >= size_) {
      throw std::runtime_error("out of bounds of fixed-size vector");
    }
  }

  int get(size_t i) const {
    _check_bounds(i);
    return data_[i];
  }
  void set(size_t i, int x) {
    _check_bounds(i);
    data_[i] = x;
  }

private:
  size_t size_;
  int *data_;
};

int main() {
  size_t size;
  std::cout << "Enter the size of the vector: ";
  std::cin >> size;

  FixedSizeVector v{size};
  std::cout << "\n";
  for (size_t i = 0; i < v.size(); ++i) {
    int x;
    std::cout << "Enter the value at index " << i << ": ";
    std::cin >> x;

    v.set(i, x);
  }

  std::cout << "\nThe contents of the vector are:\n";
  for (size_t i = 0; i < v.size(); ++i) {
    std::cout << "v[" << i << "] = " << v.get(i) << "\n";
  }
}
