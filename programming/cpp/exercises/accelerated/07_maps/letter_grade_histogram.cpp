// letter_grade_histogram.cpp
// Read information about students' grades in a course. Then print a histogram
// of the letter grades.

#include <algorithm>
#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>

struct StudentGrades {
  std::string name;
  double midterm_exam, final_exam;
  std::vector<double> homeworks;
};

double course_grade(double midterm_exam, double final_exam,
                    double homework_avg);
double median(std::vector<double> v);
double course_grade(double midterm_exam, double final_exam,
                    std::vector<double> homeworks);
double course_grade(const StudentGrades &student);
char letter_grade(double grade);
char student_letter_grade(const StudentGrades &student);
std::istream &read(std::istream &in, StudentGrades &student);
std::map<char, int> compute_histogram(const std::vector<char> v);
std::ostream &print(std::ostream &out, const std::map<char, int> &m);

int main() {
  std::vector<StudentGrades> students_grades;
  StudentGrades student_grades;
  while (read(std::cin, student_grades)) {
    students_grades.push_back(student_grades);
    std::cout << "\n";
  }
  std::cout << "\n\n";

  std::vector<char> students_letter_grades;
  std::transform(students_grades.begin(), students_grades.end(),
                 std::back_inserter(students_letter_grades),
                 student_letter_grade);

  std::map<char, int> letter_grade_counts =
      compute_histogram(students_letter_grades);
  std::cout << "The distribution of course grades is:\n";
  print(std::cout, letter_grade_counts);
}

double course_grade(double midterm_exam, double final_exam,
                    double homework_avg) {
  return 0.2 * midterm_exam + 0.4 * final_exam + 0.4 * homework_avg;
}

double median(std::vector<double> v) {
  std::sort(v.begin(), v.end());

  std::vector<double>::size_type n = v.size();
  std::vector<double>::size_type m = n / 2;

  return ((n % 2) == 0) ? (v[m - 1] + v[m]) / 2 : v[m];
}

double course_grade(double midterm_exam, double final_exam,
                    std::vector<double> homeworks) {
  return course_grade(midterm_exam, final_exam, median(homeworks));
}

double course_grade(const StudentGrades &student) {
  return course_grade(student.midterm_exam, student.final_exam,
                      student.homeworks);
}

char letter_grade(double grade) {
  if (grade < 60) {
    return 'F';
  }
  if (grade < 70) {
    return 'D';
  }
  if (grade < 80) {
    return 'C';
  }
  if (grade < 90) {
    return 'B';
  }
  return 'A';
}

char student_letter_grade(const StudentGrades &student) {
  return letter_grade(course_grade(student));
}

std::istream &read(std::istream &in, StudentGrades &student) {
  std::cout << "Enter the name of the student or end-of-file if done: ";
  if (!(in >> student.name)) {
    return in;
  }

  std::cout << "Enter the midterm exam grade for " << student.name << ": ";
  in >> student.midterm_exam;

  std::cout << "Enter the final exam grade for " << student.name << ": ";
  in >> student.final_exam;

  std::cout << "Enter the homework grades for " << student.name
            << " followed by an end-of-file: ";
  double homework;
  student.homeworks.clear();
  while (in >> homework) {
    student.homeworks.push_back(homework);
  }
  in.clear();

  return in;
}

std::map<char, int> compute_histogram(const std::vector<char> v) {
  std::map<char, int> histogram;

  for (std::vector<char>::const_iterator it = v.begin(); it != v.end(); ++it) {
    histogram[*it]++;
  }

  return histogram;
}

std::ostream &print(std::ostream &out, const std::map<char, int> &m) {
  for (std::map<char, int>::const_iterator it = m.begin(); it != m.end();
       ++it) {
    out << it->first << ": " << it->second << "\n";
  }
  return out;
}
