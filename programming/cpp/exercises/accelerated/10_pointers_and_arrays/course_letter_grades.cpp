// course_letter_grades.cpp
// Read students' assignment scores and print their letter grades.

#include <algorithm>
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

std::string letter_grade(double grade);

class StudentCourseGrade {
  public:
    StudentCourseGrade(): midterm_exam_(0), final_exam_(0) {}
    StudentCourseGrade(std::istream& in) { read(in); }
    std::istream& read(std::istream& in);
    const std::string& name() const { return name_; }
    double course_grade() const {
      return ::course_grade(midterm_exam_, final_exam_, homeworks_);
    }
    std::string letter_grade() const {
      return ::letter_grade(course_grade());
    }
    bool operator<(const StudentCourseGrade& other) {
      return name_ < other.name();
    }
  private:
    std::string name_;
    double midterm_exam_, final_exam_;
    std::vector<double> homeworks_;
};

int main() {
  std::vector<StudentCourseGrade> students;
  StudentCourseGrade student;
  std::string::size_type max_name_length = 0;
  while (student.read(std::cin)) {
    students.push_back(student);
    max_name_length = std::max(max_name_length, student.name().size());
    std::cout << "\n";
  }
  std::cout << "\n";

  std::sort(students.begin(), students.end());

  std::cout << "\nThe course grades are:\n";
  for (std::vector<StudentCourseGrade>::const_iterator it = students.begin();
      it != students.end(); ++it) {
    std::cout << it->name()
              << std::string(max_name_length - it->name().size() + 1, ' ')
              << it->letter_grade() << "\n";
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
  return course_grade(
    midterm_exam,
    final_exam,
    median(homeworks)
  );
}

std::string letter_grade(double grade) {
  static const double grade_cutoffs[] = {
    97, 94, 90, 87, 84, 80, 77, 74, 70, 60, 0
  };
  static const std::string letter_grades[] = {
    "A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D", "F"
  };
  static const size_t n_grades = sizeof(grade_cutoffs) / sizeof(*grade_cutoffs);

  for (size_t i = 0; i < n_grades; ++i) {
    if (grade >= grade_cutoffs[i]) {
      return letter_grades[i];
    }
  }

  return "?\?\?";
}

std::istream& StudentCourseGrade::read(std::istream& in) {
  std::cout << "Enter the name of the student: ";
  if (!(in >> name_)) {
    return in;
  }

  std::cout << "Enter the midterm exam grade for " << name_ << ": ";
  in >> midterm_exam_;

  std::cout << "Enter the final exam grade for " << name_ << ": ";
  in >> final_exam_;

  double homework;
  homeworks_.clear();
  std::cout << "Enter the homework grades for " << name_
            << " followed by an end-of-file: ";
  while (in >> homework) {
    homeworks_.push_back(homework);
  }
  in.clear();

  return in;
}
