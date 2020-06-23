// read_write_position.cpp
// Read from and write to positions in a file.

#include <fstream>
#include <iostream>
#include <string>

int main() {
  const std::string filename = "read_write_position_out.txt";

  std::ofstream outfile1{filename};
  outfile1 << "Hello$ World!";
  outfile1.close();

  std::ifstream infile1{filename};
  infile1.seekg(5);
  char c;
  infile1 >> c;
  infile1.close();
  std::cout << "Character at index 5: " << c << "\n";

  std::fstream outfile2{filename};
  outfile2.seekp(5, std::ios::beg);
  outfile2 << ',';
  outfile2.close();

  std::ifstream infile2{filename};
  std::string line;
  while (getline(infile2, line)) {
    std::cout << line << "\n";
  }
}
