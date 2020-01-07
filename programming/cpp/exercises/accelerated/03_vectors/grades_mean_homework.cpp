// grades_running_totals.cpp
// Compute a course grade where the final exam counts for 40%, the midterm exam
// grade counts for 20%, and the mean homework grade counts for 20%.

#include <iomanip>
#include <ios>
#include <iostream>
#include <string>

int main() {
  std::string name;
  std::cout << "Enter the student's name: ";
  std::cin >> name;

  double midterm_exam, final_exam;
  std::cout << "Enter the midterm and final exam grades: ";
  std::cin >> midterm_exam >> final_exam;

  int count = 0;
  double sum = 0, x;
  std::cout << "Enter the homework grades followed by end-of-file: ";
  while (std::cin >> x) {
    sum += x;
    count++;
  }

  std::streamsize prec = std::cout.precision();
  std::cout
    << "The course grade for " << name << " is "
    << std::setprecision(3)
    << 0.4 * final_exam + 0.2 * midterm_exam + 0.4 * sum / count
    << std::setprecision(prec)
    << "." << std::endl;

  return 0;
}
