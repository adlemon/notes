// course_grades_types_name_grade_calls.cpp
// Use annotated functions to determine when different versions of the name and
// grade functions are called.

#include "course_grades_types.h"

int main() {
  CoreStudent *p1 = new CoreStudent(std::cin);
  CoreStudent *p2 = new GraduateStudent(std::cin);
  CoreStudent s1(std::cin);
  GraduateStudent s2(std::cin);

  std::cout << std::string(80, '=') << "\n"
            << "About to call functions on p1.\n"
            << std::string(80, '=') << "\n";
  p1->course_grade(); // CoreStudent::course_grade()
  p1->name();         // CoreStudent::name()
  std::cout << std::string(80, '=') << "\n"
            << "Finished calling functions on p1.\n"
            << std::string(80, '=') << "\n";

  std::cout << "\n"
            << std::string(80, '=') << "\n"
            << "About to call functions on p2.\n"
            << std::string(80, '=') << "\n";
  p2->course_grade(); // GraduateStudent::course_grade()
  p2->name();         // CoreStudent::name()
  std::cout << std::string(80, '=') << "\n"
            << "Finished calling functions on p2.\n"
            << std::string(80, '=') << "\n";

  std::cout << "\n"
            << std::string(80, '=') << "\n"
            << "About to call functions on s1.\n"
            << std::string(80, '=') << "\n";
  s1.course_grade(); // CoreStudent::course_grade()
  s1.name();         // CoreStudent::name()
  std::cout << std::string(80, '=') << "\n"
            << "Finished calling functions on s1.\n"
            << std::string(80, '=') << "\n";

  std::cout << "\n"
            << std::string(80, '=') << "\n"
            << "About to call functions on s2.\n"
            << std::string(80, '=') << "\n";
  s2.course_grade(); // GraduateStudent::course_grade()
  s2.name();         // CoreStudent::name()
  std::cout << std::string(80, '=') << "\n"
            << "Finished calling functions on s2.\n"
            << std::string(80, '=') << "\n";
}
