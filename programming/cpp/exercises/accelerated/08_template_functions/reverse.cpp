// reverse.cpp
// Write a template function to reverse a container.

#include <iostream>
#include <iterator>
#include <list>
#include <vector>

template <class T> void swap(T &x, T &y) {
  T tmp = x;
  x = y;
  y = tmp;
}

template <class T> T reverse(T begin, T end) {
  while (begin != end) {
    --end;
    if (begin != end) {
      swap(*begin, *end);
      ++begin;
    }
  }
}

int main() {
  {
    std::vector<int> v;
    std::cout << "Enter some integers: ";
    std::copy(std::istream_iterator<int>(std::cin),
              std::istream_iterator<int>(), std::back_inserter(v));
    std::cin.clear();

    reverse(v.begin(), v.end());
    std::cout << "The integers in reverse order are: ";
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
  }

  {
    std::list<double> lst;
    std::cout << "\nEnter some doubles: ";
    std::copy(std::istream_iterator<double>(std::cin),
              std::istream_iterator<double>(), std::back_inserter(lst));

    reverse(lst.begin(), lst.end());
    std::cout << "The integers in reverse order are: ";
    std::copy(lst.begin(), lst.end(),
              std::ostream_iterator<double>(std::cout, " "));
    std::cout << "\n";
  }
}
