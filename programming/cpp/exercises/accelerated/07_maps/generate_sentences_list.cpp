// generate_sentences_list.cpp
// Randomly generate sentences that satisfy a given grammar.

#include <cctype>
#include <cstdlib>
#include <iostream>
#include <list>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

const int NUM_SENTENCES_TO_GENERATE = 10;

typedef std::string Token;
typedef std::vector<Token> Expansion;
typedef std::vector<Expansion> Expansions;
typedef std::map<Token, Expansions> Grammar;
typedef std::list<Token> Sentence;

Expansion tokenize(const std::string& s);
Grammar read_grammar(std::istream& in);
Sentence generate_sentence(const Grammar& grammar);
bool is_symbol(const Token& token);
bool is_literal(const Token& token);
int nrand(int n);
void expand_token(
  const Grammar& grammar,
  const Token& token,
  Sentence& sentence
);
std::ostream& print(std::ostream& out, const Sentence& sentence);

int main() {
  const Grammar grammar = read_grammar(std::cin);

  for (int i = 0; i < NUM_SENTENCES_TO_GENERATE; ++i) {
    if (i > 0) {
      std::cout << '\n';
    }

    std::cout << "Sentence #" << i + 1 << ":\n";
    print(std::cout, generate_sentence(grammar)) << '\n';
  }
}

Expansion tokenize(const std::string& s) {
  Expansion tokens;

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
      tokens.push_back(std::string(it, jt));
    }
    it = jt;
  }

  return tokens;
}

Grammar read_grammar(std::istream& in) {
  Grammar grammar;

  std::string line;
  while (std::getline(in, line)) {
    Expansion tokens = tokenize(line);

    if (!tokens.empty()) {
      grammar[*tokens.begin()].push_back(
        Expansion(tokens.begin() + 1, tokens.end())
      );
    }
  }

  return grammar;
}

Sentence generate_sentence(const Grammar& grammar) {
  Sentence sentence;
  expand_token(grammar, "<sentence>", sentence);
  return sentence;
}

bool is_symbol(const Token& token) {
  if (token.empty()) {
    return false;
  }

  return token[0] == '<' && token[token.size() - 1] == '>';
}

bool is_literal(const Token& token) {
  return !is_symbol(token);
}

int nrand(int n) {
  int bucket_size = RAND_MAX / n;

  int r;
  do {
    r = rand() / bucket_size;
  } while (r >= n);

  return r;
}

void expand_token(
  const Grammar& grammar,
  const Token& token,
  Sentence& sentence
) {
  if (is_literal(token)) {
    sentence.push_back(token);
    return;
  }

  Grammar::const_iterator it = grammar.find(token);
  if (it == grammar.end()) {
    throw std::logic_error("invalid token: " + token);
  }

  const Expansions& expansions = it->second;
  const Expansion& expansion = expansions[nrand(expansions.size())];

  for (Expansion::const_iterator token = expansion.begin();
      token != expansion.end(); ++token) {
    expand_token(grammar, *token, sentence);
  }
}

std::ostream& print(std::ostream& out, const Sentence& sentence) {
  for (Sentence::const_iterator it = sentence.begin();
      it != sentence.end(); ++it) {
    if (it != sentence.begin()) {
      out << ' ';
    }
    out << *it;
  }

  return out;
}
