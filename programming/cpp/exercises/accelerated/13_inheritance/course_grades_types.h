// course_grades_types.h
// Compute course grades for different types of students: undergraduates,
// graduates, students taking the class pass/fail, and students auditing the
// course.

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

template <class T> T median(std::vector<T> v);

double course_grade(double midterm_exam, double final_exam,
                    double homework_average);

double course_grade(double midterm_exam, double final_exam,
                    std::vector<double> homeworks);
std::string course_letter_grade(double course_grade);

class CoreStudent {
public:
  CoreStudent() : midterm_exam_(0), final_exam_(0), is_valid_(false) {
    std::cerr << "CoreStudent()\n";
  }
  CoreStudent(std::istream &is) {
    std::cerr << "CoreStudent(std::istream& is)\n";
    read(is);
  }
  virtual ~CoreStudent() {}
  virtual std::istream &read(std::istream &is);

  const std::string &name() const {
    std::cerr << "CoreStudent::name()\n";
    return name_;
  }
  bool is_valid() const { return is_valid_; }
  virtual bool met_all_requirements() const;

  virtual double course_grade() const {
    std::cerr << "CoreStudent::course_grade()\n";
    return ::course_grade(midterm_exam_, final_exam_, homeworks_);
  }
  virtual std::string course_letter_grade() const {
    return ::course_letter_grade(course_grade());
  }

  friend class Student;

protected:
  virtual CoreStudent *clone() const { return new CoreStudent(*this); }

  std::string name_;
  double midterm_exam_, final_exam_;
  std::vector<double> homeworks_;
  bool is_valid_;
};

class GraduateStudent : public CoreStudent {
public:
  GraduateStudent() : thesis_(0) { std::cerr << "GraduateStudent()\n"; }
  GraduateStudent(std::istream &is) {
    std::cerr << "GraduateStudent(std::istream& is)\n";
    read(is);
  }
  std::istream &read(std::istream &is);

  double course_grade() const {
    std::cerr << "GraduateStudent::course_grade()\n";
    return std::min(CoreStudent::course_grade(), thesis_);
  }
  bool met_all_requirements() const {
    return CoreStudent::met_all_requirements() && (thesis_ != 0);
  }

protected:
  GraduateStudent *clone() const { return new GraduateStudent(*this); }

private:
  double thesis_;
};

class PassFailStudent : public CoreStudent {
public:
  PassFailStudent(std::istream &is) {
    std::cerr << "PassFailStudent(std::istream& is)\n";
    read(is);
  }

  double course_grade() const {
    if (homeworks_.empty()) {
      std::cerr << "PassFailStudent::course_grade()\n";
      return (midterm_exam_ + final_exam_) / 2;
    }
    return CoreStudent::course_grade();
  }
  std::string course_letter_grade() const {
    if (course_grade() >= 60) {
      return "Pass";
    }
    return "Fail";
  }

protected:
  PassFailStudent *clone() const { return new PassFailStudent(*this); }
};

class AuditStudent : public CoreStudent {
public:
  AuditStudent() { std::cerr << "AuditStudent()\n"; }
  AuditStudent(std::istream &is) {
    std::cerr << "AuditStudent(std::istream& is)\n";
    read(is);
  }
  std::istream &read(std::istream &is);

  double course_grade() const {
    std::cerr << "AuditStudent::course_grade()\n";
    return 0.0;
  }
  std::string course_letter_grade() const { return "None"; }
  bool met_all_requirements() const { return true; }

protected:
  AuditStudent *clone() const { return new AuditStudent(*this); }
};

class Student {
public:
  Student() : student_(nullptr) {}
  Student(std::istream &is) : student_(nullptr) { read(is); }
  Student(const Student &student);
  Student &operator=(const Student &student);
  ~Student() { delete student_; }

  std::istream &read(std::istream &is);

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
    throw std::runtime_error("called course_grade() on uninitialized Student");
  }
  std::string course_letter_grade() const {
    if (student_) {
      return student_->course_letter_grade();
    }
    throw std::runtime_error(
        "called course_letter_grade() on uninitialized Student");
  }
  bool is_valid() const { return student_ != nullptr && student_->is_valid(); }
  bool met_all_requirements() const {
    if (student_) {
      return student_->met_all_requirements();
    }
    throw std::runtime_error(
        "called met_all_requirements() on uninitialized Student");
  }

  static bool compare(const Student &s1, const Student &s2) {
    return s1.name() < s2.name();
  }

private:
  CoreStudent *student_;
};
