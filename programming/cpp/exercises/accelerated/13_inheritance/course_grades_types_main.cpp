// course_grades_types_main.cpp
// Compute course grades for different types of students: undergraduates,
// graduates, students taking the class pass/fail, and students auditing the
// course.

#include "course_grades_types.h"

int main() {
  std::vector<Student> students;
  Student student;
  std::string::size_type max_name_length = 0;

  while (student.read(std::cin)) {
    max_name_length = std::max(max_name_length, student.name().size());
    students.push_back(student);
    std::cout << "\n";
  }
  std::cout << "\n\n";

  std::sort(students.begin(), students.end(), Student::compare);

  for (std::vector<Student>::size_type i = 0; i < students.size(); ++i) {
    std::cout << students[i].name()
              << std::string(max_name_length - students[i].name().size() + 1,
                             ' ');

    try {
      double course_grade = students[i].course_grade();
      std::string course_letter_grade = students[i].course_letter_grade();
      bool met_all_requirements = students[i].met_all_requirements();

      std::streamsize prec = std::cout.precision();
      std::cout << std::setprecision(3) << course_grade
                << std::setprecision(prec) << " [" << course_letter_grade << "]"
                << " [" << (met_all_requirements ? ("met all requirements")
                                                 : ("missing a requirement"))
                << "]" << std::endl;
    } catch (std::domain_error e) {
      std::cout << e.what() << std::endl;
    }
  }
}
