// permuted_index.cpp
// Read a set of phrases from the user and create a key-word-in-context
// concordance.
// https://en.wikipedia.org/wiki/Key_Word_in_Context

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

struct ConcordanceEntry {
  std::string prefix;
  std::string index;
};

std::vector<std::string> ReadPhrases();
std::vector<std::string> SplitString(const std::string& phrase);
bool compare(const ConcordanceEntry& ce1, const ConcordanceEntry& ce2);
std::vector<ConcordanceEntry> ConstructKWIC(
  const std::vector<std::string>& phrases
);
std::vector<ConcordanceEntry>::size_type PrefixWidth(
  const std::vector<ConcordanceEntry>& concordance
);
void PrintConcordance(const std::vector<ConcordanceEntry>& concordance);

int main() {
  std::vector<std::string> phrases = ReadPhrases();
  std::vector<ConcordanceEntry> kwic = ConstructKWIC(phrases);

  std::cout << '\n';
  PrintConcordance(kwic);
}

std::vector<std::string> ReadPhrases() {
  std::vector<std::string> phrases;

  while (std::cin) {
    std::string phrase;
    std::cout << "Enter the next phrase or end-of-file if done: ";
    std::getline(std::cin, phrase);
    if (std::cin) {
      phrases.push_back(phrase);
    }
  }

  return phrases;
}

std::vector<std::string> SplitString(const std::string& phrase) {
  std::vector<std::string> words;

  std::string::size_type i = 0;
  while (i < phrase.size()) {
    while (i < phrase.size() && isspace(phrase[i])) {
      i++;
    }

    std::string::size_type j = i;
    while (j < phrase.size() && !isspace(phrase[j])) {
      j++;
    }

    if (j > i) {
      words.push_back(phrase.substr(i, j - i));
    }

    i = j;
  }

  return words;
}

bool compare(const ConcordanceEntry& ce1, const ConcordanceEntry& ce2) {
  std::string::size_type i = 0;
  while (i < ce1.index.size() && i < ce2.index.size()) {
    if (tolower(ce1.index[i]) < tolower(ce2.index[i])) {
      return true;
    } else if (tolower(ce1.index[i]) > tolower(ce2.index[i])) {
      return false;
    }
    i++;
  }

  if (ce1.index.size() < ce2.index.size()) {
    return true;
  }
  return false;
}

std::vector<ConcordanceEntry> ConstructKWIC(
  const std::vector<std::string>& phrases
) {
  std::vector<ConcordanceEntry> kwic;

  for (std::vector<std::string>::const_iterator it = phrases.begin();
      it != phrases.end(); ++it) {
    std::vector<std::string> words = SplitString(*it);

    for (std::vector<std::string>::size_type i = 0; i != words.size(); i++) {
      ConcordanceEntry ce;
      for (std::vector<std::string>::size_type j = 0; j < i; j++) {
        if (j > 0) {
          ce.prefix += ' ';
        }
        ce.prefix += words[j];
      }
      for (std::vector<std::string>::size_type j = i; j < words.size(); j++) {
        if (j > i) {
          ce.index += ' ';
        }
        ce.index += words[j];
      }
      kwic.push_back(ce);
    }
  }

  std::sort(kwic.begin(), kwic.end(), compare);

  return kwic;
}

std::vector<ConcordanceEntry>::size_type PrefixWidth(
  const std::vector<ConcordanceEntry>& concordance
) {
  std::vector<ConcordanceEntry>::size_type prefix_width = 0;

  for (std::vector<ConcordanceEntry>::const_iterator it = concordance.begin();
      it != concordance.end(); ++it) {
    prefix_width = std::max(it->prefix.size(), prefix_width);
  }

  return prefix_width;
}

void PrintConcordance(const std::vector<ConcordanceEntry>& concordance) {
  std::vector<ConcordanceEntry>::size_type prefix_width = PrefixWidth(concordance);
  for (std::vector<ConcordanceEntry>::const_iterator it = concordance.begin();
      it != concordance.end(); ++it) {
    std::cout << std::string(prefix_width - it->prefix.size(), ' ')
              << it->prefix
              << std::string(5, ' ')
              << it->index << '\n';
  }
}
