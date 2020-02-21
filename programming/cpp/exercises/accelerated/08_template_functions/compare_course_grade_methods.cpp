// compare_course_grade_methods.cpp
// Compare different grading schemes.

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <stdexcept>
#include <vector>

struct StudentCourseGrades {
  std::string name;
  double midterm_exam, final_exam;
  std::vector<double> homeworks;
};

std::istream& read(std::istream& in, StudentCourseGrades& student);
bool did_all_hw(const StudentCourseGrades& student);

double median(std::vector<double> v);
double mean(const std::vector<double> v);
double median_nonzero(const std::vector<double>& v);

double course_grade(
  double midterm_exam,
  double final_exam,
  double homework_avg
);

template <class HomeworkAverageFunction>
double course_grade(
  const StudentCourseGrades& student,
  HomeworkAverageFunction get_homework_average
);

template <class HomeworkAverageFunction>
double median_course_grade(
  const std::vector<StudentCourseGrades>& students,
  HomeworkAverageFunction get_homework_average
);

template <class HomeworkAverageFunction>
void write_analysis(
  std::ostream& out,
  const std::string& analysis_method_name,
  HomeworkAverageFunction get_homework_average,
  const std::vector<StudentCourseGrades>& students_did_all_hw,
  const std::vector<StudentCourseGrades>& students_missing_hw
);

int main() {
  std::vector<StudentCourseGrades> students_did_all_hw, students_missing_hw;

  StudentCourseGrades student;
  while (read(std::cin, student)) {
    if (did_all_hw(student)) {
      students_did_all_hw.push_back(student);
    } else {
      students_missing_hw.push_back(student);
    }
    std::cout << "\n";
  }
  std::cout << "\n\n";

  if (students_did_all_hw.empty()) {
    std::cout << "No student did all the homework.\n";
    return 1;
  }
  if (students_missing_hw.empty()) {
    std::cout << "Every student did all the homework.\n";
    return 1;
  }

  write_analysis(
    std::cout,
    "median of homework scores",
    median,
    students_did_all_hw,
    students_missing_hw
  );

  write_analysis(
    std::cout,
    "mean of homework scores",
    mean,
    students_did_all_hw,
    students_missing_hw
  );

  write_analysis(
    std::cout,
    "median of nonzero homework scores",
    median_nonzero,
    students_did_all_hw,
    students_missing_hw
  );
}

std::istream& read(std::istream& in, StudentCourseGrades& student) {
  std::cout << "Enter the name of the student: ";
  if (!getline(in, student.name)) {
    return in;
  }

  std::cout << "Enter the midterm exam grade for " << student.name << ": ";
  in >> student.midterm_exam;

  std::cout << "Enter the final exam grade for " << student.name << ": ";
  in >> student.final_exam;

  std::cout << "Enter the homework grades for " << student.name
            << " followed by an end-of-file: ";
  std::copy(
    std::istream_iterator<double>(in),
    std::istream_iterator<double>(),
    std::back_inserter(student.homeworks)
  );
  in.clear();

  return in;
}

bool did_all_hw(const StudentCourseGrades& student) {
  return std::find(
    student.homeworks.begin(),
    student.homeworks.end(),
    0
  ) == student.homeworks.end();
}

double median(std::vector<double> v) {
  if (v.empty()) {
    throw std::domain_error("median of empty vector");
  }

  std::sort(v.begin(), v.end());

  std::vector<double>::size_type n = v.size();
  std::vector<double>::size_type m = n / 2;

  return ((n % 2) == 0) ? (v[m-1] + v[m]) / 2: v[m];
}

double mean(const std::vector<double> v) {
  if (v.empty()) {
    throw std::domain_error("mean of empty vector");
  }

  return std::accumulate(
    v.begin(),
    v.end(),
    0.0
  ) / v.size();
}

double median_nonzero(const std::vector<double>& v) {
  std::vector<double> v_nonzero;
  std::remove_copy(
    v.begin(),
    v.end(),
    std::back_inserter(v_nonzero),
    0
  );

  if (v_nonzero.empty()) {
    throw std::domain_error(
      "median of nonzeros of vector without any nonzero elements"
    );
  }

  return median(v_nonzero);
}

double course_grade(
  double midterm_exam,
  double final_exam,
  double homework_avg
) {
  return 0.2 * midterm_exam + 0.4 * final_exam + 0.4 * homework_avg;
}

template <class HomeworkAverageFunction>
double course_grade(
  const StudentCourseGrades& student,
  HomeworkAverageFunction get_homework_average
) {
  return course_grade(
    student.midterm_exam,
    student.final_exam,
    get_homework_average(student.homeworks)
  );
}

template <class HomeworkAverageFunction>
double median_course_grade(
  const std::vector<StudentCourseGrades>& students,
  HomeworkAverageFunction get_homework_average
) {
  std::vector<double> course_grades;
  for (std::vector<StudentCourseGrades>::const_iterator it = students.begin();
      it != students.end(); ++it) {
    course_grades.push_back(course_grade(*it, get_homework_average));
  }
  return median(course_grades);
}

template <class HomeworkAverageFunction>
void write_analysis(
  std::ostream& out,
  const std::string& analysis_method_name,
  HomeworkAverageFunction get_homework_average,
  const std::vector<StudentCourseGrades>& students_did_all_hw,
  const std::vector<StudentCourseGrades>& students_missing_hw
) {
  out << analysis_method_name
      << ": median(did all hw) = "
      << median_course_grade(students_did_all_hw, get_homework_average)
      << ", median(missing hw) = "
      << median_course_grade(students_missing_hw, get_homework_average)
      << "\n";
}

