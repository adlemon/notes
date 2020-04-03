// course_grades_types.cpp
// Compute course grades for different types of students: undegraduates,
// graduates, students taking the class pass/fail, and students auditing the
// course.

#include "course_grades_types.h"

template <class T> T median(std::vector<T> v) {
  if (v.size() == 0) {
    throw std::domain_error("median of empty vector");
  }

  std::sort(v.begin(), v.end());

  typename std::vector<T>::size_type n = v.size();
  typename std::vector<T>::size_type m = n / 2;

  return ((n % 2) == 0) ? (v[m - 1] + v[m]) / 2 : v[m];
}

double course_grade(double midterm_exam, double final_exam,
                    double homework_average) {
  return 0.2 * midterm_exam + 0.4 * final_exam + 0.4 * homework_average;
}

double course_grade(double midterm_exam, double final_exam,
                    std::vector<double> homeworks) {
  return course_grade(midterm_exam, final_exam, median(homeworks));
}

std::string course_letter_grade(double course_grade) {
  if (course_grade >= 97) {
    return "A+";
  } else if (course_grade >= 94) {
    return "A";
  } else if (course_grade >= 90) {
    return "A-";
  } else if (course_grade >= 87) {
    return "B+";
  } else if (course_grade >= 84) {
    return "B";
  } else if (course_grade >= 80) {
    return "B-";
  } else if (course_grade >= 77) {
    return "C+";
  } else if (course_grade >= 74) {
    return "C";
  } else if (course_grade >= 70) {
    return "C-";
  } else if (course_grade >= 60) {
    return "D";
  }
  return "F";
}

std::istream &CoreStudent::read(std::istream &is) {
  std::cout << "Enter the name of the student: ";
  is >> name_;

  std::cout << "Enter the midterm exam grade for " << name_ << ": ";
  is >> midterm_exam_;

  std::cout << "Enter the final exam grade for " << name_ << ": ";
  is >> final_exam_;

  double homework;
  std::cout << "Enter the homework grades for " << name_
            << " followed by an end-of-file: ";
  while (is >> homework) {
    homeworks_.push_back(homework);
  }
  std::cin.clear();

  is_valid_ = true;
  return is;
}

bool CoreStudent::met_all_requirements() const {
  for (std::vector<double>::const_iterator it = homeworks_.begin();
       it != homeworks_.end(); ++it) {
    if (*it == 0) {
      return false;
    }
  }
  return true;
}

std::istream &GraduateStudent::read(std::istream &is) {
  CoreStudent::read(is);
  is_valid_ = false;

  std::cout << "Enter the thesis grade for " << name() << ": ";
  if (!(is >> thesis_)) {
    return is;
  }

  is_valid_ = true;
  return is;
}

std::istream &AuditStudent::read(std::istream &is) {
  std::cout << "Enter the name of the student: ";
  is_valid_ = true;
  return (is >> name_);
}

Student::Student(const Student &s) : student_(nullptr) {
  if (s.student_) {
    student_ = s.student_->clone();
  }
}

Student &Student::operator=(const Student &s) {
  if (&s != this) {
    delete student_;
    if (s.student_) {
      student_ = s.student_->clone();
    } else {
      student_ = nullptr;
    }
  }
  return *this;
}

std::istream &Student::read(std::istream &is) {
  delete student_;
  student_ = nullptr;

  char student_type;
  std::cout << "C: Core\n"
            << "G: Graduate\n"
            << "P: Pass/Fail\n"
            << "A: Auditor\n"
            << "Enter the type of student: ";
  if (!(is >> student_type)) {
    return is;
  }

  switch (student_type) {
  case 'C':
    student_ = new CoreStudent(is);
    break;
  case 'G':
    student_ = new GraduateStudent(is);
    break;
  case 'P':
    student_ = new PassFailStudent(is);
    break;
  case 'A':
    student_ = new AuditStudent(is);
    break;
  default:
    is.setstate(std::ios::failbit);
  }

  return is;
}
