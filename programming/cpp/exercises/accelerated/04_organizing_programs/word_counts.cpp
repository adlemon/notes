// word_counts.cpp
// Read words from the standard input. After reading all of the words, print the
// total number of words that were read, the number of unique words that were
// read, and the number of times that each unique word was read.

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

struct WordCount {
  std::string word;
  int count;
};

void ReadWords(std::vector<std::string>& words);
void CountWords(
  std::vector<std::string>& words,
  std::vector<WordCount>& word_counts,
  std::string::size_type& max_word_length
);
void PrintStatistics(
  const std::vector<std::string>& words,
  const std::vector<WordCount>& word_counts,
  const int& max_word_length
);

int main() {
  std::vector<std::string> words;
  ReadWords(words);

  std::vector<WordCount> word_counts;
  std::string::size_type max_word_length;
  CountWords(words, word_counts, max_word_length);

  std::cout << std::string(2, '\n');
  PrintStatistics(words, word_counts, max_word_length);
}

void ReadWords(std::vector<std::string>& words) {
  std::string word;
  std::cout << "Enter the next word or end-of-file if done: ";
  while (std::cin >> word) {
    words.push_back(word);
    std::cout << "Enter the next word or end-of-file if done: ";
  }
}

void CountWords(
  std::vector<std::string>& words,
  std::vector<WordCount>& word_counts,
  std::string::size_type& max_word_length
) {
  std::sort(words.begin(), words.end());

  max_word_length = 0;
  std::vector<std::string>::size_type i = 0;
  while (i < words.size()) {
    max_word_length = std::max(words[i].size(), max_word_length);

    std::vector<std::string>::size_type j = i;
    while (j < words.size() && words[i] == words[j]) {
      j++;
    }

    WordCount wc;
    wc.word = words[i];
    wc.count = j - i;
    word_counts.push_back(wc);

    i = j;
  }
}

void PrintStatistics(
  const std::vector<std::string>& words,
  const std::vector<WordCount>& word_counts,
  const int& max_word_length
) {
  std::cout << "Number of words read: " << words.size() << '\n'
            << "Number of unique words read: " << word_counts.size() << '\n';
  for (std::vector<WordCount>::size_type i = 0; i < word_counts.size(); i++) {
    std::cout << std::setw(max_word_length) << word_counts[i].word << ' '
              << word_counts[i].count << '\n';
  }
}
