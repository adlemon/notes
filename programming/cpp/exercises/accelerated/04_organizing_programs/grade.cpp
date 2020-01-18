// grade.cpp
// Define utilities for computing course grades.

#include <stdexcept>

#include "median.h"
#include "student_info.h"

double grade(double midterm_exam, double final_exam, double homework_avg) {
  return 0.2 * midterm_exam + 0.4 * final_exam + 0.4 * homework_avg;
}

double grade(
  double midterm_exam,
  double final_exam,
  std::vector<double> homeworks
) {
  if (homeworks.empty()) {
    throw std::domain_error("course grade for student without homework grades");
  }

  return grade(midterm_exam, final_exam, median(homeworks));
}

double grade(const StudentInfo& s) {
  return grade(s.midterm_exam, s.final_exam, s.homeworks);
}
