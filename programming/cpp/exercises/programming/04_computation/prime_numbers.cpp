// prime_numbers.cpp
// Read a natural number n and print the first n natural numbers.

#include <cmath>
#include <iostream>
#include <vector>

bool is_prime(int n);
std::vector<unsigned int> first_n_primes_test(unsigned int n);
std::vector<unsigned int> first_n_primes_sieve(unsigned int n);

int main() {
  unsigned int n;
  std::cout << "Enter a natural number: ";
  std::cin >> n;

  std::cout << "\nThe first " << n << " prime numbers are:\n";
  std::cout << "\n-- Test Method:\n";
  for (unsigned int p : first_n_primes_test(n)) {
    std::cout << p << "\n";
  }

  std::cout << "\n-- Sieve Method:\n";
  for (unsigned int p : first_n_primes_sieve(n)) {
    std::cout << p << "\n";
  }
}

bool is_prime(unsigned int n) {
  for (unsigned int factor = 2; factor <= sqrt(n); ++factor) {
    if ((n % factor) == 0) {
      return false;
    }
  }
  return true;
}

std::vector<unsigned int> first_n_primes_test(unsigned int n) {
  std::vector<unsigned int> primes;

  for (unsigned int i = 2; primes.size() < n; ++i) {
    if (is_prime(i)) {
      primes.push_back(i);
    }
  }

  return primes;
}

std::vector<unsigned int> first_n_primes_sieve(unsigned int n) {
  std::vector<unsigned int> primes;
  // is_prime_index[i] is true if i is prime (or we have not reached i in the
  // for loop below indexed by i) and false otherwise.
  std::vector<bool> is_prime_index(n, true);
  is_prime_index[0] = is_prime_index[1] = false;

  for (unsigned int i = 2; primes.size() < n; ++i) {
    if (i == is_prime_index.size()) {
      // If we have reached the end of our index without yet finding n primes,
      // then we double the size of the index, and mark all multiples of primes
      // in the extended index as not prime.
      auto old_index_size = is_prime_index.size();
      is_prime_index.resize(2 * old_index_size, true);
      for (std::vector<bool>::size_type i = 2; i < old_index_size; ++i) {
        if (is_prime_index[i]) {
          unsigned int j = i * (old_index_size / i);
          while (j < is_prime_index.size()) {
            is_prime_index[j] = false;
            j += i;
          }
        }
      }
    }

    if (is_prime_index[i]) {
      primes.push_back(i);

      // Mark all multiples of i as not prime.
      unsigned int j = 2 * i;
      while (j < is_prime_index.size()) {
        is_prime_index[j] = false;
        j += i;
      }
    }
  }

  return primes;
}
