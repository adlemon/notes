// student_course_grades_instrumented.cpp
// Read student grades, compute course grades, and partitioning students into
// passing and failing students. In addition, we instrument the class to
// represent a student's course grades to count the numbers of times that
// instances of the class are constructed, copied via construction, copied via
// assignment, and destroyed. This instrumentation allows us to compare
// different methods for partition the students into passing and failing
// students.

#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <vector>

template <class T> double median(std::vector<T> v);

double course_grade(double midterm_exam, double final_exam,
                    double homework_avg);
double course_grade(double midterm_exam, double final_exam,
                    std::vector<double> homeworks);
bool is_passing(double course_grade);

class StudentCourseGrades {
public:
  StudentCourseGrades() : midterm_exam_(0), final_exam_(0) {
    default_constructor_count++;
  }
  StudentCourseGrades(int grade)
      : midterm_exam_(grade), final_exam_(grade), homeworks_(10, grade) {}
  StudentCourseGrades(const StudentCourseGrades &other) {
    name_ = other.name_;
    midterm_exam_ = other.midterm_exam_;
    final_exam_ = other.final_exam_;
    homeworks_ = other.homeworks_;
    copy_constructor_count++;
  }
  StudentCourseGrades &operator=(const StudentCourseGrades &other) {
    if (&other != this) {
      copy_assignment_count++;
      name_ = other.name_;
      midterm_exam_ = other.midterm_exam_;
      final_exam_ = other.final_exam_;
      homeworks_ = other.homeworks_;
    }
    return *this;
  }
  ~StudentCourseGrades() { destructor_count++; }
  const std::string &name() const { return name_; }
  double course_grade() const {
    return ::course_grade(midterm_exam_, final_exam_, homeworks_);
  }
  bool is_passing() const { return ::is_passing(course_grade()); }
  static int default_constructor_count;
  static int copy_constructor_count;
  static int copy_assignment_count;
  static int destructor_count;
  static void reset_instrumentation_counts() {
    default_constructor_count = 0;
    copy_constructor_count = 0;
    copy_assignment_count = 0;
    destructor_count = 0;
  }
  static void print_instrumentation_counts() {
    std::cout << "default_constructor_count = " << default_constructor_count
              << "\n"
              << "copy_constructor_count    = " << copy_constructor_count
              << "\n"
              << "copy_assignment_count     = " << copy_assignment_count << "\n"
              << "destructor_count          = " << destructor_count << "\n";
  }

private:
  std::string name_;
  double midterm_exam_, final_exam_;
  std::vector<double> homeworks_;
};
int StudentCourseGrades::default_constructor_count = 0;
int StudentCourseGrades::copy_constructor_count = 0;
int StudentCourseGrades::copy_assignment_count = 0;
int StudentCourseGrades::destructor_count = 0;

bool is_passing_student(const StudentCourseGrades &student);
bool is_failing_student(const StudentCourseGrades &student);

int main() {
  std::vector<StudentCourseGrades> students;
  for (int grade = 1; grade <= 50; ++grade) {
    students.push_back(StudentCourseGrades(grade));
    students.push_back(StudentCourseGrades(100 - grade + 1));
  }

  {
    std::vector<StudentCourseGrades> passing_students = students;
    std::vector<StudentCourseGrades> failing_students;

    StudentCourseGrades::reset_instrumentation_counts();
    std::vector<StudentCourseGrades>::size_type i = 0;
    while (i < passing_students.size()) {
      if (passing_students[i].is_passing()) {
        ++i;
      } else {
        failing_students.push_back(passing_students[i]);
        passing_students.erase(passing_students.begin() + i);
      }
    }
  }
  std::cout << "1) Erase from vector:\n";
  StudentCourseGrades::print_instrumentation_counts();

  {
    std::vector<StudentCourseGrades> passing_students = students;
    std::vector<StudentCourseGrades> failing_students;

    StudentCourseGrades::reset_instrumentation_counts();
    std::remove_copy_if(passing_students.begin(), passing_students.end(),
                        std::back_inserter(failing_students),
                        is_passing_student);
    passing_students.erase(std::remove_if(passing_students.begin(),
                                          passing_students.end(),
                                          is_failing_student),
                           passing_students.end());
  }
  std::cout << "\n2) Copy and then remove from vector:\n";
  StudentCourseGrades::print_instrumentation_counts();

  {
    std::vector<StudentCourseGrades> passing_students = students;

    std::vector<StudentCourseGrades>::iterator it = std::stable_partition(
        passing_students.begin(), passing_students.end(), is_passing_student);
    std::vector<StudentCourseGrades> failing_students(it,
                                                      passing_students.end());
    passing_students.erase(it, passing_students.end());
  }
  std::cout << "\n3) Partition and then copy from vector:\n";
  StudentCourseGrades::print_instrumentation_counts();

  {
    std::list<StudentCourseGrades> passing_students, failing_students;
    std::copy(students.begin(), students.end(),
              std::back_inserter(passing_students));

    StudentCourseGrades::reset_instrumentation_counts();
    std::list<StudentCourseGrades>::iterator it = passing_students.begin();
    while (it != passing_students.end()) {
      if (it->is_passing()) {
        ++it;
      } else {
        it = passing_students.erase(it);
      }
    }
  }
  std::cout << "\n4) Copy and erase from list:\n";
  StudentCourseGrades::print_instrumentation_counts();
}

template <class T> double median(std::vector<T> v) {
  if (v.size() == 0) {
    return 0.0;
  }

  std::sort(v.begin(), v.end());

  typename std::vector<T>::size_type n = v.size();
  typename std::vector<T>::size_type m = n / 2;

  return ((n % 2) == 0) ? (v[m - 1] + v[m]) / 2.0 : v[m];
}

double course_grade(double midterm_exam, double final_exam,
                    double homework_avg) {
  return 0.2 * midterm_exam + 0.4 * final_exam + 0.4 * homework_avg;
}

double course_grade(double midterm_exam, double final_exam,
                    std::vector<double> homeworks) {
  return course_grade(midterm_exam, final_exam, median(homeworks));
}

bool is_passing(double course_grade) { return course_grade >= 60; }

bool is_passing_student(const StudentCourseGrades &student) {
  return student.is_passing();
}

bool is_failing_student(const StudentCourseGrades &student) {
  return !student.is_passing();
}
