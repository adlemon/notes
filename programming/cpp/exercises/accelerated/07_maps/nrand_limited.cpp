// nrand_limited.cpp
// Given a random number generator that produces a sample from the uniform
// distribution on the integers in the range [0, n0), write a random number
// generator that produces a sample from the uniform distribution on the
// integers in the range [0, n), where n is an arbitrary positive int.

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

const int n0 = 7;
int sub_random(int n, int n0, int generate_random() = rand);
int n0rand();
int nrand(int n);

int main() {
  const int num_samples = 10000;
  const int n = 13;

  std::vector<int> value_counts(n);
  for (int i = 0; i < num_samples; ++i) {
    value_counts[nrand(n)]++;
  }

  for (int i = 0; i < n; i++) {
    std::cout << i << ": " << value_counts[i] << " ("
              << 100.0 * value_counts[i] / num_samples << "%)\n";
  }
}

// Given a function generate_random that returns a sample from the uniform
// distribution on the integers in [0, n0) and an integer n <= n0, return a
// sample from the uniform distribution on the integers in [0, n).
int rand_helper(int n, int n0, int generate_random()) {
  if (n > n0) {
    throw std::domain_error("called rand_helper with n > n0");
  }

  // Each value in [0, n) will be associated with bucket_size values in [0, n0).
  // Thus, we need to ensure that bucket_size * n <= n0. We choose bucket_size
  // to be the largest integer such that bucket_size * n <= n0.
  int bucket_size = n0 / n;

  int r;
  do {
    r = generate_random() / bucket_size;
  } while (r >= n);

  return r;
}

int n0rand() { return sub_random(n0, RAND_MAX); }

int nrand(int n) {
  if (n <= n0) {
    return sub_random(n, n0, n0rand);
  }

  // Suppose the integer num_buckets satisfies num_buckets * n0 >= n. Then we
  // can sample an integer from the range [0, num_buckets * n0) uniformly at
  // random by sampling integers bucket from the range [0, num_buckets) and
  // offset from the range [0, n0) uniformly at random, and using the integer
  // bucket * n0 + offset. We can then generate a sample from the uniform
  // distribution on the integers in the range [0, n) by generating samples from
  // the uniform distribution on the integers in the range
  // [0, num_buckets * n0), rejecting samples that do not lie in the range
  // [0, n), and returning the first sample that we do not reject.
  int num_buckets = n / n0;
  if (num_buckets * n0 < n) {
    ++num_buckets;
  }

  int r;
  do {
    r = nrand(num_buckets) * n0 + n0rand();
  } while (r >= n);

  return r;
}
