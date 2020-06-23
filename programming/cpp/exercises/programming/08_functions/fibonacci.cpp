// fibonacci.cpp
// Construct and print a vector of Fibonacci numbers.

#include <iostream>
#include <vector>

std::vector<int> fibonacci_vector(int n);
std::ostream &operator<<(std::ostream &os, const std::vector<int> &v);

int main() {
  std::vector<int> v = fibonacci_vector(10);
  std::cout << v;
}

std::vector<int> fibonacci_vector(int n) {
  std::vector<int> v(n);
  if (n > 0) {
    v[0] = 0;
  }
  if (n > 1) {
    v[1] = 1;
  }

  for (int i = 2; i < n; ++i) {
    v[i] = v[i - 2] + v[i - 1];
  }

  return v;
}

std::ostream &operator<<(std::ostream &os, const std::vector<int> &v) {
  for (std::vector<int>::size_type i = 0; i < v.size(); ++i) {
    os << "v[" << i << "] = " << v[i] << "\n";
  }
  return os;
}
