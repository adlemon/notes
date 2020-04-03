// student_course_grade_class.cpp
// Program to compute student grades, using a class to represent each student.

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

double median(std::vector<double> v);
double course_grade(double midterm_exam, double final_exam,
                    double homework_avg);
double course_grade(double midterm_exam, double final_exam,
                    const std::vector<double> &homeworks);
class StudentCourseGrade {
public:
  StudentCourseGrade() : midterm_exam_(0), final_exam_(0) {}
  StudentCourseGrade(std::istream &in) { read(in); }
  const std::string &name() const { return name_; }
  bool is_valid() const { return !homeworks_.empty(); }
  std::istream &read(std::istream &in);
  double grade() const;

private:
  std::string name_;
  double midterm_exam_, final_exam_;
  std::vector<double> homeworks_;
};
bool compare(const StudentCourseGrade &s1, const StudentCourseGrade &s2);

int main() {
  std::vector<StudentCourseGrade> students;
  std::string::size_type max_name_length = 0;

  StudentCourseGrade student;
  while (student.read(std::cin)) {
    max_name_length = std::max(max_name_length, student.name().size());
    students.push_back(student);
    std::cout << std::endl;
  }

  std::sort(students.begin(), students.end(), compare);

  std::cout << std::endl << std::endl;
  for (std::vector<StudentCourseGrade>::const_iterator it = students.begin();
       it != students.end(); ++it) {
    std::cout << it->name()
              << std::string(max_name_length - it->name().size() + 1, ' ');
    try {
      double g = it->grade();
      std::streamsize prec = std::cout.precision();
      std::cout << std::setprecision(3) << g << std::setprecision(prec)
                << std::endl;
    } catch (std::domain_error e) {
      std::cout << e.what() << std::endl;
    }
  }
}

double course_grade(double midterm_exam, double final_exam,
                    double homework_avg) {
  return 0.2 * midterm_exam + 0.4 * final_exam + 0.4 * homework_avg;
}

double median(std::vector<double> v) {
  if (v.empty()) {
    throw std::domain_error("median of empty vector");
  }

  std::sort(v.begin(), v.end());

  std::vector<double>::size_type n = v.size();
  std::vector<double>::size_type m = n / 2;

  return ((n % 2) == 0) ? (v[m - 1] + v[m]) / 2 : v[m];
}

double course_grade(double midterm_exam, double final_exam,
                    const std::vector<double> &homeworks) {
  return course_grade(midterm_exam, final_exam, median(homeworks));
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

  homeworks_.clear();
  std::cout << "Enter the homework grades for " << name_
            << " followed by an end-of-file: ";
  double homework_grade;
  while (in >> homework_grade) {
    homeworks_.push_back(homework_grade);
  }
  in.clear();

  return in;
}

double StudentCourseGrade::grade() const {
  return course_grade(midterm_exam_, final_exam_, homeworks_);
}

bool compare(const StudentCourseGrade &s1, const StudentCourseGrade &s2) {
  return s1.name() < s2.name();
}
