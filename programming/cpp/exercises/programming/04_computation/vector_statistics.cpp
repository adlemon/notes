// vector_statistics.cpp
// Read integers into a vector and then print statistics about the vector.

#include <algorithm>
#include <iostream>
#include <vector>

int min_sorted(const std::vector<int> &v);
double median_sorted(const std::vector<int> &v);
int sum(const std::vector<int> &v);
double mean(const std::vector<int> &v);
int max_sorted(const std::vector<int> &v);
int mode_sorted(const std::vector<int> &v);

int main() {
  std::cout << "Enter integers and any noninteger when done:\n";
  std::vector<int> v;
  for (int i; std::cin >> i;) {
    v.push_back(i);
  }
  if (v.size() == 0) {
    return 0;
  }

  std::sort(v.begin(), v.end());
  std::cout << "The minimum of the integers entered is " << min_sorted(v)
            << ".\n"
            << "The median of the integers entered is " << median_sorted(v)
            << ".\n"
            << "The mean of the integers entered is " << mean(v) << ".\n"
            << "The maximum of the integers entered is " << max_sorted(v)
            << ".\n"
            << "The mode of the integers entered is " << mode_sorted(v)
            << ".\n";
}

int min_sorted(const std::vector<int> &v) { return v[0]; }

double median_sorted(const std::vector<int> &v) {
  auto n = v.size();
  auto m = n / 2;

  if ((n % 2) == 0) {
    return (v[m - 1] + v[m]) / 2;
  }
  return v[m];
}

int sum(const std::vector<int> &v) {
  int s = 0;
  for (int i : v) {
    s += i;
  }
  return s;
}

double mean(const std::vector<int> &v) {
  return static_cast<double>(sum(v)) / v.size();
}

int max_sorted(const std::vector<int> &v) { return v[v.size() - 1]; }

int mode_sorted(const std::vector<int> &v) {
  int mode = v[0];
  int mode_count = 1;

  int current_value = v[0];
  int current_value_count = 0;
  for (int i : v) {
    if (i == current_value) {
      ++current_value_count;
    } else {
      if (current_value_count > mode_count) {
        mode = current_value;
        mode_count = current_value_count;
      }
      current_value = i;
      current_value_count = 1;
    }
  }
  if (current_value_count > mode_count) {
    mode = current_value;
  }

  return mode;
}
