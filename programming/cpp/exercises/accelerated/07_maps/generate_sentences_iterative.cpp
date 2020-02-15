// generate_sentences_iterative.cpp
// Generate sentences according to a grammar.

#include <cctype>
#include <cstdlib>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

typedef std::string Token;
typedef std::vector<Token> Tokens;
typedef std::vector<Tokens> Expansions;
typedef std::map<Token, Expansions> Grammar;

bool is_symbol(const Token& t);
bool is_literal(const Token& t);
Tokens tokenize(std::string s);
Grammar read_grammar(std::istream& in);
int nrand(int n);
Tokens generate_sentence(const Grammar& g);
std::ostream& print(std::ostream& out, const Tokens& ts);

int main() {
  Grammar g = read_grammar(std::cin);
  std::cout << "\n";

  for (int i = 0; i < 10; ++i) {
    std::cout << "Sentence #" << i + 1 << ":\n";
    print(std::cout, generate_sentence(g)) << "\n\n";
  }
}

bool is_symbol(const Token& t) {
  if (t.empty()) {
    return false;
  }

  return t[0] == '<' && t[t.size() - 1] == '>';
}

bool is_literal(const Token& t) {
  return !is_symbol(t);
}

Tokens tokenize(std::string s) {
  Tokens tokens;

  std::string::const_iterator it = s.begin();
  while (it != s.end()) {
    while (it != s.end() && isspace(*it)) {
      ++it;
    }

    std::string::const_iterator jt = it;
    while (jt != s.end() && !isspace(*jt)) {
      ++jt;
    }

    if (jt != it) {
      tokens.push_back(Token(it, jt));
    }

    it = jt;
  }

  return tokens;
}

Grammar read_grammar(std::istream& in) {
  Grammar g;

  std::string line;
  while (std::getline(in, line)) {
    Tokens ts = tokenize(line);

    if (ts.size() < 2) {
      throw std::invalid_argument("invalid grammar line: " + line);
    }

    g[*ts.begin()].push_back(Tokens(++ts.begin(), ts.end()));
  }

  return g;
}

int nrand(int n) {
  int bucket_size = RAND_MAX / n;

  int r;
  do {
    r = rand() / bucket_size;
  } while (r >= n);

  return r;
}

Tokens generate_sentence(const Grammar& g) {
  Tokens sentence, stack;
  stack.push_back("<sentence>");

  while (!stack.empty()) {
    Token t = stack[stack.size() - 1];
    stack.resize(stack.size() - 1);

    if (is_literal(t)) {
      sentence.push_back(t);
    } else {
      Grammar::const_iterator grammar_rule = g.find(t);
      if (grammar_rule == g.end()) {
        throw std::logic_error("unknown token" + t);
      }

      Tokens expansion = grammar_rule->second[nrand(grammar_rule->second.size())];
      for (Tokens::const_reverse_iterator it = expansion.rbegin();
          it != expansion.rend(); ++it) {
        stack.push_back(*it);
      }
    }
  }

  return sentence;
}

std::ostream& print(std::ostream& out, const Tokens& ts) {
  for (Tokens::const_iterator it = ts.begin(); it != ts.end(); ++it) {
    if (it != ts.begin()) {
      out << " ";
    }
    out << *it;
  }

  return out;
}
