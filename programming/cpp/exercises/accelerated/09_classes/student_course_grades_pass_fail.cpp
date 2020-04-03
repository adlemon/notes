// student_course_grades_pass_fail.cpp
// Process course grades for students taking a class pass/fail.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

double pass_fail_grade(double exam_average);
class StudentCourseGrade {
public:
  StudentCourseGrade() : midterm_exam_(0), final_exam_(0) {}
  StudentCourseGrade(std::istream &in) { read(in); }
  std::istream &read(std::istream &in);
  const std::string &name() const { return name_; }
  char PassFailGrade() const;

private:
  std::string name_;
  double midterm_exam_, final_exam_;
};

bool compare(const StudentCourseGrade &s1, const StudentCourseGrade &s2);

int main() {
  std::vector<StudentCourseGrade> students;
  std::string::size_type max_name_length = 0;

  StudentCourseGrade student;
  while (student.read(std::cin)) {
    students.push_back(student);
    max_name_length = std::max(max_name_length, student.name().size());
    std::cout << "\n";
  }
  std::cout << "\n\n";

  std::sort(students.begin(), students.end(), compare);

  for (std::vector<StudentCourseGrade>::const_iterator it = students.begin();
       it != students.end(); ++it) {
    std::cout << it->name()
              << std::string(max_name_length - it->name().size() + 1, ' ')
              << it->PassFailGrade() << "\n";
  }
}

double pass_fail_grade(double exam_average) {
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

char StudentCourseGrade::PassFailGrade() const {
  return pass_fail_grade((midterm_exam_ + final_exam_) / 2);
}

bool compare(const StudentCourseGrade &s1, const StudentCourseGrade &s2) {
  return s1.name() < s2.name();
}
