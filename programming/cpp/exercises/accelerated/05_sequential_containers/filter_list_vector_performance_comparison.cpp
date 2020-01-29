// filter_list_vector_performance_comparison.cpp
// Compare the execution times of filtering lists and vectors.

#include <chrono>
#include <iomanip>
#include <iostream>
#include <list>
#include <vector>

std::vector<int> GenerateVector(int n);
std::list<int> GenerateList(int n);
bool FilterElement(int i);
void FilterVector(std::vector<int>& v);
void FilterList(std::list<int>& lst);

struct PerformanceBenchmark {
  int n;
  std::chrono::duration<double> vector_execution;
  std::chrono::duration<double> list_execution;
};

int main() {
  std::vector<PerformanceBenchmark> performance_benchmarks;
  for (int n = 10; n <= 1000000; n *= 10) {
    PerformanceBenchmark performance_benchmark;
    performance_benchmark.n = n;

    std::vector<int> v = GenerateVector(n);
    std::list<int> lst = GenerateList(n);

    std::chrono::time_point<std::chrono::system_clock> start, end;

    start = std::chrono::system_clock::now();
    FilterVector(v);
    end = std::chrono::system_clock::now();
    performance_benchmark.vector_execution = (end - start);

    start = std::chrono::system_clock::now();
    FilterList(lst);
    end = std::chrono::system_clock::now();
    performance_benchmark.list_execution = (end - start);

    performance_benchmarks.push_back(performance_benchmark);
  }

  for (std::vector<PerformanceBenchmark>::const_iterator it =
      performance_benchmarks.begin();
      it != performance_benchmarks.end(); ++it) {
    std::cout << std::setw(7) << it->n
              << " " << std::setw(10) << it->vector_execution.count()
              << " " << std::setw(10) << it->list_execution.count() << "\n";
  }
}

std::vector<int> GenerateVector(int n) {
  std::vector<int> v;
  for (int i = 0; i < n; i++) {
    v.push_back(i);
  }
  return v;
}

std::list<int> GenerateList(int n) {
  std::list<int> lst;
  for (int i = 0; i < n; i++) {
    lst.push_back(i);
  }
  return lst;
}

bool FilterElement(int i) {
  return ((i % 2) == 1);
}

void FilterVector(std::vector<int>& v) {
  std::vector<int>::iterator it = v.begin();
  while (it != v.end()) {
    if (FilterElement(*it)) {
      it = v.erase(it);
    } else {
      ++it;
    }
  }
}
void FilterList(std::list<int>& lst) {
  std::list<int>::iterator it = lst.begin();
  while (it != lst.end()) {
    if (FilterElement(*it)) {
      it = lst.erase(it);
    } else {
      ++it;
    }
  }
}
