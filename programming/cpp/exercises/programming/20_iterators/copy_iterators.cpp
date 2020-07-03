// copy_iterators.cpp
// Implements a function to copy one range of iterators into another.

#include <iostream>
#include <list>
#include <vector>

template <class In, class Out>
void copy_iterators(In in_begin, In in_end, Out out_begin) {
  Out out_cursor = out_begin;
  for (In in_cursor = in_begin; in_cursor != in_end;
       ++in_cursor, ++out_cursor) {
    *out_cursor = *in_cursor;
  }
}

template <class T>
std::ostream &operator<<(std::ostream &os, std::vector<T> v) {
  os << "{";
  for (typename std::vector<T>::size_type i = 0; i < v.size(); ++i) {
    if (i > 0) {
      os << ", ";
    }
    os << v[i];
  }
  return os << "}";
}

int main() {
  std::list<int> lst{2, 4, 6, 8, 10};
  std::vector<int> v(5);
  copy_iterators(lst.begin(), lst.end(), v.begin());
  std::cout << v << "\n";
}
