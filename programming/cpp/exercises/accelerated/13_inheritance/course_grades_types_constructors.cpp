// course_grades_types_constructors.cpp
// Use annotated constructors to determine when different types of constructors
// are called.

#include "course_grades_types.h"

int main() {
  // Call the default CoreStudent constructor.
  {
    std::cout << std::string(80, '=') << "\n"
              << "About to call default CoreStudent constructor.\n"
              << std::string(80, '=') << "\n";
    CoreStudent s;
    std::cout << std::string(80, '=') << "\n"
              << "Finished calling default CoreStudent constructor.\n"
              << std::string(80, '=') << "\n";
  }

  // Call the CoreStudent constructor that reads data from an input stream.
  {
    std::cout << "\n"
              << std::string(80, '=') << "\n"
              << "About to call CoreStudent stream constructor.\n"
              << std::string(80, '=') << "\n";
    CoreStudent s(std::cin);
    std::cout << std::string(80, '=') << "\n"
              << "Finished calling CoreStudent stream constructor.\n"
              << std::string(80, '=') << "\n";
  }

  // Call the default GraduateStudent constructor. The default CoreStudent
  // constructor is called by the GraduateStudent constructor.
  {
    std::cout << "\n"
              << std::string(80, '=') << "\n"
              << "About to call default GraduateStudent constructor.\n"
              << std::string(80, '=') << "\n";
    GraduateStudent s;
    std::cout << std::string(80, '=') << "\n"
              << "Finished calling default GraduateStudent constructor.\n"
              << std::string(80, '=') << "\n";
  }

  // Call the GraduateStudent constructor that reads from an input stream. The
  // default CoreStudent constructor is called by the GraduateStudent
  // constructor.
  {
    std::cout << "\n"
              << std::string(80, '=') << "\n"
              << "About to call GraduateStudent stream constructor.\n"
              << std::string(80, '=') << "\n";
    GraduateStudent s(std::cin);
    std::cout << std::string(80, '=') << "\n"
              << "Finished calling GraduateStudent stream constructor.\n"
              << std::string(80, '=') << "\n";
  }
}
