// compare_grading_methods.cpp
// Compare the median grades in a course using different grading methods.

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

struct StudentInfo {
  std::string name;
  double midterm_exam, final_exam;
  std::vector<double> homeworks;
};

double mean(const std::vector<double>& v);
double median(std::vector<double> v);
double median_nonzero(std::vector<double> v);

std::istream& read(std::istream& in, StudentInfo& student);
bool did_all_hw(const StudentInfo& student);

double course_grade(
  double midterm_exam,
  double final_exam,
  double homework_avg
);

double median_analysis(const std::vector<StudentInfo>& students);
double median_nonzero_analysis(const std::vector<StudentInfo>& students);
double mean_analysis(const std::vector<StudentInfo>& students);

void write_analysis(
  std::ostream& out,
  std::string analysis_name,
  double analysis_function(const std::vector<StudentInfo>& students),
  const std::vector<StudentInfo>& students_all_hw,
  const std::vector<StudentInfo>& students_missing_hw
);

int main() {
  std::vector<StudentInfo> students_all_hw, students_missing_hw;

  StudentInfo student;
  while (read(std::cin, student)) {
    if (did_all_hw(student)) {
      students_all_hw.push_back(student);
    } else {
      students_missing_hw.push_back(student);
    }
    std::cout << '\n';
  }
  std::cout << '\n';

  if (students_all_hw.empty()) {
    std::cout << "No student did all the homework.\n";
    return 1;
  }
  if (students_missing_hw.empty()) {
    std::cout << "Every student did all the homework.\n";
    return 1;
  }

  write_analysis(
    std::cout,
    "median",
    median_analysis,
    students_all_hw,
    students_missing_hw
  );

  write_analysis(
    std::cout,
    "mean",
    mean_analysis,
    students_all_hw,
    students_missing_hw
  );

  write_analysis(
    std::cout,
    "nonzero median",
    median_nonzero_analysis,
    students_all_hw,
    students_missing_hw
  );
}

double mean(const std::vector<double>& v) {
  return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
}

double median(std::vector<double> v) {
  if (v.empty()) {
    throw std::domain_error("median of an empty vector");
  }

  std::sort(v.begin(), v.end());

  std::vector<double>::size_type n = v.size();
  std::vector<double>::size_type m = n / 2;
  return ((n % 2) == 0) ? (v[m-1] + v[m]) / 2 : v[m];
}

double median_nonzero(std::vector<double> v) {
  std::vector<double> nonzeros;
  remove_copy(v.begin(), v.end(), std::back_inserter(nonzeros), 0);
  return median(nonzeros);
}

std::istream& read(std::istream& in, StudentInfo& student) {
  std::cout << "Enter the name of the student: ";
  in >> student.name;

  if (!in) {
    return in;
  }

  std::cout << "Enter the midterm exam grade for " << student.name << ": ";
  in >> student.midterm_exam;

  std::cout << "Enter the final exam grade for " << student.name << ": ";
  in >> student.final_exam;

  double homework;
  std::cout << "Enter the homework grades for " << student.name
            << " followed by an end-of-file: ";
  student.homeworks.clear();
  while (in >> homework) {
    student.homeworks.push_back(homework);
  }

  in.clear();
  return in;
}

bool did_all_hw(const StudentInfo& student) {
  return std::find(
    student.homeworks.begin(),
    student.homeworks.end(),
    0
  ) == student.homeworks.end();
}

double course_grade(
  double midterm_exam,
  double final_exam,
  double homework_avg
) {
  return 0.2 * midterm_exam + 0.4 * final_exam + 0.4 * homework_avg;
}

double course_grade_homework_median(const StudentInfo& s) {
  return course_grade(
    s.midterm_exam,
    s.final_exam,
    median(s.homeworks) ? !s.homeworks.empty() : 0
  );
}

double median_analysis(const std::vector<StudentInfo>& students) {
  std::vector<double> course_grades;
  std::transform(
    students.begin(),
    students.end(),
    std::back_inserter(course_grades),
    course_grade_homework_median
  );

  return median(course_grades);
}

double course_grade_homework_median_nonzero(const StudentInfo& student) {
  try {
    return course_grade(
      student.midterm_exam,
      student.final_exam,
      median_nonzero(student.homeworks)
    );
  } catch (std::domain_error) {
    return course_grade(
      student.midterm_exam,
      student.final_exam,
      0
    );
  }
}

double median_nonzero_analysis(const std::vector<StudentInfo>& students) {
  std::vector<double> course_grades;
  std::transform(
    students.begin(),
    students.end(),
    std::back_inserter(course_grades),
    course_grade_homework_median_nonzero
  );
  return median(course_grades);
}

double course_grade_homework_mean(const StudentInfo& student) {
  return course_grade(
    student.midterm_exam,
    student.final_exam,
    mean(student.homeworks)
  );
}

double mean_analysis(const std::vector<StudentInfo>& students) {
  std::vector<double> course_grades;
  std::transform(
    students.begin(),
    students.end(),
    std::back_inserter(course_grades),
    course_grade_homework_mean
  );

  return median(course_grades);
}

void write_analysis(
  std::ostream& out,
  std::string analysis_name,
  double analysis_function(const std::vector<StudentInfo>& students),
  const std::vector<StudentInfo>& students_all_hw,
  const std::vector<StudentInfo>& students_missing_hw
) {
  out << analysis_name << ":"
    << " median(students_all_hw) = " << analysis_function(students_all_hw)
    << ", median(students_missing_hw) = "
    << analysis_function(students_missing_hw)
    << '\n';
}
