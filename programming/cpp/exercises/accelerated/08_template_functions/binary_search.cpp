// binary_search.cpp
// Write a template function to perform binary search given some random-access
// iterators.

#include <iostream>
#include <iterator>
#include <string>
#include <vector>

template <class IteratorType, class ValueType>
bool binary_search(IteratorType begin, IteratorType end, const ValueType& x) {
  while (begin < end) {
    IteratorType mid = begin + (end - begin) / 2;
    if (x == *mid) {
      return true;
    }
    if (x < *mid) {
      end = mid;
    } else {
      begin = mid + 1;
    }
  }
  return false;
}

int main() {
  {
    std::vector<int> v;
    std::cout << "Enter some integers in ascending order: ";
    std::copy(
      std::istream_iterator<int>(std::cin),
      std::istream_iterator<int>(),
      std::back_inserter(v)
    );
    std::cin.clear();

    int x;
    std::cout << "Enter the integer to search for: ";
    std::cin >> x;

    if (binary_search(v.begin(), v.end(), x)) {
      std::cout << "Found the value in the data.\n";
    } else {
      std::cout << "Did not find the value in the data.\n";
    }
  }

  {
    std::string s;
    std::cout << "\nEnter a string of characters in ascending order: ";
    std::cin >> s;

    char c;
    std::cout << "Enter a character: ";
    std::cin >> c;

    if (binary_search(s.begin(), s.end(), c)) {
      std::cout << "Found the character in the string.\n";
    } else {
      std::cout << "Did not find the character in the string.\n";
    }
  }
}
