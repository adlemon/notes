// count_words.cpp
// Read words from the standard input, and count the number of times that each
// distinct word appears.

#include <iostream>
#include <string>
#include <vector>

int main() {
  std::vector<std::string> words;
  std::vector<int> counts;

  // Read words.
  std::cout << "Enter a word or end-of-file if done:\n";
  std::string word;
  while (std::cin >> word) {
    // Find the index of the word in the words vector.
    std::vector<std::string>::size_type i = 0;
    while (i < words.size() && words[i] != word) {
      i++;
    }

    // If we haven't seen the word before, add the word to the vector of words
    // and initialize its count.
    if (i == words.size()) {
      words.push_back(word);
      counts.push_back(0);
    }

    // Update the count.
    counts[i]++;
  }

  // Print the word counts.
  std::cout << "\nWord Counts:\n";
  for (std::vector<std::string>::size_type i = 0; i < words.size(); i++) {
    std::cout << words[i] << ": " << counts[i] << "\n";
  }
}
