// grades_mean_homework_safe.cpp
// Compute a course grade where the final exam counts for 40%, the midterm exam
// grade counts for 20%, and the mean homework grade counts for 20%. In this
// version of the program, we check to avoid division by zero if the user does
// not enter an homework grades.

#include <iomanip>
#include <ios>
#include <iostream>
#include <string>

int main() {
  std::string name;
  std::cout << "Enter the name of the student: ";
  std::cin >> name;

  double midterm_exam, final_exam;
  std::cout << "Enter the midterm exam grade for " << name << ": ";
  std::cin >> midterm_exam;
  std::cout << "Enter the final exam grade for " << name << ": ";
  std::cin >> final_exam;

  int num_homework = 0;
  double homework_total = 0;
  double homework_grade;
  std::cout << "Enter the homework grades for " << name
            << " or end-of-file if done: ";
  while (std::cin >> homework_grade) {
    homework_total += homework_grade;
    num_homework++;
  }

  if (num_homework == 0) {
    std::cout << "\nCannot compute course grade without any homework scores.\n";
    return 1;
  }
  double homework_mean = homework_total / num_homework;

  double course_grade =
      0.4 * homework_mean + 0.2 * midterm_exam + 0.4 * final_exam;
  std::streamsize prec = std::cout.precision();
  std::cout << "Course grade for " << name << ": " << std::setprecision(3)
            << course_grade << std::setprecision(prec) << "\n";
}
