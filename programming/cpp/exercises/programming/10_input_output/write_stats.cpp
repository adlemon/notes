// write_stats.cpp
// Read integers from a file and write statistics to a file.

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct VectorStats {
  size_t count;
  int min;
  double median;
  double mean;
  int max;
};

VectorStats vector_stats(std::vector<int> v);
std::ostream &operator<<(std::ostream &os, VectorStats stats);

int main() {
  std::string infilename;
  std::cout << "Enter the name of the input file: ";
  std::cin >> infilename;
  std::ifstream infile{infilename};
  if (!infile) {
    std::cerr << "Unable to open the file " << infilename << " for reading.\n";
    return 1;
  }

  std::string outfilename;
  std::cout << "Enter the name of the output file: ";
  std::cin >> outfilename;
  std::ofstream outfile{outfilename};
  if (!outfile) {
    std::cerr << "Unable to open the file " << outfilename << " for writing.\n";
  }

  std::vector<int> v;
  for (int i; infile >> i;) {
    v.push_back(i);
  }

  outfile << vector_stats(v);
}

VectorStats vector_stats(std::vector<int> v) {
  std::sort(v.begin(), v.end());

  VectorStats stats;
  stats.count = v.size();
  stats.min = v[0];
  stats.max = v[v.size() - 1];

  auto n = v.size();
  auto m = n / 2;
  stats.median = ((n % 2) == 0) ? (v[m - 1] + v[m]) / 2.0 : v[m - 1];

  int sum = 0;
  for (int x : v) {
    sum += x;
  }
  stats.mean = static_cast<double>(sum) / v.size();

  return stats;
}

std::ostream &operator<<(std::ostream &os, VectorStats stats) {
  return os << "count: " << stats.count << "\n"
            << "min: " << stats.min << "\n"
            << "median: " << stats.median << "\n"
            << "mean: " << stats.mean << "\n"
            << "max: " << stats.max << "\n";
}
