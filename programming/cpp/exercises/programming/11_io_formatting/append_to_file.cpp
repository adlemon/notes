// append_to_file.cpp
// Append to a file.

#include <fstream>
#include <iostream>
#include <string>

int main() {
  const std::string filename = "append_to_file_out.txt";

  std::ofstream outfile1{filename};
  outfile1 << "Hello";
  outfile1.close();

  std::ofstream outfile2{filename, std::ios_base::app};
  outfile2 << ", World!";
  outfile2.close();

  std::ifstream infile{filename};
  std::string line;
  while (getline(infile, line)) {
    std::cout << line << "\n";
  }
}
