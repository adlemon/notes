// word_histogram.cpp
// Create a histogram of the words in a file.

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

class WordStream {
public:
  WordStream(std::istream &is, const std::string &separators)
      : is_{is}, separators_(separators) {}
  WordStream &operator>>(std::string &s);
  operator bool();

private:
  std::istream &is_;
  const std::string separators_;
};

bool contains(const std::string &s, const char c);

struct WordCount {
  std::string word;
  unsigned count;
};

using WordHistogram = std::vector<WordCount>;
WordHistogram word_histogram(std::vector<std::string> words);
std::ostream &operator<<(std::ostream &os, WordHistogram word_hist);

std::string tolower(const std::string &s);

int main() {
  std::string filename;
  std::cout << "Enter the name of the input file: ";
  std::cin >> filename;

  std::ifstream infile{filename};
  if (!infile) {
    std::cerr << "Unable to open file " << filename << " for reading.\n";
    return 1;
  }

  WordStream ws(infile, " ,;:.!?\"(){}[]<>/~&|$@#%^*\n");
  std::vector<std::string> words;
  for (std::string word; ws >> word;) {
    if (!word.empty()) {
      words.push_back(tolower(word));
    }
  }

  std::cout << word_histogram(words);
}

std::string tolower(const std::string &s) {
  std::string t(s);
  for (std::string::size_type i = 0; i < t.size(); ++i) {
    t[i] = tolower(t[i]);
  }
  return t;
}

bool contains(const std::string &s, const char c) {
  for (char ch : s) {
    if (ch == c) {
      return true;
    }
  }
  return false;
}

WordStream &WordStream::operator>>(std::string &s) {
  s.clear();
  while (is_) {
    char c = is_.get();
    if (!contains(separators_, c)) {
      s += c;
      break;
    }
  }
  while (is_) {
    char c = is_.get();
    if (contains(separators_, c)) {
      break;
    }
    s += c;
  }
  return *this;
}

WordStream::operator bool() { return is_.good() && !is_.fail() && !is_.bad(); }

WordHistogram word_histogram(std::vector<std::string> words) {
  WordHistogram word_hist;

  std::sort(words.begin(), words.end());
  for (auto it = words.begin(); it != words.end();) {
    std::string word = *it;

    unsigned count = 1;
    while (it != words.end() && *it == word) {
      ++it;
      ++count;
    }

    word_hist.push_back(WordCount{word, count});
  }

  return word_hist;
}

std::ostream &operator<<(std::ostream &os, WordHistogram word_hist) {
  for (const WordCount &wc : word_hist) {
    os << wc.word << ": " << wc.count << "\n";
  }
  return os;
}
