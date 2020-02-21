// find.cpp
// Write a template function to find a value between two iterators.

#include <iostream>
#include <iterator>
#include <list>
#include <vector>

template <class IteratorType, class ValueType>
ValueType find(IteratorType b, IteratorType e, const ValueType& x) {
  while (b != e && *b != x) {
    ++b;
  }
  return *b;
}

int main() {
  std::vector<int> v;
  std::cout << "Enter a collection of integers: ";
  std::copy(
    std::istream_iterator<int>(std::cin),
    std::istream_iterator<int>(),
    std::back_inserter(v)
  );
  std::cin.clear();

  int x;
  std::cout << "Enter a value to search for: ";
  std::cin >> x;

  if (find(v.begin(), v.end(), x)) {
    std::cout << "The integer value was found in the collection.\n";
  } else {
    std::cout << "The integer value was not found in the collection.\n";
  }

  std::list<double> w;
  std::cout << "\nEnter a collection of doubles: ";
  std::copy(
    std::istream_iterator<double>(std::cin),
    std::istream_iterator<double>(),
    std::back_inserter(w)
  );
  std::cin.clear();

  int y;
  std::cout << "Enter a value to search for: ";
  std::cin >> y;

  if (find(w.begin(), w.end(), y)) {
    std::cout << "The double value was found in the collection.\n";
  } else {
    std::cout << "The double value was not found in the collection.\n";
  }
}
