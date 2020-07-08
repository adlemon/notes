// stream_iterators.cpp
// Uses stream iterators to copy the unique "words" from one file to another.

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int main() {
  // Open the input file and its words into a vector.
  std::string infilename;
  std::cout << "Enter the name of the input file: ";
  std::cin >> infilename;

  std::ifstream infile{infilename};
  if (!infile) {
    std::cerr << "Unable to open " << infilename << " for reading.\n";
    return 1;
  }

  std::istream_iterator<std::string> isi{infile};
  std::vector<std::string> words{std::istream_iterator<std::string>{infile},
                                 std::istream_iterator<std::string>{}};
  std::sort(words.begin(), words.end());

  // Open the output file and write to it the unique words in sorted order.
  std::string outfilename;
  std::cout << "Enter the name of the output file: ";
  std::cin >> outfilename;

  std::ofstream outfile{outfilename};
  if (!outfile) {
    std::cerr << "Unable to open " << outfilename << " for writing.\n";
    return 2;
  }

  std::ostream_iterator<std::string> osi{outfile, "\n"};
  std::unique_copy(words.begin(), words.end(), osi);
}
