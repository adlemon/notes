// median.cpp
// Implement a function to compute the median of a vector of doubles.

#include <algorithm>
#include <stdexcept>

#include "median.h"

double median(std::vector<double> v) {
  if (v.empty()) {
    throw std::domain_error("median of an empty vector");
  }

  std::sort(v.begin(), v.end());
  std::vector<double>::size_type n = v.size();
  std::vector<double>::size_type m = n / 2;
  // Case I: n = 2 * m is even.
  //   The median is (v[m-1] + v[m]) / 2.
  // Case II: n = 2 * m + 1 is odd.
  //   The median is v[m].
  return ((n % 2) == 0) ? (v[m - 1] + v[m]) / 2 : v[m];
}
