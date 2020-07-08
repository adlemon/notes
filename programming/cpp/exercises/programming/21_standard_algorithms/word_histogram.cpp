// word_histogram.cpp
// Read words from a file and print a histogram.

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

struct WordCount {
  std::string word;
  int count;
};

int main() {
  std::string infilename;
  std::cout << "Enter the name of the input file: ";
  std::cin >> infilename;

  std::ifstream infile{infilename};
  if (!infile) {
    std::cerr << "Unable to open " << infilename << " for reading.\n";
    return 1;
  }

  std::string outfilename;
  std::cout << "Enter the name of the output file: ";
  std::cin >> outfilename;

  std::ofstream outfile{outfilename};
  if (!outfile) {
    std::cerr << "Unable to open " << outfilename << " for writing.\n";
    return 2;
  }

  std::map<std::string, int> words;
  for (std::istream_iterator<std::string> infile_it{infile}, end_it{};
       infile_it != end_it; ++infile_it) {
    ++words[*infile_it];
  }

  std::vector<WordCount> word_counts;
  for (auto word_count : words) {
    word_counts.push_back(WordCount{word_count.first, word_count.second});
  }
  std::sort(word_counts.begin(), word_counts.end(),
            [](const WordCount &wc1, const WordCount &wc2) {
              if (wc1.count != wc2.count) {
                return wc1.count > wc2.count;
              }
              return wc1.word < wc2.word;
            });

  for (const WordCount &word_count : word_counts) {
    outfile << word_count.word << ": " << word_count.count << "\n";
  }
}
