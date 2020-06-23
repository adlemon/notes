// merge_sorted.cpp
// Read the names of two input files and one output file from the standard
// input. We assume that each of the input files contains integers in sorted
// order, separated by white space. Read the contents of the two input files,
// and write the output file containing all of the integers in both of the input
// files in sorted.

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> read_input_file(std::ifstream &is);

int main() {
  std::string infilename1;
  std::cout << "Enter the name of the first input file: ";
  std::cin >> infilename1;
  std::ifstream infile1{infilename1};
  if (!infile1) {
    std::cout << "Failed to open " << infilename1 << " for reading.\n";
    return 1;
  }

  std::string infilename2;
  std::cout << "Enter the name of the second input file: ";
  std::cin >> infilename2;
  std::ifstream infile2{infilename2};
  if (!infile2) {
    std::cout << "Failed to open " << infilename2 << " for reading.\n";
    return 2;
  }

  std::string outfilename;
  std::cout << "Enter the name of the output file: ";
  std::cin >> outfilename;
  std::ofstream outfile{outfilename};
  if (!outfile) {
    std::cout << "Failed to open " << outfilename << " for writing.\n";
    return 3;
  }

  std::vector<int> v1 = read_input_file(infile1);
  std::vector<int> v2 = read_input_file(infile2);

  auto i1 = v1.begin();
  auto i2 = v2.begin();
  while ((i1 != v1.end()) && (i2 != v2.end())) {
    if (*i1 <= *i2) {
      outfile << *i1 << "\n";
      ++i1;
    } else {
      outfile << *i2 << "\n";
      ++i2;
    }
  }
  while (i1 != v1.end()) {
    outfile << *i1 << "\n";
    ++i1;
  }
  while (i2 != v2.end()) {
    outfile << *i2 << "\n";
    ++i2;
  }
}

std::vector<int> read_input_file(std::ifstream &is) {
  std::vector<int> v;
  for (int i; is >> i;) {
    v.push_back(i);
  }
  return v;
}
