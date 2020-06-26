// directions_of_stack_and_heap.cpp
// Empirically identify the directions of growth for the stack and heap.

#include <iostream>

int main() {
  int stack_variable_1 = 1;
  int stack_variable_2 = stack_variable_1 + 1;
  int stack_variable_3 = stack_variable_2 + 1;
  int stack_variable_4 = stack_variable_3 + 1;
  int stack_variable_5 = stack_variable_4 + 1;

  std::cout << "&stack_variable_1 = " << &stack_variable_1 << "\n"
            << "&stack_variable_2 = " << &stack_variable_2 << "\n"
            << "&stack_variable_3 = " << &stack_variable_3 << "\n"
            << "&stack_variable_4 = " << &stack_variable_4 << "\n"
            << "&stack_variable_5 = " << &stack_variable_5 << "\n";

  int *heap_variable_1 = new int;
  int *heap_variable_2 = new int;
  int *heap_variable_3 = new int;
  int *heap_variable_4 = new int;
  int *heap_variable_5 = new int;

  std::cout << "heap_variable_1 = " << heap_variable_1 << "\n"
            << "heap_variable_2 = " << heap_variable_2 << "\n"
            << "heap_variable_3 = " << heap_variable_3 << "\n"
            << "heap_variable_4 = " << heap_variable_4 << "\n"
            << "heap_variable_5 = " << heap_variable_5 << "\n";

  delete heap_variable_1;
  delete heap_variable_2;
  delete heap_variable_3;
  delete heap_variable_4;
  delete heap_variable_5;
}
