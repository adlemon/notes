// nrand_binary.cpp
// Given a function that randomly produces either 0 or 1 with equal probability,
// write a function that computes a random integer in the range [0, n), where n
// is an arbitrary positive int.

#include <cstdlib>
#include <iostream>
#include <map>

int rand_bit();
int num_bits(int n);
int nrand(int n);

int main() {
  const int num_samples = 10000;

  std::map<int, int> value_counts;
  for (int i = 0; i < num_samples; ++i) {
    value_counts[nrand(10) + 1] += 1;
  }

  for (std::map<int, int>::const_iterator it = value_counts.begin();
      it != value_counts.end(); ++it) {
    std::cout << it->first << ": " << it->second
              << " (" << 100.0 * it->second / num_samples << "%)\n";
  }
}

int rand_bit() {
  int bucket_size = RAND_MAX / 2;

  int r;
  do {
    r = rand() / bucket_size;
  } while (r > 1);

  return r;
}

int num_bits(int n) {
  int bits = 0;
  while (n > 0) {
    n >>= 1;
    ++bits;
  }
  return bits;
}

int nrand(int n) {
  int bits = num_bits(n);

  int r;
  do {
    r = 0;
    for (int i = 0; i < bits; ++i) {
      r = (r << 1) + rand_bit();
    }
  } while (r >= n);

  return r;
}

