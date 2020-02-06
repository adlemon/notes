e/ failing_students_vector.cpp
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

std::vector<StudentInfo> ReadStudents();
double course_grade(double midterm_exam, double final_exam,
                    double homework_avg);
double median(std::vector<double> v);
double course_grade(double midterm_exam, double final_exam,
                    const std::vector<double>& homeworks);
double course_grade(const StudentInfo& student);
bool is_failing(const StudentInfo& student);
std::vector<StudentInfo> FilterFailingStudents(
    std::vector<StudentInfo>& students);
void PrintStudents(const std::vector<StudentInfo>& students);

int main() {
  std::vector<StudentInfo> students = ReadStudents();

  std::vector<StudentInfo> failing_students = FilterFailingStudents(students);

  if (students.empty()) {
    std::cout << "\nThere were no passing students.\n";
  } else {
    std::cout << "\nThe passing students were:\n";
    PrintStudents(students);
  }

  if (failing_students.empty()) {
    std::cout << "\nThere were no failing students.\n";
  } else {
    std::cout << "\nThe failing students were:\n";
    PrintStudents(failing_students);
  }
}

std::vector<StudentInfo> ReadStudents() {
  std::vector<StudentInfo> students;

  while (std::cin) {
    StudentInfo student;
    std::cout << "Enter the name of the next student or end-of-file if done: ";
    if (std::cin >> student.name) {
      std::cout << "Enter the midterm exam grade for " << student.name << ": ";
      std::cin >> student.midterm_exam;

      std::cout << "Enter the final exam grade for " << student.name << ": ";
      std::cin >> student.final_exam;

      double homework_grade;
      std::cout << "Enter the homework grades for " << student.name
                << " and end-of-file when done: ";
      while (std::cin >> homework_grade) {
        student.homeworks.push_back(homework_grade);
      }
      std::cin.clear();

      students.push_back(student);
    }
    std::cout << '\n';
  }

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
  return ((n % 2) == 0) ? (v[m-1] + v[m]) / 2 : v[m];
}

double course_grade(double midterm_exam, double final_exam,
                    const std::vector<double>& homeworks) {
  return course_grade(midterm_exam, final_exam, median(homeworks));
}

double course_grade(const StudentInfo& student) {
  return course_grade(student.midterm_exam, student.final_exam,
                      student.homeworks);
}

bool is_failing(const StudentInfo& student) {
  return course_grade(student) < 60;
}

std::vector<StudentInfo> FilterFailingStudents(
    std::vector<StudentInfo>& students) {
  std::vector<StudentInfo> failing_students;

  std::vector<StudentInfo>::iterator it = students.begin();
  while (it != students.end()) {
    if (is_failing(*it)) {
      failing_students.push_back(*it);
      it = students.erase(it);
    } else {
      ++it;
    }
  }

  return failing_students;
}

void PrintStudents(const std::vector<StudentInfo>& students) {
  for (std::vector<StudentInfo>::const_iterator it = students.begin();
      it != students.end(); ++it) {
    std::cout << it->name << '\n';
  }
}
