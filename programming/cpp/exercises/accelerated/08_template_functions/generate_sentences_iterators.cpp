// generate_sentences_iterators.cpp
// Generate a sentence according to a grammar.

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

typedef std::string Token;
typedef std::list<Token> TokenList;
typedef std::vector<TokenList> TokenLists;
typedef std::map<Token, TokenLists> Grammar;

bool is_symbol(const Token &t);
bool is_literal(const Token &t);
TokenList tokenize(const std::string &s);
Grammar read_grammar(std::istream &in);
int nrand(int n);

template <class T> void output_sentence(const Grammar &g, T out);

int main() {
  Grammar g = read_grammar(std::cin);

  for (int i = 0; i < 10; ++i) {
    std::cout << "(" << i + 1 << ") ";
    output_sentence(g, std::ostream_iterator<Token>(std::cout, " "));
    std::cout << "\n";
  }

  TokenLists token_lists;
  for (int i = 0; i < 10; ++i) {
    TokenList token_list;
    output_sentence(g, std::back_inserter(token_list));
    token_lists.push_back(token_list);
  }

  std::cout << "\n";
  int i = 1;
  for (TokenLists::const_iterator it = token_lists.begin();
       it != token_lists.end(); ++i, ++it) {
    std::cout << "(" << i << ") ";
    std::copy(it->begin(), it->end(),
              std::ostream_iterator<Token>(std::cout, " "));
    std::cout << "\n";
  }
}

bool is_symbol(const Token &t) {
  return !t.empty() && t[0] == '<' && t[t.size() - 1] == '>';
}

bool is_literal(const Token &t) { return !is_symbol(t); }

TokenList tokenize(const std::string &s) {
  TokenList tokens;

  std::string::const_iterator it = s.begin();
  while (it != s.end()) {
    it = std::find_if_not(it, s.end(), isspace);
    std::string::const_iterator jt = std::find_if(it, s.end(), isspace);
    if (it != jt) {
      tokens.push_back(std::string(it, jt));
    }
    it = jt;
  }

  return tokens;
}

Grammar read_grammar(std::istream &in) {
  Grammar g;

  std::string line;
  while (std::getline(in, line)) {
    TokenList tokens = tokenize(line);

    if (tokens.size() < 2) {
      throw std::invalid_argument("invalid grammar line: " + line);
    }

    g[*tokens.begin()].push_back(TokenList(++tokens.begin(), tokens.end()));
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

template <class T> void output_sentence(const Grammar &g, T out) {
  TokenList tokens;
  tokens.push_back("<sentence>");

  while (!tokens.empty()) {
    const Token token = tokens.back();
    tokens.pop_back();

    if (is_literal(token)) {
      *out = token;
    } else {
      Grammar::const_iterator expansions = g.find(token);
      if (expansions == g.end()) {
        throw std::logic_error("unknown token: " + token);
      }

      TokenList expansion =
          expansions->second[nrand(expansions->second.size())];

      for (TokenList::const_reverse_iterator it = expansion.rbegin();
           it != expansion.rend(); ++it) {
        tokens.push_back(*it);
      }
    }
  }
}
