// course_grade_functions.cpp
// Use functions to compute a student's course grade.

#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

double median(std::vector<double> v);
double compute_course_grade(
  double midterm_exam,
  double final_exam,
  double homework_avg
);
double compute_course_grade(
  double midterm_exam,
  double final_exam,
  const std::vector<double>& homeworks
);
std::istream& read_homeworks(std::istream& in, std::vector<double>& homeworks);

int main() {
  std::string name;
  std::cout << "Enter the name of the student: ";
  std::cin >> name;

  double midterm_exam, final_exam;
  std::cout << "Enter the midterm exam grade for " << name << ": ";
  std::cin >> midterm_exam;
  std::cout << "Enter the final exam grade for " << name << ": ";
  std::cin >> final_exam;

  std::vector<double> homeworks;
  std::cout << "Enter the homework grades for " << name
    << " followed by an end-of-file: ";
  read_homeworks(std::cin, homeworks);

  try {
    double course_grade = compute_course_grade(midterm_exam, final_exam, homeworks);
    std::streamsize prec = std::cout.precision();
    std::cout << "The course grade for " << name << " is "
      << std::setprecision(3)
      << course_grade
      << std::setprecision(prec)
      << std::endl;
  } catch (std::domain_error) {
    std::cout << std::endl << "Unable to compute course grade for " << name
      << " because no homework grades were entered."
      << std::endl;
    return 1;
  }

  return 0;
}

double median(std::vector<double> v) {
  if (v.empty()) {
    throw std::domain_error("median of an empty vector");
  }

  std::sort(v.begin(), v.end());
  std::vector<double>::size_type n = v.size();
  std::vector<double>::size_type m = n / 2;
  return ((n % 2) == 0) ? (v[m-1] + v[m]) / 2 : v[m];
}

double compute_course_grade(
  double midterm_exam,
  double final_exam,
  double homework_avg
) {
  return 0.2 * midterm_exam + 0.4 * final_exam + 0.4 * homework_avg;
}

double compute_course_grade(
  double midterm_exam,
  double final_exam,
  const std::vector<double>& homeworks
) {
  if (homeworks.empty()) {
    throw std::domain_error("student has done no homework");
  }

  return compute_course_grade(midterm_exam, final_exam, median(homeworks));
}

std::istream& read_homeworks(std::istream& in, std::vector<double>& homeworks) {
  if (in) {
    homeworks.clear();

    double x;
    while (in >> x) {
      homeworks.push_back(x);
    }

    in.clear();
  }

  return in;
}
