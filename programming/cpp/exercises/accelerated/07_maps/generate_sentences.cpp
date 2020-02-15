// generate_sentences.cpp
// Randomly generate sentences according to a grammar.

#include <cctype>
#include <cstdlib>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

typedef std::vector<std::string> GrammarRule;
typedef std::vector<GrammarRule> GrammarRules;
typedef std::map<std::string, GrammarRules> Grammar;

std::vector<std::string> tokenize(const std::string& s);
Grammar read_grammar(std::istream& in);
std::vector<std::string> generate_sentence(const Grammar& g);
bool is_symbol(const std::string& s);
bool is_literal(const std::string& s);
int nrand(int n);
void generate_token(
  const Grammar& g,
  const std::string& token,
  std::vector<std::string>& sentence
);
std::ostream& print(
  std::ostream& out,
  const std::vector<std::string>& sentence
);

int main() {
  const Grammar g = read_grammar(std::cin);

  for (int i = 0; i < 10; ++i) {
    if (i > 0) {
      std::cout << "\n";
    }

    std::cout << "Sentence #" << (i + 1) << ":\n";
    print(std::cout, generate_sentence(g)) << "\n";
  }
}

std::vector<std::string> tokenize(const std::string& s) {
  std::vector<std::string> v;

  std::string::const_iterator it = s.begin();
  while (it != s.end()) {
    while (it != s.end() && std::isspace(*it)) {
      ++it;
    }

    std::string::const_iterator jt = it;
    while (jt != s.end() && !std::isspace(*jt)) {
      ++jt;
    }

    if (it != jt) {
      v.push_back(std::string(it, jt));
    }
    it = jt;
  }

  return v;
}

Grammar read_grammar(std::istream& in) {
  Grammar g;

  std::string line;
  while (std::getline(in, line)) {
    std::vector<std::string> tokens = tokenize(line);

    if (!tokens.empty()) {
      g[tokens[0]].push_back(
        GrammarRule(tokens.begin() + 1, tokens.end())
      );
    }
  }

  return g;
}

std::vector<std::string> generate_sentence(const Grammar& g) {
  std::vector<std::string> sentence;

  generate_token(g, "<sentence>", sentence);

  return sentence;
}

bool is_symbol(const std::string& s) {
  return s.size() > 1 && s[0] == '<' && s[s.size() - 1] == '>';
}

bool is_literal(const std::string& s) {
  return !is_symbol(s);
}

int nrand(int n) {
  if (n <= 0 || n > RAND_MAX) {
    throw std::domain_error("argument to nrand is out of range");
  }

  const int bucket_size = RAND_MAX / n;

  int r;
  do {
    r = rand() / bucket_size;
  } while (r >= n);

  return r;
}

void generate_token(
  const Grammar& g,
  const std::string& token,
  std::vector<std::string>& sentence
) {
  if (is_literal(token)) {
    sentence.push_back(token);
    return;
  }

  Grammar::const_iterator it = g.find(token);
  if (it == g.end()) {
    throw std::logic_error("unknown rule");
  }

  const GrammarRules grammar_rules = it->second;
  const GrammarRule grammar_rule = grammar_rules[nrand(grammar_rules.size())];

  for (GrammarRule::const_iterator jt = grammar_rule.begin();
      jt != grammar_rule.end(); ++jt) {
    generate_token(g, *jt, sentence);
  }
}

std::ostream& print(
  std::ostream& out,
  const std::vector<std::string>& sentence
) {
  for (std::vector<std::string>::const_iterator it = sentence.begin();
      it != sentence.end(); ++it) {
    if (it != sentence.begin()) {
      out << " ";
    }
    out << *it;
  }
  return out;
}
