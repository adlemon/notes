// filter_students.cpp
// Filter students based on whether they passed the class or did all the
// homework.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct StudentData {
  std::string name;
  double midterm_exam, final_exam;
  std::vector<double> homeworks;
};

std::istream &read(std::istream &in, StudentData &student);

double course_grade(double midterm_exam, double final_exam,
                    double homework_avg);

double median(std::vector<double> v);

double course_grade(const StudentData &student);

bool is_failing(const StudentData &student);
bool did_all_hw(const StudentData &student);

std::vector<StudentData>
filter_students(std::vector<StudentData> &students,
                bool predicate(const StudentData &student));

std::ostream &print(std::ostream &out,
                    const std::vector<StudentData> &students);

int main() {
  std::vector<StudentData> students;
  StudentData student;
  while (read(std::cin, student)) {
    students.push_back(student);
    std::cout << '\n';
  }

  std::vector<StudentData> failing_students = students;
  std::vector<StudentData> passing_students =
      filter_students(failing_students, is_failing);

  if (passing_students.empty()) {
    std::cout << "\n\nNo students passed the class.\n";
  } else {
    std::cout << "\n\nThe students who passed the class are:\n";
    print(std::cout, passing_students);
  }

  if (failing_students.empty()) {
    std::cout << "\nNo students failed the class.\n";
  } else {
    std::cout << "\nThe students who failed the class are:\n";
    print(std::cout, failing_students);
  }

  std::vector<StudentData> students_did_all_hw = students;
  std::vector<StudentData> students_missing_hw =
      filter_students(students_did_all_hw, did_all_hw);

  if (students_did_all_hw.empty()) {
    std::cout << "\nNo students did all the homework.\n";
  } else {
    std::cout << "\nThe students who did all the homework are:\n";
    print(std::cout, students_did_all_hw);
  }
  if (students_missing_hw.empty()) {
    std::cout << "\nNo students are missing a homework.\n";
  } else {
    std::cout << "\nThe students who are missing a homework are:\n";
    print(std::cout, students_missing_hw);
  }
}

std::istream &read(std::istream &in, StudentData &student) {
  std::cout << "Enter the name of the student: ";
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

double course_grade(const StudentData &student) {
  return course_grade(student.midterm_exam, student.final_exam,
                      median(student.homeworks));
}

bool is_failing(const StudentData &student) {
  return course_grade(student) < 60;
}

bool did_all_hw(const StudentData &student) {
  return std::find(student.homeworks.begin(), student.homeworks.end(), 0) ==
         student.homeworks.end();
}

std::vector<StudentData>
filter_students(std::vector<StudentData> &students,
                bool predicate(const StudentData &student)) {
  std::vector<StudentData>::iterator filtered_students_begin =
      std::stable_partition(students.begin(), students.end(), predicate);

  std::vector<StudentData> filtered_students(filtered_students_begin,
                                             students.end());

  students.erase(filtered_students_begin, students.end());

  return filtered_students;
}

std::ostream &print(std::ostream &out,
                    const std::vector<StudentData> &students) {
  for (std::vector<StudentData>::const_iterator it = students.begin();
       it != students.end(); ++it) {
    out << it->name << '\n';
  }
  return out;
}
