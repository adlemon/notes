// student_course_grade_overall.cpp
// Analyze student course grades by storing the overall course grade in each
// student record (rather than storing the individual assignment grades).

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

double course_grade(
  double midterm_exam,
  double final_exam,
  double homework_avg
);

template <class T>
T median(std::vector<T> v);

double course_grade(
  double midterm_exam,
  double final_exam,
  std::vector<double> homeworks
);

class StudentCourseGrade {
  public:
    StudentCourseGrade(): course_grade_(0) {};
    StudentCourseGrade(std::istream& in) { read(in); }
    std::istream& read(std::istream& in);
    const std::string& name() const { return name_; }
    double course_grade() const { return course_grade_; }
  private:
    std::string name_;
    double course_grade_;
};

bool compare(const StudentCourseGrade& s1, const StudentCourseGrade& s2);

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
    std::streamsize prec = std::cout.precision();
    std::cout << it->name()
              << std::string(max_name_length - it->name().size() + 1, ' ')
              << std::setprecision(4) << it->course_grade()
              << std::setprecision(prec) << "\n";
  }
}

double course_grade(
  double midterm_exam,
  double final_exam,
  double homework_avg
) {
  return 0.2 * midterm_exam + 0.4 * final_exam + 0.4 * homework_avg;
}

template <class T>
T median(std::vector<T> v) {
  if (v.empty()) {
    throw std::domain_error("median of empty vector");
  }

  std::sort(v.begin(), v.end());

  typename std::vector<T>::size_type n = v.size();
  typename std::vector<T>::size_type m = n / 2;

  return ((n % 2) == 0) ? (v[m-1] + v[m]) / 2 : v[m];
}

double course_grade(
  double midterm_exam,
  double final_exam,
  std::vector<double> homeworks
) {
  return course_grade(midterm_exam, final_exam, median(homeworks));
}

std::istream& StudentCourseGrade::read(std::istream& in) {
  std::cout << "Enter the name of the student: ";
  if (!(in >> name_)) {
    return in;
  }

  double midterm_exam, final_exam;
  std::cout << "Enter the midterm exam grade for " << name_ << ": ";
  in >> midterm_exam;
  std::cout << "Enter the final exam grade for " << name_ << ": ";
  in >> final_exam;

  std::vector<double> homeworks;
  double homework;
  std::cout << "Enter the homework grades for " << name_
            << " followed by an end-of-file: ";
  while (in >> homework) {
    homeworks.push_back(homework);
  }
  in.clear();

  course_grade_ = ::course_grade(midterm_exam, final_exam, homeworks);

  return in;
}

bool compare(const StudentCourseGrade& s1, const StudentCourseGrade& s2) {
  return s1.name() < s2.name();
}
