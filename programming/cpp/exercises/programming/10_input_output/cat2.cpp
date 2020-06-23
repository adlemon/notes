// cat2.cpp
// Read the names of two input files and one output file from the standard
// input, and then write the contents of the two inputs files to the output
// file.

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::string infilename1;
  std::cout << "Enter the name of the first input file: ";
  std::cin >> infilename1;
  std::ifstream infile1{infilename1};
  if (!infile1) {
    std::cerr << "Unable to open file " << infilename1 << " for reading.\n";
    return 1;
  }

  std::string infilename2;
  std::cout << "Enter the name of the second input file: ";
  std::cin >> infilename2;
  std::ifstream infile2{infilename2};
  if (!infile2) {
    std::cerr << "Unable to open file " << infilename2 << " for reading.\n";
    return 2;
  }

  std::string outfilename;
  std::cout << "Enter the name of the output file: ";
  std::cin >> outfilename;
  std::ofstream outfile{outfilename};
  if (!outfile) {
    std::cerr << "Unable to open file " << outfilename << " for writing.\n";
    return 3;
  }

  std::string line;
  for (auto &infile : {&infile1, &infile2}) {
    while (getline(*infile, line)) {
      outfile << line << "\n";
    }
  }
}
