// pointer_vector.cpp
// Implements a vector that stores and takes ownership of pointers.

#include <iostream>
#include <vector>

template <class T> class PointerVector {
public:
  ~PointerVector() {
    for (auto p : v_) {
      delete p;
    }
  }
  void push_back(T *p) { v_.push_back(p); }
  T *operator[](int i) { return v_[i]; }

  typename std::vector<T *>::iterator begin() { return v_.begin(); }
  typename std::vector<T *>::iterator end() { return v_.end(); }
  typename std::vector<T *>::const_iterator begin() const { return v_.begin(); }
  typename std::vector<T *>::const_iterator end() const { return v_.end(); }

private:
  std::vector<T *> v_;
};

template <class T>
std::ostream &operator<<(std::ostream &os, const PointerVector<T> &pv) {
  bool is_first = true;

  os << "{";
  for (auto p : pv) {
    if (is_first) {
      is_first = false;
    } else {
      os << ", ";
    }
    os << *p;
  }
  return os << "}";
}

int main() {
  PointerVector<int> pv;
  pv.push_back(new int{1});
  pv.push_back(new int{2});
  pv.push_back(new int{3});
  pv.push_back(new int{4});
  std::cout << pv << "\n";
}
