// greet_framed.cpp
// Prompt a user to enter a name, and then print a framed greeting to the
// console.

#include <iostream>
#include <string>

int main()
{
  std::string name;
  std::cout << "What is your name? ";
  std::cin >> name;

  const std::string greeting = "Hello, " + name + "!";
  const std::string padding_row = "* " + std::string(greeting.size(), ' ') + " *";
  const std::string frame_row = std::string(padding_row.size(), '*');

  std::cout
    << frame_row << "\n"
    << padding_row << "\n"
    << "* " << greeting << " *" << "\n"
    << padding_row << "\n"
    << frame_row << std::endl;

  return 0;
}
