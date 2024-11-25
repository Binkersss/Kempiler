//
// Created by binker on 11/25/24.
//
#ifndef TOKENIZATION_HPP
#define TOKENIZATION_HPP
#include <iostream>
#include <string>
#include <vector>
#include <optional>

enum class TokenType {
    Exit,
    Int,
    Semi,
    Eof,
};

struct Token {
  TokenType type;
  std::optional<std::string> value;

  Token(TokenType type) : type(type) {}
  Token(TokenType type, const std::string& value) : type(type), value(value) {}

};

class Tokenizer {
private:
    std::string m_src;
    size_t m_index = 0;

    char peek() const {
        if (m_index >= m_src.length()) {
            return '\0';
        }
            return m_src[m_index];
    }

    char consume() {
      return m_src[m_index++];
    }
public:
  explicit Tokenizer(std::string src) : m_src(std::move(src)) {}

  std::vector<Token> tokenize() {
    std::vector<Token> tokens;

    while (m_index < m_src.length()) {
            if (std::isspace(peek())) {
              consume();
              continue;
            }

            if (peek() == 'e' && m_index + 3 < m_src.length()) {
              if (m_src.substr(m_index, 4) == "exit") {
                m_index += 4;
                tokens.push_back(Token(TokenType::Exit));
                continue;
              }
            }

            if (std::isdigit(peek())) {
              std::string num;
              while (std::isdigit(peek())) {
                num += consume();
              }

              tokens.push_back(Token(TokenType::Int, num));
              continue;
            }

            if (peek() == ';') {
              consume();
              tokens.push_back(Token(TokenType::Semi));
              continue;
            }

            std::cerr << "Invalid character: " << peek() << std::endl;
            exit(EXIT_FAILURE);
    }

    tokens.push_back(Token(TokenType::Eof));
    return tokens;
  }
};
#endif //TOKENIZATION_HPP
