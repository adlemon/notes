// simple_vector_test.cpp
// Interactive test for the SimpleVector class.

#include "simple_vector.cpp"

int main() {
  SimpleVector<int> v;

  bool continue_repl = true;
  while (continue_repl) {
    switch (get_action()) {
    case VectorAction::Invalid:
      std::cout << "Invalid selection.\n\n";
      break;
    case VectorAction::Print:
      simple_vector_print(v);
      break;
    case VectorAction::PushBack:
      simple_vector_push_back(v);
      break;
    case VectorAction::Update:
      simple_vector_update(v);
      break;
    case VectorAction::Erase:
      simple_vector_erase(v);
      break;
    case VectorAction::EraseRange:
      simple_vector_erase_range(v);
      break;
    case VectorAction::Clear:
      simple_vector_clear(v);
      break;
    case VectorAction::Quit:
      continue_repl = false;
      break;
    }
  }

  {
    int arr[] = {1, 2, 3, 4, 5};
    SimpleVector<int> v;
    v.assign(arr, 5);
    std::cout << "v.size() = " << v.size() << "\n";
    for (SimpleVector<int>::size_type i = 0; i < v.size(); ++i) {
      std::cout << "v[" << i << "] = " << v[i] << "\n";
    }
  }
}

VectorAction get_action() {
  std::cout << "(1) Print the vector\n"
            << "(2) Push a new value onto the back of the vector\n"
            << "(3) Modifying an existing element of the vector\n"
            << "(4) Erase an element of the vector\n"
            << "(5) Erase a range of elements from the vector\n"
            << "(6) Clear the vector\n"
            << "(7) Quit\n"
            << "Choose an action: ";

  int a;
  std::cin >> a;
  std::cout << "\n";

  if (!(std::cin && 1 <= a && a <= 7)) {
    std::cin.clear();
    std::cin.ignore();
    return VectorAction::Invalid;
  }

  return static_cast<VectorAction>(a);
}

void simple_vector_print(const SimpleVector<int> &v) {
  if (v.size() == 0) {
    std::cout << "<empty>\n\n";
    return;
  }

  for (SimpleVector<int>::size_type i = 0; i < v.size(); ++i) {
    std::cout << "[" << i << "] => " << v[i] << "\n";
  }
  std::cout << "\n";
}

void simple_vector_push_back(SimpleVector<int> &v) {
  int val;
  std::cout << "Enter the value to append to the vector: ";
  if (!(std::cin >> val)) {
    std::cin.ignore();
    std::cin.clear();
    std::cout << "Invalid value.\n\n";
    return;
  }

  v.push_back(val);
  std::cout << "\n";
}

void simple_vector_update(SimpleVector<int> &v) {
  SimpleVector<int>::size_type i;
  std::cout << "Enter the index to update: ";
  if (!((std::cin >> i) && (i < v.size()))) {
    std::cin.clear();
    std::cin.ignore();
    std::cout << "Invalid index.\n\n";
    return;
  }

  int val;
  std::cout << "Enter the new value: ";
  if (!(std::cin >> val)) {
    std::cin.clear();
    std::cin.ignore();
    std::cout << "Invalid value.\n\n";
    return;
  }

  v[i] = val;
  std::cout << "\n";
}

void simple_vector_erase(SimpleVector<int> &v) {
  SimpleVector<int>::size_type i;
  std::cout << "Enter the index to erase: ";
  if (!((std::cin >> i) && (i < v.size()))) {
    std::cin.clear();
    std::cin.ignore();
    std::cout << "Invalid index.\n\n";
    return;
  }

  v.erase(v.begin() + i);
  std::cout << "\n";
}

void simple_vector_erase_range(SimpleVector<int> &v) {
  SimpleVector<int>::size_type i, j;
  std::cout << "Enter the first index in the range: ";
  if (!((std::cin >> i) && (i < v.size()))) {
    std::cin.clear();
    std::cin.ignore();
    std::cout << "Invalid index.\n\n";
  }

  std::cout << "Enter one past the last index in the range: ";
  if (!((std::cin >> j) && (i < j) && (j <= v.size()))) {
    std::cin.clear();
    std::cin.ignore();
    std::cout << "Invalid index.\n\n";
  }

  v.erase(v.begin() + i, v.begin() + j);
  std::cout << "\n";
}

void simple_vector_clear(SimpleVector<int> &v) { v.clear(); }
