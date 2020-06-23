// boolean_calculator.cpp
// Implement a simple calculator for Boolean expressions that satisfy the
// following grammar.
// * expression:
//     * clause
//     * expression | clause
// * clause:
//     * unit
//     * clause & unit
// * unit:
//     * atom
//     * !unit
// * atom:
//     * 0
//     * 1
//     * (expression)

#include <iostream>
#include <string>

constexpr char unknown = '?';
constexpr char print = ';';
constexpr char quit = 'q';
const std::string prompt = "> ";
const std::string result = "= ";

struct Token {
  Token() : type(unknown), value(false) {}
  Token(char type) : type(type), value(false) {}
  Token(char type, bool value) : type(type), value(value) {}

  char type;
  bool value;
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

bool expression(TokenStream &ts);
bool clause(TokenStream &ts);
bool unit(TokenStream &ts);
bool atom(TokenStream &ts);

int main() {
  std::cout << "This program evaluates Boolean expressions constructed from\n"
            << "the literals 0 and 1, parentheses, and the operators & and |.\n"
            << "Each expression must be terminated by a " << print << ". Enter "
            << quit << " to quit.\n\n";

  TokenStream ts;
  bool value = false;

  try {
    bool has_value = false;
    std::cout << prompt;
    while (std::cin) {
      try {
        Token t = ts.get();

        if (t.type == quit) {
          break;
        }
        if (t.type == print) {
          if (has_value) {
            std::cout << result << value << "\n\n";
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
  case '!':
  case '&':
  case '|':
  case print:
  case quit:
    return Token(c);
  case '0':
    return Token('#', false);
  case '1':
    return Token('#', true);
  default:
    throw std::runtime_error("invalid token");
  }
}

void TokenStream::putback(Token t) {
  if (has_putback_) {
    throw std::runtime_error("putback into TokenStream with existing putback");
  }
  has_putback_ = true;
  putback_ = t;
}

void TokenStream::flush() {
  for (Token t = get(); t.type != print; t = get())
    ;
}

bool expression(TokenStream &ts) {
  bool value = clause(ts);
  while (true) {
    Token t = ts.get();
    if (t.type == '|') {
      value |= clause(ts);
    } else {
      ts.putback(t);
      return value;
    }
  }
}

bool clause(TokenStream &ts) {
  bool value = unit(ts);
  while (true) {
    Token t = ts.get();
    if (t.type == '&') {
      value &= unit(ts);
    } else {
      ts.putback(t);
      return value;
    }
  }
}

bool unit(TokenStream &ts) {
  Token t = ts.get();
  if (t.type == '!') {
    return !unit(ts);
  }
  ts.putback(t);
  return atom(ts);
}

bool atom(TokenStream &ts) {
  Token t = ts.get();
  switch (t.type) {
  case '#':
    return t.value;
  case '(': {
    bool value = expression(ts);
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
