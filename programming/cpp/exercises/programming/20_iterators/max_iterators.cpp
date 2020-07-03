// max_iterators.cpp
// Implements a function to compute the maximum value in a range of iterators.

#include <iostream>
#include <list>
#include <vector>

template <class It> It max_iterator(It begin, It end) {
  It max_it = begin;
  for (It cursor = begin; cursor != end; ++cursor) {
    if (*cursor > *max_it) {
      max_it = cursor;
    }
  }
  return max_it;
}

int main() {
  int arr[] = {3, 2, 5, 4, 1};
  std::cout << "*max_iterator(arr, arr + 5) = " << *max_iterator(arr, arr + 5)
            << "\n";

  std::vector<int> v{3, 2, 5, 4, 1};
  std::cout << "*max_iterator(v.begin(), v.end()) = "
            << *max_iterator(v.begin(), v.end()) << "\n";

  std::list<int> lst{3, 2, 5, 4, 1};
  std::cout << "*max_iterator(lst.begin(), lst.end()) = "
            << *max_iterator(lst.begin(), lst.end()) << "\n";
}
