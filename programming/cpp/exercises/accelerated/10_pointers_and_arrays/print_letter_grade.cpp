// print_letter_grade.cpp
// Prompt the user for a numerical grade and print the corresponding letter
// grade.

#include <iostream>
#include <string>

std::string letter_grade(double grade);

int main() {
  double grade;
  std::cout << "Enter the numerical grade: ";
  std::cin >> grade;

  std::cout << "\nThe corresponding letter grade is: "
            << letter_grade(grade) << "\n";
}

std::string letter_grade(double grade) {
  static const double grade_cutoffs[] = {
    97, 94, 90, 87, 84, 80, 77, 74, 70, 60, 0
  };
  static const char* const letter_grades[] = {
    "A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D", "F"
  };
  static const size_t n_grades = sizeof(grade_cutoffs) / sizeof(*grade_cutoffs);

  for (size_t i = 0; i < n_grades; ++i) {
    if (grade >= grade_cutoffs[i]) {
      return letter_grades[i];
    }
  }

  return "?\?\?";
}
