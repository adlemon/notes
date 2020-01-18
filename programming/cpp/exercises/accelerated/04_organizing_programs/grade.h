#ifndef GRADE_H_
#define GRADE_H_
// grade.h
// Declare utilities for computing course grades.

#include <vector>

#include "student_info.h"

double grade(double midterm_exam, double final_exam, double homework_avg);
double grade(
  double midterm_exam,
  double final_exam,
  std::vector<double> homeworks
);
double grade(const StudentInfo& s);

#endif
