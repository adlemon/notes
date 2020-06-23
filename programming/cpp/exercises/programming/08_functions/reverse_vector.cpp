// reverse_vector.cpp
// Reverses a vector in place.

#include <iostream>
#include <vector>

std::vector<int> range(int begin, int end);
void swap(int &x, int &y);
void reverse(std::vector<int> &v);
std::ostream &operator<<(std::ostream &os, const std::vector<int> &v);

int main() {
  std::vector<int> v = range(0, 10);
  std::cout << "Original:\n" << v;

  reverse(v);
  std::cout << "Reversed:\n" << v;
}

std::vector<int> range(int begin, int end) {
  std::vector<int> v;
  for (int i = begin; i < end; ++i) {
    v.push_back(i);
  }
  return v;
}

void swap(int &x, int &y) {
  int tmp = x;
  x = y;
  y = tmp;
}

void reverse(std::vector<int> &v) {
  for (std::vector<int>::size_type i = 0; i < v.size() / 2; ++i) {
    swap(v[i], v[v.size() - i - 1]);
  }
}

std::ostream &operator<<(std::ostream &os, const std::vector<int> &v) {
  for (std::vector<int>::size_type i = 0; i < v.size(); ++i) {
    os << "v[" << i << "] = " << v[i] << "\n";
  }
  return os;
}
