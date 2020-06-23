// arithmetic_calculator.cpp
// Implement a simple calculator with variables. Variables are defined using the
// syntax "let <name> = <value>;". Valid arithmetic expressions satisfy the
// following grammar.
// Expression:
//   Term
//   Expression + Term
//   Expression - Term
// Term:
//   Atom
//   Term * Atom
//   Term / Atom
// Atom:
//   <double literal>
//   <variable name>
//   +Atom
//   -Atom
//   (Expression)

#include <iostream>
#include <string>
#include <vector>

constexpr char unknown_type = '?';
constexpr char end_statement_type = ';';
constexpr char quit_type = 'q';
constexpr char declare_type = 'D';
constexpr char name_type = 'N';
const std::string prompt = "> ";
const std::string result = "= ";
const std::string declare = "let";

struct Token {
  Token() : type(unknown_type) {}
  Token(char type) : type(type) {}
  Token(char type, double value) : type(type), value(value) {}
  Token(char type, const std::string &name) : type(type), name(name) {}

  char type;
  double value;
  std::string name;
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

struct Symbol {
  std::string name;
  double value;
};

class SymbolTable {
public:
  void declare(TokenStream &ts);
  double get(const std::string &name) const;
  void set(const std::string &name, double value);

private:
  std::vector<Symbol> symbols_;
};

double expression(TokenStream &ts, const SymbolTable &st);
double term(TokenStream &ts, const SymbolTable &st);
double atom(TokenStream &ts, const SymbolTable &st);

int main() {
  std::cout
      << "This program evaluates arithmetic expressions constructed\n"
      << "from double literals, parentheses, and the addition, subtraction,\n"
      << "multiplication, and division operators. Each expression must be\n"
      << "terminated by a " << end_statement_type
      << ". Variables can be defined using\n"
      << "the syntax `" << declare << " <name> = <value>;`. Enter " << quit_type
      << " to quit.\n\n";

  TokenStream ts;
  SymbolTable st;
  double value = 0.0;

  bool has_value = false;
  std::cout << prompt;
  try {
    while (std::cin) {
      try {
        Token t = ts.get();

        if (t.type == quit_type) {
          break;
        }
        if (t.type == end_statement_type) {
          if (has_value) {
            std::cout << result << value << "\n\n";
            has_value = false;
          } else {
            std::cout << "\n";
          }
          std::cout << prompt;
        } else if (t.type == declare_type) {
          st.declare(ts);
          has_value = false;
        } else {
          ts.putback(t);
          value = expression(ts, st);
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
  case '=':
  case end_statement_type:
  case quit_type:
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
    if (isalpha(c)) {
      std::string s(1, c);
      while (std::cin.get(c) && (isalpha(c) || isdigit(c))) {
        s += c;
      }
      std::cin.putback(c);
      if (s == declare) {
        return Token(declare_type);
      }
      return Token(name_type, s);
    } else {
      throw std::runtime_error("invalid token");
    }
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
  for (Token t = get(); t.type != end_statement_type; t = get())
    ;
}

void SymbolTable::declare(TokenStream &ts) {
  Token name_token = ts.get();
  if (name_token.type != name_type) {
    throw std::runtime_error("invalid variable name");
  }
  for (Symbol s : symbols_) {
    if (s.name == name_token.name) {
      throw std::runtime_error("variable " + s.name + " already declared");
    }
  }

  Token equals_token = ts.get();
  if (equals_token.type != '=') {
    throw std::runtime_error("expected =");
  }

  double value = expression(ts, *this);

  symbols_.push_back(Symbol{name_token.name, value});
}

double SymbolTable::get(const std::string &name) const {
  for (Symbol s : symbols_) {
    if (s.name == name) {
      return s.value;
    }
  }

  throw std::runtime_error("unknown variable: " + name);
}

void SymbolTable::set(const std::string &name, double value) {
  for (Symbol s : symbols_) {
    if (s.name == name) {
      s.value = value;
    }
  }

  throw std::runtime_error("unknown variable: " + name);
}

double expression(TokenStream &ts, const SymbolTable &st) {
  double value = term(ts, st);
  while (true) {
    Token t = ts.get();
    switch (t.type) {
    case '+':
      value += term(ts, st);
      break;
    case '-':
      value -= term(ts, st);
      break;
    default:
      ts.putback(t);
      return value;
    }
  }

  return value;
}

double term(TokenStream &ts, const SymbolTable &st) {
  double value = atom(ts, st);
  while (true) {
    Token t = ts.get();
    switch (t.type) {
    case '*':
      value *= atom(ts, st);
      break;
    case '/': {
      double denominator = atom(ts, st);
      if (denominator == 0.0) {
        throw std::runtime_error("division by zero");
      }
      value /= atom(ts, st);
      break;
    }
    default:
      ts.putback(t);
      return value;
    }
  }
}

double atom(TokenStream &ts, const SymbolTable &st) {
  Token t = ts.get();
  switch (t.type) {
  case '#':
    return t.value;
  case '+':
    return atom(ts, st);
  case '-':
    return -atom(ts, st);
  case name_type:
    return st.get(t.name);
  case '(': {
    double value = expression(ts, st);
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
