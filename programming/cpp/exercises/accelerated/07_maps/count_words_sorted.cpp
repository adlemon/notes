// count_words_sorted.cpp
// Read words from the standard input. After all of the words have been read,
// print each unique word that was read, together with the number of times that
// the word occurred. When printing the words,

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct WordCount {
  std::string word;
  int count;
};

bool word_count_less_than(WordCount wc1, WordCount wc2) {
  if (wc1.count < wc2.count) {
    return true;
  }
  if (wc1.count > wc2.count) {
    return false;
  }
  return wc1.word < wc2.word;
}

int main() {
  std::map<std::string, int> word_counts_map;

  std::string word;
  std::cout << "Enter the words followed by an end-of-file:\n";
  while (std::cin >> word) {
    word_counts_map[word]++;
  }

  std::vector<WordCount> word_counts_vector;
  for (std::map<std::string, int>::const_iterator it = word_counts_map.begin();
       it != word_counts_map.end(); ++it) {
    WordCount wc;
    wc.word = it->first;
    wc.count = it->second;

    word_counts_vector.push_back(wc);
  }
  std::sort(word_counts_vector.begin(), word_counts_vector.end(),
            word_count_less_than);

  for (std::vector<WordCount>::const_iterator it = word_counts_vector.begin();
       it != word_counts_vector.end(); ++it) {
    std::cout << it->word << ": " << it->count << "\n";
  }
}
