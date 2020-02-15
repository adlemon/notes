// count_words.cpp
// Read words from the user, and count the number of times that each word
// occurs. After reading all of the words, print the words and corresponding
// counts.

#include <iostream>
#include <map>
#include <string>

int main() {
  std::string word;

  std::cout << "Enter the words: ";
  std::map<std::string, int> word_counts;
  while (std::cin >> word) {
    ++word_counts[word];
  }

  std::cout << "\nThe words and their counts are:\n";
  for (std::map<std::string, int>::const_iterator it = word_counts.begin();
      it != word_counts.end(); ++it) {
    std::cout << it->first << "\t" << it->second << "\n";
  }
}
