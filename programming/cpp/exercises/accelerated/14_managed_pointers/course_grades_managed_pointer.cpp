// course_grades_managed_pointer.cpp
// Compute student course grades.

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

#include "managed_pointer.cpp"

double course_grade(double midterm_exam, double final_exam,
                    double homework_avg) {
  return 0.2 * midterm_exam + 0.4 * final_exam + 0.4 * homework_avg;
}

template <class T> double median(std::vector<T> v) {
  if (v.empty()) {
    throw std::domain_error("median of empty vector");
  }

  typename std::vector<T>::size_type n = v.size();
  typename std::vector<T>::size_type m = n / 2;

  std::sort(v.begin(), v.end());
  return ((n % 2) == 0) ? (v[m - 1] + v[m]) / 2 : v[m];
}

double course_grade(double midterm_exam, double final_exam,
                    std::vector<double> homeworks) {
  return course_grade(midterm_exam, final_exam, median(homeworks));
}

class CoreStudent {
public:
  CoreStudent() : midterm_exam_(0), final_exam_(0) {}
  CoreStudent(std::istream &is) { read(is); }
  virtual ~CoreStudent() {}

  std::istream &read(std::istream &is);

  const std::string &name() const { return name_; }

  virtual double course_grade() const {
    return ::course_grade(midterm_exam_, final_exam_, homeworks_);
  }

protected:
  std::string name_;
  double midterm_exam_, final_exam_;
  std::vector<double> homeworks_;
};

std::istream &CoreStudent::read(std::istream &is) {
  std::cout << "Enter the name of the student: ";
  if (!(is >> name_)) {
    return is;
  }

  std::cout << "Enter the midterm exam grade for " << name_ << ": ";
  is >> midterm_exam_;

  std::cout << "Enter the final exam grade for " << name_ << ": ";
  is >> final_exam_;

  std::cout << "Enter the homework grades for " << name_
            << " followed by an end-of-file: ";
  double homework;
  while (is >> homework) {
    homeworks_.push_back(homework);
  }
  is.clear();

  return is;
}

class GraduateStudent : public CoreStudent {
public:
  GraduateStudent() : thesis_(0) {}
  GraduateStudent(std::istream &is) { read(is); }

  std::istream &read(std::istream &is);

  double course_grade() const {
    return std::min(CoreStudent::course_grade(), thesis_);
  }

private:
  double thesis_;
};

std::istream &GraduateStudent::read(std::istream &is) {
  CoreStudent::read(is);
  std::cout << "Enter the thesis grade for " << name_ << ": ";
  return is >> thesis_;
}

class Student {
public:
  Student() {}
  Student(std::istream &is) { read(is); }

  std::istream &read(std::istream &);

  const std::string &name() const {
    if (student_) {
      return student_->name();
    }
    throw std::runtime_error("called name() on uninitialized Student");
  }

  double course_grade() const {
    if (student_) {
      return student_->course_grade();
    }
    throw std::runtime_error("called grade() on uninitialized Student");
  }

private:
  ManagedPointer<CoreStudent> student_;
};

std::istream &Student::read(std::istream &is) {
  std::cout << "U: Undergraduate\n"
            << "G: Graduate Student\n"
            << "Enter the type of student: ";
  char c;
  if (!(is >> c)) {
    return is;
  }

  if (c == 'U') {
    student_ = new CoreStudent(is);
  } else if (c == 'G') {
    student_ = new GraduateStudent(is);
  }

  return is;
}

bool compare_core_student_managed_pointers(ManagedPointer<CoreStudent> s1,
                                           ManagedPointer<CoreStudent> s2) {
  return s1->name() < s2->name();
}

bool compare_students(Student s1, Student s2) { return s1.name() < s2.name(); }

int main() {
  std::vector<Student> students;
  Student student;
  std::string::size_type max_name_length = 0;

  while (student.read(std::cin)) {
    students.push_back(student);
    max_name_length = std::max(max_name_length, student.name().size());
    std::cout << "\n";
  }
  std::cout << "\n\n";

  std::sort(students.begin(), students.end(), compare_students);

  for (std::vector<ManagedPointer<Student>>::size_type i = 0;
       i != students.size(); ++i) {
    std::cout << students[i].name()
              << std::string(max_name_length - students[i].name().size() + 1,
                             ' ');
    try {
      double course_grade = students[i].course_grade();
      std::streamsize prec = std::cout.precision();
      std::cout << std::setprecision(3) << course_grade
                << std::setprecision(prec) << std::endl;
    } catch (std::domain_error e) {
      std::cout << e.what() << std::endl;
    }
  }
}
