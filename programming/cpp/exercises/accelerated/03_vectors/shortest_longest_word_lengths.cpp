// shortest_longest_word_lengths.cpp
// Read words from the standard input and report the lengths of the shortest and
// longest words that are read.

#include <iostream>
#include <string>

int main() {
  bool have_read_word = false;
  std::string::size_type shortest_length, longest_length;

  std::string word;
  while (std::cin >> word) {
    std::string::size_type n = word.size();
    if (!have_read_word || n < shortest_length) {
      shortest_length = n;
    }
    if (!have_read_word || n > longest_length) {
      longest_length = n;
    }
    have_read_word = true;
  }

  std::cout << "Length of shortest word: " << shortest_length << "\n"
            << "Length of longest word:  " << longest_length << "\n";
}
