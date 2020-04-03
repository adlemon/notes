// copy.cpp
// Write a template function to copy data from one container to another.

#include <iostream>
#include <iterator>
#include <list>
#include <vector>

template <class InputIterator, class OutputIterator>
OutputIterator my_copy(InputIterator b, InputIterator e, OutputIterator out) {
  while (b != e) {
    *out = *b;
    ++out;
    ++b;
  }
  return out;
}

int main() {
  std::vector<int> v;
  std::cout << "Enter a collection of integers: ";
  std::copy(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(),
            std::back_inserter(v));

  std::list<int> lst;
  my_copy(v.begin(), v.end(), std::back_inserter(lst));

  std::cout << "You entered the integers: ";
  std::copy(lst.begin(), lst.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";
}
