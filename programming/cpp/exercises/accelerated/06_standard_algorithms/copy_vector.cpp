// copy_vector.cpp
// Copy data from one vector to another.

#include <iostream>
#include <vector>

void print(std::ostream& out, std::vector<int> v);

int main() {
  std::vector<int> u(10, 100);

  std::vector<int> v1(u.size(), 0);
  std::copy(u.begin(), u.end(), v1.begin());
  std::cout << "v1 = ";
  print(std::cout, v1);
  std::cout << "\n";

  std::vector<int> v2;
  std::copy(u.begin(), u.end(), std::back_inserter(v2));
  std::cout << "v2 = ";
  print(std::cout, v2);
  std::cout << "\n";
}

void print(std::ostream& out, std::vector<int> v) {
  out << "[";
  
  for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
    if (it != v.begin()) {
      out << ", ";
    }
    out << *it;
  }

  out << "]";
}
