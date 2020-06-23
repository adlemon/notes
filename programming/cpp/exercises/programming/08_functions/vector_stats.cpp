// vector_stats.cpp
// Compute statistics for a vector.

#include <algorithm>
#include <iostream>
#include <vector>

struct VectorStats {
  int min;
  double median;
  double mean;
  int max;
};

std::vector<int> range(int begin, int end);
VectorStats vector_stats(std::vector<int> v);
std::ostream &operator<<(std::ostream &os, const VectorStats &stats);

int main() {
  std::vector<int> v = range(0, 10);
  v.push_back(100);

  VectorStats stats = vector_stats(v);
  std::cout << stats;
}

std::vector<int> range(int begin, int end) {
  std::vector<int> v;
  for (int i = begin; i < end; ++i) {
    v.push_back(i);
  }
  return v;
}

VectorStats vector_stats(std::vector<int> v) {
  VectorStats stats;

  std::sort(v.begin(), v.end());
  stats.min = v[0];
  stats.max = v[v.size() - 1];

  auto n = v.size();
  auto m = n / 2;
  stats.median = ((n % 2) == 0) ? (v[m - 1] + v[m]) / 2.0 : v[m];

  int sum = 0;
  for (int x : v) {
    sum += x;
  }
  stats.mean = static_cast<double>(sum) / v.size();

  return stats;
}

std::ostream &operator<<(std::ostream &os, const VectorStats &stats) {
  return os << "Min: " << stats.min << "\n"
            << "Median: " << stats.median << "\n"
            << "Mean: " << stats.mean << "\n"
            << "Max: " << stats.max << "\n";
}
