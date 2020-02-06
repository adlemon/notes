// concatenate_string_vector.cpp
// Concatenate a vector of strings.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::string concatenate(std::vector<std::string> v);

int main() {
  std::vector<std::string> words;

  std::cout << "Enter some words: ";
  std::string word;
  while (std::cin >> word) {
    words.push_back(word);
  }

  std::string concatenated_words = concatenate(words);
  std::cout << "\nThe concatenation of all the words is:\n"
            << concatenated_words << '\n';
}

std::string concatenate(std::vector<std::string> v) {
  return std::accumulate(v.begin(), v.end(), std::string());
}
