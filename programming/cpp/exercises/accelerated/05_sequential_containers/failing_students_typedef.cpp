// failing_students_typedef.cpp
// Divide a collection of students (either a vector or a list) into the passing
// and failing students.

#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <vector>

struct StudentInfo {
  std::string name;
  double midterm_exam, final_exam;
  std::vector<double> homeworks;
};

// Uncomment one of the following typedefs.
// typedef std::vector<StudentInfo> student_container_type;
typedef std::list<StudentInfo> student_container_type;

student_container_type ReadStudents();
double course_grade(double midterm_exam, double final_exam,
                    double homework_avg);
double median(std::vector<double> v);
double course_grade(double midterm_exam, double final_exam,
                    std::vector<double> homeworks);
double course_grade(const StudentInfo &student);
bool is_failing(const StudentInfo &student);
student_container_type
filter_failing_students(student_container_type &students);

int main() {
  student_container_type students = ReadStudents();
  student_container_type failing_students = filter_failing_students(students);

  if (students.empty()) {
    std::cout << "\nThere are no passing students.\n";
  } else {
    std::cout << "\nThe passing students are:\n";
    for (student_container_type::const_iterator it = students.begin();
         it != students.end(); ++it) {
      std::cout << it->name << "\n";
    }
  }

  if (failing_students.empty()) {
    std::cout << "\nThere are no failing students.\n";
  } else {
    std::cout << "\nThe failing students are:\n";
    for (student_container_type::const_iterator it = failing_students.begin();
         it != failing_students.end(); ++it) {
      std::cout << it->name << "\n";
    }
  }
}

student_container_type ReadStudents() {
  student_container_type students;

  while (std::cin) {
    StudentInfo student;

    std::cout << "Enter the name for the next student of end-of-file if done: ";
    if (std::getline(std::cin, student.name)) {
      std::cout << "Enter the midterm exam score for " << student.name << ": ";
      std::cin >> student.midterm_exam;

      std::cout << "Enter the final exam score for " << student.name << ": ";
      std::cin >> student.final_exam;

      double homework;
      std::cout << "Enter the homework scores for " << student.name
                << " followed by an end-of-file: ";
      while (std::cin >> homework) {
        student.homeworks.push_back(homework);
      }
      std::cin.clear();
      students.push_back(student);
    }
    std::cout << "\n";
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

bool is_failing(const StudentInfo &student) {
  return course_grade(student) < 60;
}

student_container_type
filter_failing_students(student_container_type &students) {
  student_container_type failing_students;

  student_container_type::iterator it = students.begin();
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
