// solve_quadratic.cpp
// Solve a quadratic equation with real coefficients.

#include <iostream>

class Quadratic_Degenerate {};
class Quadratic_NonRealRoots {};
class Sqrt_DidNotConverge {};

double abs(double x);
double sqrt(double x);
void solve_quadratic(double a, double b, double c);

int main() {
  std::cout << "Specify a quadratic equation with real coefficients:\n"
            << "  a * x^2 + b * x + c = 0.\n";

  double a, b, c;
  std::cout << "a = ";
  std::cin >> a;
  std::cout << "b = ";
  std::cin >> b;
  std::cout << "c = ";
  std::cin >> c;

  try {
    solve_quadratic(a, b, c);
  } catch (Quadratic_Degenerate) {
    std::cerr << "Given degenerate quadratic equation (that is, a = 0).\n";
  } catch (Quadratic_NonRealRoots) {
    std::cerr << "Given quadratic equation without real roots.\n";
  } catch (...) {
    std::cerr << "There was an unknown error.\n";
  }
}

double abs(double x) {
  if (x < 0) {
    return -x;
  }
  return x;
}

double sqrt(double x) {
  double r = x;
  for (int i = 0; i < 10; ++i) {
    r = (r + (x / r)) / 2;
  }

  if (abs(r * r - x) > 1e-6) {
    throw Sqrt_DidNotConverge{};
  }
  return r;
}

void solve_quadratic(double a, double b, double c) {
  if (a == 0.0) {
    throw Quadratic_Degenerate{};
  }

  double disc = b * b - 4 * a * c;
  if (disc < 0) {
    throw Quadratic_NonRealRoots{};
  }

  if (disc == 0) {
    std::cout << "repeated root: " << -b / (2 * a) << "\n";
    return;
  }

  double sqrt_disc = sqrt(disc);
  double root1 = (-b - sqrt_disc) / (2 * a);
  double root2 = (-b + sqrt_disc) / (2 * a);
  std::cout << "root1: " << root1 << "\n"
            << "root2: " << root2 << "\n";
}
