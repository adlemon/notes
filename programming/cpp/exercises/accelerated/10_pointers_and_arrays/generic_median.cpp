// generic_median.cpp
// Write a median function that works with arrays or vectors of any arithmetic
// type.

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template <class V, class C> V median(const C &begin, const C &end) {
  std::vector<V> v;
  std::copy(begin, end, std::back_inserter(v));
  std::sort(v.begin(), v.end());

  typename std::vector<V>::size_type n = v.size();
  typename std::vector<V>::size_type m = n / 2;

  return ((n % 2) == 0) ? (v[m - 1] + v[m]) / 2 : v[m];
}

int main() {
  std::vector<int> v = {3, 2, 4, 5, 1};
  std::cout << "median(v) = "
            << median<int, std::vector<int>::const_iterator>(v.begin(), v.end())
            << "\n";
  std::cout << "v = ";
  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";

  double a[] = {3.3, 2.2, 4.4, 5.5, 1.1};
  std::cout << "median(a) = " << median<double, double *>(a + 0, a + 5) << "\n";
  std::cout << "a = ";
  std::copy(a + 0, a + 5, std::ostream_iterator<double>(std::cout, " "));
  std::cout << "\n";
}
