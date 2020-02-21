// max.cpp
// Write a template function to compute the maximum of two values.

#include <iostream>

template <class DataType>
DataType max(const DataType& x, const DataType& y);

int main() {
  int i1, i2;
  std::cout << "Enter two integers: ";
  std::cin >> i1 >> i2;
  std::cout << "The maximum of the two integers is: " << max(i1, i2) << "\n";

  double d1, d2;
  std::cout << "\nEnter two doubles: ";
  std::cin >> d1 >> d2;
  std::cout << "The maximum of the doubles is: " << max(d1, d2) << "\n";
}

template <class DataType>
DataType max(const DataType& x, const DataType& y) {
  return (y > x) ? y : x;
}
