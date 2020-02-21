// replace.cpp
// Write a template function to replace all occurrences of a value between two
// iterators with another value.

#include <iostream>
#include <iterator>
#include <list>
#include <vector>

template <class InputIteratorType, class ValueType>
InputIteratorType replace(
  InputIteratorType b,
  const InputIteratorType& e,
  const ValueType& old_value,
  const ValueType& new_value
) {
  while (b != e) {
    if (*b == old_value) {
      *b = new_value;
    }
    ++b;
  }
  return b;
}

int main() {
  {
    std::vector<int> v;
    std::cout << "Enter the integer data: ";
    std::copy(
      std::istream_iterator<int>(std::cin),
      std::istream_iterator<int>(),
      std::back_inserter(v)
    );
    std::cin.clear();

    int old_value, new_value;
    std::cout << "Enter the old value: ";
    std::cin >> old_value;
    std::cout << "Enter the new value: ";
    std::cin >> new_value;

    replace(v.begin(), v.end(), old_value, new_value);
    std::cout << "The modified data is: ";
    std::copy(
      v.begin(),
      v.end(),
      std::ostream_iterator<int>(std::cout, " ")
    );
    std::cout << "\n";
  }

  {
    std::list<double> lst;
    std::cout << "\nEnter the double data: ";
    std::copy(
      std::istream_iterator<double>(std::cin),
      std::istream_iterator<double>(),
      std::back_inserter(lst)
    );
    std::cin.clear();

    double old_value, new_value;
    std::cout << "Enter the old value: ";
    std::cin >> old_value;
    std::cout << "Enter the new value: ";
    std::cin >> new_value;

    replace(lst.begin(), lst.end(), old_value, new_value);
    std::cout << "The modified data is: ";
    std::copy(
      lst.begin(),
      lst.end(),
      std::ostream_iterator<double>(std::cout, " ")
    );
    std::cout << "\n";
  }
}
