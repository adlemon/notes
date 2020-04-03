// failing_students_resize.cpp
// Divide a vector of students into the passing and failing students.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct StudentInfo {
  std::string name;
  double midterm_exam, final_exam;
  std::vector<double> homeworks;
};

std::istream &read_student(std::istream &in, StudentInfo &student);
std::vector<StudentInfo> read_students(std::istream &in);
double course_grade(double midterm_exam, double final_exam,
                    double homework_avg);
double median(std::vector<double> v);
double course_grade(double midterm_exam, double final_exam,
                    std::vector<double> homeworks);
double course_grade(const StudentInfo &student);
bool is_failing(double course_grade);
bool is_failing(const StudentInfo &student);
std::vector<StudentInfo>
filter_failing_students(std::vector<StudentInfo> &students);

int main() {
  std::vector<StudentInfo> students = read_students(std::cin);
  std::vector<StudentInfo> failing_students = filter_failing_students(students);

  if (students.empty()) {
    std::cout << "\n\nThere are no passing students.\n";
  } else {
    std::cout << "\n\nThe passing students are:\n";
    for (std::vector<StudentInfo>::const_iterator it = students.begin();
         it != students.end(); ++it) {
      std::cout << it->name << '\n';
    }
  }

  if (failing_students.empty()) {
    std::cout << "\nThere are no failing students.\n";
  } else {
    std::cout << "\nThe failing students are:\n";
    for (std::vector<StudentInfo>::const_iterator it = failing_students.begin();
         it != failing_students.end(); ++it) {
      std::cout << it->name << '\n';
    }
  }
}

std::istream &read_student(std::istream &in, StudentInfo &student) {
  std::cout << "Enter the name of the student: ";
  in >> student.name;

  if (!in) {
    return in;
  }

  std::cout << "Enter the midterm exam grade for " << student.name << ": ";
  in >> student.midterm_exam;
  std::cout << "Enter the final exam grade for " << student.name << ": ";
  in >> student.final_exam;

  double homework;
  std::cout << "Enter the homework grades for " << student.name
            << " followed by an end-of-file: ";
  while (in >> homework) {
    student.homeworks.push_back(homework);
  }
  in.clear();

  return in;
}

std::vector<StudentInfo> read_students(std::istream &in) {
  StudentInfo student;
  std::vector<StudentInfo> students;
  while (read_student(in, student)) {
    std::cout << '\n';
    students.push_back(student);
  }
  in.clear();
  return students;
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

double course_grade(const StudentInfo &student) {
  return course_grade(student.midterm_exam, student.final_exam,
                      student.homeworks);
}

bool is_failing(double course_grade) { return course_grade < 60; }

bool is_failing(const StudentInfo &student) {
  return is_failing(course_grade(student));
}

std::vector<StudentInfo>
filter_failing_students(std::vector<StudentInfo> &students) {
  std::vector<StudentInfo>::size_type read_cursor = 0, write_cursor = 0;
  std::vector<StudentInfo> failing_students;
  while (read_cursor < students.size()) {
    if (is_failing(students[read_cursor])) {
      failing_students.push_back(students[read_cursor]);
    } else {
      students[write_cursor] = students[read_cursor];
      write_cursor++;
    }
    read_cursor++;
  }
  students.resize(write_cursor);

  return failing_students;
}
