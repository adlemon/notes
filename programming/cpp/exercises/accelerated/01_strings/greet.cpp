// greet.cpp
// Prompt the user for a name, and then print a greeting to the console.

#include <iostream>
#include <string>

int main()
{
  std::string name;
  std::cout << "What is your name? ";
  std::cin >> name;

  std::cout << "Hello, " << name << "!" << std::endl;
  
  return 0;
}
