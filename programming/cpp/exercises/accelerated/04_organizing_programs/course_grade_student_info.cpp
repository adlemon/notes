// course_grade_student_info.cpp
// Read and store course grades in a structure.

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

struct StudentInfo {
  std::string name;
  double course_grade;
};

double median(std::vector<double> v);

double course_grade(
  double midterm_exam,
  double final_exam,
  double homework_avg
);
double course_grade(
  double midterm_exam,
  double final_exam,
  std::vector<double> homeworks
);
std::istream& ReadStudentInfo(std::istream& in, StudentInfo& student);
void ReadStudentInfos(std::vector<StudentInfo>& students);
bool compare(const StudentInfo& s1, const StudentInfo& s2);
void PrintStudentInfos(const std::vector<StudentInfo>& students);

int main() {
  std::vector<StudentInfo> students;
  ReadStudentInfos(students);

  std::sort(students.begin(), students.end(), compare);

  std::cout << std::string(2, '\n');
  PrintStudentInfos(students);
}

double median(std::vector<double> v) {
  std::sort(v.begin(), v.end());

  std::vector<double>::size_type n = v.size();
  std::vector<double>::size_type m = n / 2;

  return ((n % 2) == 0) ? (v[m-1] + v[m]) / 2 : v[m];
}

double course_grade(
  double midterm_exam,
  double final_exam,
  double homework_avg
) {
  return 0.2 * midterm_exam + 0.4 * final_exam + 0.4 * homework_avg;
}

double course_grade(
  double midterm_exam,
  double final_exam,
  std::vector<double> homeworks
  ) {
  return course_grade(midterm_exam, final_exam, median(homeworks));
}

std::istream& ReadStudentInfo(std::istream& in, StudentInfo& student) {
  if (!in) {
    return in;
  }

  std::cout << "Enter the name of the student or end-of-file if done: ";
  if (!(in >> student.name)) {
    return in;
  }

  double midterm_exam, final_exam;
  std::cout << "Enter the midterm exam grade for " << student.name << ": ";
  in >> midterm_exam;
  std::cout << "Enter the final exam grade for " << student.name << ": ";
  in >> final_exam;

  std::vector<double> homeworks;
  double homework;
  std::cout << "Enter the homework scores for " << student.name
            << " and end-of-file when done: ";
  while (in >> homework) {
    homeworks.push_back(homework);
  }
  in.clear();
  std::cout << "read " << homeworks.size() << " grades\n";

  student.course_grade = course_grade(midterm_exam, final_exam, homeworks);

  return in;
}

void ReadStudentInfos(std::vector<StudentInfo>& students) {
  StudentInfo student;
  while (ReadStudentInfo(std::cin, student)) {
    students.push_back(student);
  }
}

bool compare(const StudentInfo& s1, const StudentInfo& s2) {
  return s1.name < s2.name;
}

void PrintStudentInfos(const std::vector<StudentInfo>& students) {
  std::string::size_type max_name_length = 0;
  for (std::vector<StudentInfo>::size_type i = 0; i < students.size(); i++) {
    max_name_length = std::max(students[i].name.size(), max_name_length);
  }

  for (std::vector<StudentInfo>::size_type i = 0; i < students.size(); i++) {
    std::cout << std::setw(max_name_length) << students[i].name << ' '
              << students[i].course_grade << '\n';
  }
}
