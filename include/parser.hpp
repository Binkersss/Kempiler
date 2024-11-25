//
// Created by binker on 11/25/24.
//

#ifndef PARSER_HPP
#define PARSER_HPP

#include "node.hpp"

class Parser {
private:
  std::vector<Token> m_tokens;
  size_t m_index = 0;

  Token peek() const {
    if (m_index >= m_tokens.size()) return Token(TokenType::Eof);
    return m_tokens[m_index];
  }

  Token consume() {
    return m_tokens[m_index++];
  }

public:
  explicit Parser(std::vector<Token> tokens) : m_tokens(std::move(tokens)) {}

  std::optional<Node> parse() {
    if (peek().type == TokenType::Exit) {
      consume(); // consume 'exit'

      if (peek().type != TokenType::Int) {
        std::cerr << "Expected integer after 'exit'" << std::endl;
        return std::nullopt;
      }

      std::string exit_code = peek().value.value();
      consume(); // consume integer

      if (peek().type != TokenType::Semi) {
        std::cerr << "Expected semicolon" << std::endl;
        return std::nullopt;
      }
      consume(); // consume semicolon

      return Node{NodeType::Exit, ExitNode{exit_code}};
    }

    std::cerr << "Expected 'exit' statement" << std::endl;
    return std::nullopt;
  }
};



#endif //PARSER_HPP
