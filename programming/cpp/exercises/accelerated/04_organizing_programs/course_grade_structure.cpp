// course_grade_structure.cpp
// Use a structure to compute students' course grades.

#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "grade.h"
#include "student_info.h"

int main() {
  std::vector<StudentInfo> students;
  StudentInfo student;
  std::string::size_type max_name_length = 0;
  while (read(std::cin, student)) {
    max_name_length = std::max(max_name_length, student.name.size());
    students.push_back(student);
  }

  sort(students.begin(), students.end(), compare);

  for (std::vector<StudentInfo>::size_type i = 0; i < students.size(); i++) {
    std::cout << students[i].name
      << std::string(max_name_length - students[i].name.size() + 1, ' ');

    try {
      double course_grade = grade(students[i]);
      std::streamsize prec = std::cout.precision();
      std::cout << std::setprecision(3)
        << course_grade
        << std::setprecision(prec);
    } catch (std::domain_error e) {
      std::cout << e.what();
    }
    std::cout << std::endl;
  }
}
