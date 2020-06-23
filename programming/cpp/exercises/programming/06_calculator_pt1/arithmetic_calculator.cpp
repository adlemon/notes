// arithmetic_calculator.cpp
// Implement a basic calculator for arithmetic expressions that satisfy the
// following grammar.
// * expression:
//     * term
//     * expression + term
//     * expression - term
// * term:
//     * atom
//     * term * atom
//     * term / atom
// * atom:
//   * <double literal>
//   * (expression)
//   * +atom
//   * -atom

#include <iostream>
#include <string>

constexpr char unknown = '?';
constexpr char print = ';';
constexpr char quit = 'q';
const std::string prompt = "> ";
const std::string result = "= ";

struct Token {
  Token() : type(unknown) {}
  Token(char type) : type(type) {}
  Token(char type, double value) : type(type), value(value) {}

  char type;
  double value;
};

class TokenStream {
public:
  Token get();
  void putback(Token t);
  void flush();

private:
  bool has_putback_;
  Token putback_;
};

double expression(TokenStream &ts);
double term(TokenStream &ts);
double atom(TokenStream &ts);

int main() {
  std::cout
      << "This program evaluates arithmetic expressions constructed\n"
      << "from double literals, parentheses, and the addition, subtraction,\n"
      << "multiplication, and division operators. Each expression must be\n"
      << "terminated by a " << print << ". Enter " << quit << " to quit.\n\n";

  TokenStream ts;
  double value = 0.0;

  std::cout << prompt;
  bool has_value = false;
  try {
    while (std::cin) {
      try {
        Token t = ts.get();

        if (t.type == quit) {
          break;
        }
        if (t.type == print) {
          if (has_value) {
            std::cout << result << value << "\n\n";
            has_value = false;
          } else {
            std::cout << "\n";
          }
          std::cout << prompt;
        } else {
          ts.putback(t);
          value = expression(ts);
          has_value = true;
        }
      } catch (std::exception &e) {
        std::cerr << e.what() << std::endl << std::endl;
        ts.flush();
        std::cout << prompt;
      }
    }
  } catch (...) {
    std::cerr << "unknown error" << std::endl;
    return 1;
  }
}

Token TokenStream::get() {
  if (has_putback_) {
    has_putback_ = false;
    return putback_;
  }

  char c;
  std::cin >> c;
  switch (c) {
  case '(':
  case ')':
  case '+':
  case '-':
  case '*':
  case '/':
  case print:
  case quit:
    return Token(c);
  case '.':
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9': {
    std::cin.putback(c);
    double value;
    std::cin >> value;
    return Token('#', value);
  }
  default:
    throw std::runtime_error("invalid token");
  }
}

void TokenStream::putback(Token t) {
  if (has_putback_) {
    throw std::runtime_error("putback into TokenStream with existing putback");
  }
  putback_ = t;
  has_putback_ = true;
}

void TokenStream::flush() {
  for (Token t = get(); t.type != print;)
    ;
}

double expression(TokenStream &ts) {
  double value = term(ts);
  while (true) {
    Token t = ts.get();
    switch (t.type) {
    case '+': {
      value += term(ts);
      break;
    }
    case '-': {
      value -= term(ts);
      break;
    }
    default:
      ts.putback(t);
      return value;
    }
  }
}

double term(TokenStream &ts) {
  double value = atom(ts);
  while (true) {
    Token t = ts.get();
    switch (t.type) {
    case '*':
      value *= atom(ts);
      break;
    case '/': {
      double denominator = atom(ts);
      if (denominator == 0.0) {
        throw std::runtime_error("division by zero");
      }
      value /= denominator;
      break;
    }
    default:
      ts.putback(t);
      return value;
    }
  }
}

double atom(TokenStream &ts) {
  Token t = ts.get();
  switch (t.type) {
  case '#':
    return t.value;
  case '+':
    return atom(ts);
  case '-':
    return -atom(ts);
  case '(': {
    double value = expression(ts);
    t = ts.get();
    if (t.type != ')') {
      throw std::runtime_error("expected )");
    }
    return value;
  }
  default:
    throw std::runtime_error("expected atom");
  }
}
