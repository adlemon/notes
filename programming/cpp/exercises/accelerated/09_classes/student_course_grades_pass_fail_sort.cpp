// student_course_grades_pass_fail_sort.cpp
// Process grades for students who took a class pass/fail.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

char pass_fail_grade(double exam_average);

class StudentCourseGrade {
public:
  StudentCourseGrade() : midterm_exam_(0), final_exam_(0) {}
  StudentCourseGrade(std::istream &in) { read(in); }
  std::istream &read(std::istream &in);
  const std::string &name() const { return name_; }
  char pass_fail_grade() const;

private:
  std::string name_;
  double midterm_exam_, final_exam_;
};

bool compare(const StudentCourseGrade &s1, const StudentCourseGrade &s2);

int main() {
  std::vector<StudentCourseGrade> students;
  std::string::size_type max_name_length;

  StudentCourseGrade student;
  while (student.read(std::cin)) {
    students.push_back(student);
    max_name_length = std::max(max_name_length, student.name().size());
    std::cout << "\n";
  }
  std::cout << "\n";

  std::sort(students.begin(), students.end(), compare);

  for (std::vector<StudentCourseGrade>::const_iterator it = students.begin();
       it != students.end(); ++it) {
    std::cout << it->name()
              << std::string(max_name_length - it->name().size() + 1, ' ')
              << it->pass_fail_grade() << "\n";
  }
}

char pass_fail_grade(double exam_average) {
  return (exam_average > 60) ? 'P' : 'F';
}

std::istream &StudentCourseGrade::read(std::istream &in) {
  std::cout << "Enter the name of the student: ";
  if (!(in >> name_)) {
    return in;
  }

  std::cout << "Enter the midterm exam grade for " << name_ << ": ";
  in >> midterm_exam_;

  std::cout << "Enter the final exam grade for " << name_ << ": ";
  in >> final_exam_;

  return in;
}

char StudentCourseGrade::pass_fail_grade() const {
  return ::pass_fail_grade((midterm_exam_ + final_exam_) / 2);
}

bool compare(const StudentCourseGrade &s1, const StudentCourseGrade &s2) {
  char g1 = s1.pass_fail_grade(), g2 = s2.pass_fail_grade();
  if (g1 != g2) {
    return (g1 == 'P');
  }
  return s1.name() < s2.name();
}
