// median.cpp
// Template function to compute the median of a vector.

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template <class DataType> DataType median(std::vector<DataType> v);

int main() {
  std::vector<int> v;

  std::cout << "Enter integers: ";
  std::copy(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(),
            std::back_inserter(v));
  std::cin.clear();
  std::cout << "\nThe median of the entered integers is: " << median(v) << "\n";

  std::vector<double> w;
  std::cout << "\nEnter doubles: ";
  std::copy(std::istream_iterator<double>(std::cin),
            std::istream_iterator<double>(), std::back_inserter(w));
  std::cout << "\nThe median of the entered doubles is: " << median(w) << "\n";
}

template <class DataType> DataType median(std::vector<DataType> v) {
  std::sort(v.begin(), v.end());

  typename std::vector<DataType>::size_type n = v.size();
  typename std::vector<DataType>::size_type m = n / 2;

  return ((n % 2) == 0) ? (v[m - 1] + v[m]) / 2 : v[m];
}
