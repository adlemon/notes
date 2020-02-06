// copy_vector_bug.cpp
// Attempt to copy a vector; this program has a bug. See copy_vector.cpp for a
// correct implementation.

#include <algorithm>
#include <vector>

int main() {
  std::vector<int> u(10, 100);
  std::vector<int> v;
  std::copy(u.begin(), u.end(), v.begin());
}
