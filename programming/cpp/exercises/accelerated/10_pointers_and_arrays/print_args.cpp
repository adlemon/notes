// print_args.cpp
// Print the command-line arguments of the command.

#include <iostream>

int main(int argc, char** argv) {
  std::cout << "# of command-line arguments: " << argc << "\n";
  for (int i = 0; i < argc; ++i) {
    std::cout << "argv[" << i << "] = " << argv[i] << "\n";
  }
}
