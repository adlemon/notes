// grades_median_homework.cpp
// Compute a course grade where the final exam counts for 40%, the midterm exam
// grade counts for 20%, and the median homework grade counts for 20%.

#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::string name;
  std::cout << "Enter the student's name: ";
  std::cin >> name;

  double midterm_exam, final_exam;
  std::cout << "Enter the midterm and final exam grades: ";
  std::cin >> midterm_exam >> final_exam;

  std::vector<double> homework;
  double x;
  std::cout << "Enter the homework grades followed by end-of-file: ";
  while (std::cin >> x) {
    homework.push_back(x);
  }

  std::vector<double>::size_type num_homework = homework.size();
  if (num_homework == 0) {
    std::cout
      << "Cannot compute the course grade"
         " without any homework grades."
      << std::endl;
    return 1;
  }

  int m = num_homework / 2;
  std::sort(homework.begin(), homework.end());
  double homework_median = ((num_homework % 2) == 0)
                         ? (homework[m] + homework[m + 1]) / 2
                         : homework[m];

  std::streamsize prec = std::cout.precision();
  std::cout
    << "The course grade for " << name << " is "
    << std::setprecision(3)
    << 0.4 * final_exam + 0.2 * midterm_exam + 0.4 * homework_median
    << std::setprecision(prec)
    << "." << std::endl;

  return 0;
}
