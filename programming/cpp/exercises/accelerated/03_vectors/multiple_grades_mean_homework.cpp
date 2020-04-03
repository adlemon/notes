// multiple_grades_mean_homework.cpp
// Compute course grades for multiple studnents where the final exam counts for
// 40%, the midterm exam grade counts for 20%, and the mean homework grade
// counts for 20%.

#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

int main() {
  const int NUM_HOMEWORK = 5;
  std::vector<std::string> names;
  std::vector<double> course_grades;

  std::string name;
  bool read_another = true;
  while (read_another) {
    std::cout << "Enter the name of the student or end-of-file if done: ";
    if (std::cin >> name) {
      names.push_back(name);

      double homework_total = 0.0;
      for (int i = 1; i <= NUM_HOMEWORK; i++) {
        double homework_grade;
        std::cout << "Enter the grade for homework " << i << " for " << name
                  << ": ";
        std::cin >> homework_grade;
        homework_total += homework_grade;
      }
      double homework_mean = homework_total / NUM_HOMEWORK;

      double midterm_exam, final_exam;
      std::cout << "Enter the midterm exam grade for " << name << ": ";
      std::cin >> midterm_exam;
      std::cout << "Enter the final exam grade for " << name << ": ";
      std::cin >> final_exam;

      double course_grade =
          0.4 * final_exam + 0.2 * midterm_exam + 0.4 * homework_mean;
      course_grades.push_back(course_grade);

      std::cout << std::endl;
    } else {
      read_another = false;
    }
  }

  std::cout << "Course Grades:\n";
  for (std::vector<std::string>::size_type i = 0; i < names.size(); i++) {
    std::streamsize prec = std::cout.precision();
    std::cout << names[i] << ": " << std::setprecision(3) << course_grades[i]
              << std::setprecision(prec) << "\n";
  }
}
