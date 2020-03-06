// filter_lines.cpp
// Read lines from a file; for each line, ask the user whether or not to keep
// the line; for each line that the user tells us to keep, write the line to
// the output file.

#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::string outfilename;
  std::cout << "Enter the name of the output file: ";
  std::cin >> outfilename;

  std::ifstream infile("in.txt");
  std::ofstream outfile(outfilename.c_str());

  std::string line;
  while (std::getline(infile, line)) {
    std::cout << "Read line: " << line << "\n";

    char c = '\0';
    while (!(c == 'y' || c == 'n')) {
      std::cout << "Keep? y/n: ";
      std::cin >> c;
    }

    if (c == 'y') {
      outfile << line << std::endl;
    }
  }
}
