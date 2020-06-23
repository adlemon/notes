// rational_numbers.cpp
// A class for rational numbers.

#include <iostream>

class RationalNumber {
public:
  class DivisionByZeroError {};
  RationalNumber() : numerator_(0), denominator_(1) {}
  RationalNumber(int numerator, int denominator)
      : numerator_(numerator), denominator_(denominator) {
    if (denominator_ == 0) {
      throw DivisionByZeroError();
    }
    Reduce();
  }
  RationalNumber(const RationalNumber &q)
      : numerator_(q.numerator_), denominator_(q.denominator_) {}

  friend std::ostream &operator<<(std::ostream &os, const RationalNumber &q);
  friend bool operator==(const RationalNumber &q1, const RationalNumber &q2);
  friend RationalNumber operator+(const RationalNumber &q1,
                                  const RationalNumber &q2);
  friend RationalNumber operator-(const RationalNumber &q1,
                                  const RationalNumber &q2);
  friend RationalNumber operator*(const RationalNumber &q1,
                                  const RationalNumber &q2);
  friend RationalNumber operator/(const RationalNumber &q1,
                                  const RationalNumber &q2);

private:
  void Reduce();
  int numerator_;
  int denominator_;
};

int gcd(int m, int n);
int lcm(int m, int n);

std::ostream &operator<<(std::ostream &os, const RationalNumber &q);
bool operator==(const RationalNumber &q1, const RationalNumber &q2);
RationalNumber operator+(const RationalNumber &q1, const RationalNumber &q2);
RationalNumber operator-(const RationalNumber &q1, const RationalNumber &q2);
RationalNumber operator*(const RationalNumber &q1, const RationalNumber &q2);
RationalNumber operator/(const RationalNumber &q1, const RationalNumber &q2);

int main() {
  RationalNumber q1{2, 3};
  RationalNumber q2{2, 4};

  std::cout << "q1 = " << q1 << "\n"
            << "q2 = " << q2 << "\n";

  std::cout << "\n"
            << "q1 + q2 = " << (q1 + q2) << "\n"
            << "q1 - q2 = " << (q1 - q2) << "\n"
            << "q1 * q2 = " << (q1 * q2) << "\n"
            << "q1 / q2 = " << (q1 / q2) << "\n"
            << "(q1 == q2) = " << (q1 == q2) << "\n"
            << "(q1 == q1) = " << (q1 == q1) << "\n";
}

int gcd(int m, int n) {
  while (n != 0) {
    int tmp = n;
    n = (m % n);
    m = tmp;
  }
  return m;
}

int lcm(int m, int n) { return (m * n) / gcd(m, n); }

void RationalNumber::Reduce() {
  int d = gcd(numerator_, denominator_);
  numerator_ /= d;
  denominator_ /= d;
}

std::ostream &operator<<(std::ostream &os, const RationalNumber &q) {
  return os << q.numerator_ << " / " << q.denominator_;
}

bool operator==(const RationalNumber &q1, const RationalNumber &q2) {
  return (q1.numerator_ == q2.numerator_) &&
         (q1.denominator_ == q2.denominator_);
}

RationalNumber operator+(const RationalNumber &q1, const RationalNumber &q2) {
  int common_denominator = lcm(q1.denominator_, q2.denominator_);
  return RationalNumber(q1.numerator_ * common_denominator / q1.denominator_ +
                            q2.numerator_ * common_denominator /
                                q2.denominator_,
                        common_denominator);
}

RationalNumber operator-(const RationalNumber &q1, const RationalNumber &q2) {
  int common_denominator = lcm(q1.denominator_, q2.denominator_);
  return RationalNumber(q1.numerator_ * common_denominator / q1.denominator_ -
                            q2.numerator_ * common_denominator /
                                q2.denominator_,
                        common_denominator);
}

RationalNumber operator*(const RationalNumber &q1, const RationalNumber &q2) {
  return RationalNumber(q1.numerator_ * q2.numerator_,
                        q1.denominator_ * q2.denominator_);
}

RationalNumber operator/(const RationalNumber &q1, const RationalNumber &q2) {
  if (q2.numerator_ == 0) {
    throw RationalNumber::DivisionByZeroError();
  }
  return RationalNumber(q1.numerator_ * q2.denominator_,
                        q1.denominator_ * q2.numerator_);
}
