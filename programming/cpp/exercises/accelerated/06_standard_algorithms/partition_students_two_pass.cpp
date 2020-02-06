// partition_students_two_pass.cpp
// Partition a vector of students into the passing students and the failing
// students using a two-pass algorithm.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct StudentInfo {
  std::string name;
  double midterm_exam;
  double final_exam;
  std::vector<double> homeworks;
};

std::istream& read(std::istream& in, StudentInfo& student);
double course_grade(
  double midterm_exam,
  double final_exam,
  double homework_avg
);
double median(std::vector<double> v);
double course_grade(const StudentInfo& student);
bool is_passing(const StudentInfo& student);
bool is_failing(const StudentInfo& student);
std::vector<StudentInfo> extract_failing_students(
  std::vector<StudentInfo>& students
);
void print(const std::vector<StudentInfo>& students);

int main() {
  std::vector<StudentInfo> students;

  StudentInfo student;
  while (read(std::cin, student)) {
    students.push_back(student);
    std::cout << '\n';
  }
  std::cout << '\n';

  std::vector<StudentInfo> failing_students = extract_failing_students(
    students
  );

  if (students.empty()) {
    std::cout << "\nThere are no passing students.\n";
  } else {
    std::cout << "\nThe passing students are:\n";
    print(students);
  }

  if (failing_students.empty()) {
    std::cout << "\nThere are no failing students.\n";
  } else {
    std::cout << "\nThe failing students are:\n";
    print(failing_students);
  }
}

std::istream& read(std::istream& in, StudentInfo& student) {
  std::cout << "Enter the name of the student: ";
  in >> student.name;

  if (!in) {
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

double course_grade(
  double midterm_exam,
  double final_exam,
  double homework_avg
) {
  return 0.2 * midterm_exam + 0.4 * final_exam + 0.4 * homework_avg;
}

double median(std::vector<double> v) {
  std::sort(v.begin(), v.end());

  std::vector<double>::size_type n = v.size();
  std::vector<double>::size_type m = n / 2;
  return ((n % 2) == 0) ? (v[m-1] + v[m]) / 2 : v[m];
}

double course_grade(const StudentInfo& student) {
  return course_grade(
    student.midterm_exam,
    student.final_exam,
    median(student.homeworks)
  );
}


bool is_passing(const StudentInfo& student) {
  return course_grade(student) >= 60;
}

bool is_failing(const StudentInfo& student) {
  return !is_passing(student);
}

std::vector<StudentInfo> extract_failing_students(
  std::vector<StudentInfo>& students
) {
  std::vector<StudentInfo> failing_students;
  std::remove_copy_if(
    students.begin(),
    students.end(),
    std::back_inserter(failing_students),
    is_passing
  );

  students.erase(
    std::remove_if(
      students.begin(),
      students.end(),
      is_failing
    ),
    students.end()
  );

  return failing_students;
}

void print(const std::vector<StudentInfo>& students) {
  for (std::vector<StudentInfo>::const_iterator it = students.begin();
      it != students.end(); ++it) {
    std::cout << it->name << '\n';
  }
}
