// sorted_without_duplicates.cpp
// Read integers and then print the integers in sorted order without duplicates.

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::cout << "Enter integers and a non-integer when done:\n";
  std::vector<int> v;
  for (int i; std::cin >> i;) {
    v.push_back(i);
  }
  if (v.size() == 0) {
    return 0;
  }

  std::sort(v.begin(), v.end());

  std::cout << "The numbers that were entered, in sorted order and without "
               "duplicates, are as shown below.\n";
  int previous_value = v[0] - 1;
  for (int i : v) {
    if (i != previous_value) {
      std::cout << i << "\n";
      previous_value = i;
    }
  }
}
