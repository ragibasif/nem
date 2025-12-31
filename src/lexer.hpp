#pragma once

#include <cstdio>
#include <string>
#include <vector>

#include "token.hpp"

// Debug macro - disabled by default, can be enabled with -DDEBUG=1
#ifndef DEBUG
#define DEBUG 0
#endif

#define TRACE fprintf(stderr, "[%s:%d (%s)]\n", __FILE__, __LINE__, __func__);

namespace nem {

// TODO: Debug tracing

class Lexer {
 public:
  Lexer(std::string_view source) : source(source) {
#if DEBUG
    TRACE;
#endif
  }

  std::vector<Token> tokenize() {
#if DEBUG
    TRACE;
#endif
    std::vector<Token> tokens;

    while (!end()) {
      Token token = scan();
      if (token.type != TokenType::Comment) {
        tokens.emplace_back(token);
      }
    }

#if DEBUG
    for (const auto& token : tokens) {
      token.print();
    }
#endif

    return tokens;
  }

 private:
  std::string_view source;
  size_t start = 0;     // start of current lexeme
  size_t current = 0;   // current character being looked at
  size_t position = 0;  // absolute offset
  unsigned int line = 1;
  unsigned int column = 1;

  [[nodiscard]] static bool is_alpha(const char c) {
#if DEBUG
    TRACE;
#endif
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
  }

  [[nodiscard]] static bool is_alnum(const char c) {
#if DEBUG
    TRACE;
#endif
    return is_alpha(c) || is_digit(c);
  }

  [[nodiscard]] static bool is_digit(const char c) {
#if DEBUG
    TRACE;
#endif
    return c >= '0' && c <= '9';
  }

  [[nodiscard]] bool end() const {
#if DEBUG
    TRACE;
#endif
    return current >= source.size();
  }

  char next() {
#if DEBUG
    TRACE;
#endif
    char c = source[current];
    current++;
    column++;
    position++;
    return c;
  }

  [[nodiscard]] char peek() const {
#if DEBUG
    TRACE;
#endif
    if (end()) {
      return '\0';
    }
    return source[current];
  }

  [[nodiscard]] char peek_next() const {
#if DEBUG
    TRACE;
#endif
    if (end() || (current + 1 >= source.size())) {
      return '\0';
    }
    return source[current + 1];
  }

  [[nodiscard]] bool match(const char expected) {
#if DEBUG
    TRACE;
#endif
    if (end() || source[current] != expected) {
      return false;
    }
    current++;
    column++;
    return true;
  }

  Token make_token(TokenType type) const {
#if DEBUG
    TRACE;
#endif
    auto lexeme = source.substr(start, current - start);
    return Token{type, std::monostate{}, lexeme, position, line, column};
  }

  // white space and comments
  void skip() {
#if DEBUG
    TRACE;
#endif
    while (true) {
      char c = peek();
      switch (c) {
        case ' ': {
          [[fallthrough]];
        }
        case '\r': {
          [[fallthrough]];
        }
        case '\t': {
          next();
          break;
        }
        case '\n': {
          line++;
          column = 1;
          next();
          break;
        }
        case '/': {
          if (peek_next() == '/') {
            // C++ style comments: //
            while (peek() != '\n' && !end()) {
              next();
            }
          } else if (peek_next() == '*') {
            // C style comments-: /**/
            next();  // '/'
            next();  // '*'
            while (!(peek() == '*' && peek_next() == '/') && !end()) {
              if (peek() == '\n') {
                line++;
                column = 1;
              }
              next();
            }
            if (!end()) {
              next();  // '*'
              next();  // '/'
            }
          } else {
            return;  // division operator
          }
          break;
        }
        default:
          return;
      }
    }
  }

  Token operators(const char c) {
#if DEBUG
    TRACE;
#endif
    switch (c) {
      // single-char operators
      case '(': {
        return make_token(TokenType::OpenParenthesis);
      }

      case ')': {
        return make_token(TokenType::CloseParenthesis);
      }

      case '[': {
        return make_token(TokenType::OpenSquareBracket);
      }

      case ']': {
        return make_token(TokenType::CloseSquareBracket);
      }

      case '{': {
        return make_token(TokenType::OpenCurlyBrace);
      }

      case '}': {
        return make_token(TokenType::CloseCurlyBrace);
      }

      case ';': {
        return make_token(TokenType::Semicolon);
      }

      case ',': {
        return make_token(TokenType::Comma);
      }

      case '?': {
        return make_token(TokenType::Question);
      }

      case '~': {
        return make_token(TokenType::Invert);
      }

      // multi-char operators
      case '.': {
        if (match('.')) {
          if (match('.')) {
            return make_token(TokenType::Ellipsis);  // ...
          } else {
            return make_token(TokenType::Error);  // ".." is not a C token
          }
        } else {
          return make_token(TokenType::Dot);
        }
      }

      case '+': {
        if (match('+')) {
          return make_token(TokenType::Increment);  // ++
        } else if (match('=')) {
          return make_token(TokenType::AddAssignment);  // +=
        } else {
          return make_token(TokenType::Add);
        }
      }

      case '-': {
        if (match('-')) {
          return make_token(TokenType::Decrement);  // --
        } else if (match('=')) {
          return make_token(TokenType::SubtractAssignment);  // -=
        } else if (match('>')) {
          return make_token(TokenType::Arrow);  // ->
        } else {
          return make_token(TokenType::Subtract);
        }
      }

      case '>': {
        if (match('>')) {
          if (match('=')) {
            return make_token(TokenType::BitwiseShiftRightAssignment);  // >>=
          } else {
            return make_token(TokenType::BitwiseShiftRight);  // >>
          }
        } else if (match('=')) {
          return make_token(TokenType::GreaterEqual);  // >=
        } else {
          return make_token(TokenType::Greater);
        }
      }

      case '<': {
        if (match('<')) {
          if (match('=')) {
            return make_token(TokenType::BitwiseShiftLeftAssignment);  // <<=
          } else {
            return make_token(TokenType::BitwiseShiftLeft);  // <<
          }
        } else if (match('=')) {
          return make_token(TokenType::LessEqual);  // <=
        } else {
          return make_token(TokenType::Less);
        }
      }

      case '=': {
        return make_token(match('=') ? TokenType::Equal
                                     : TokenType::Assignment);
      }

      case '!': {
        return make_token(match('=') ? TokenType::NotEqual : TokenType::Not);
      }

      case '&': {
        if (match('&')) {
          return make_token(TokenType::LogicalAnd);
        } else if (match('=')) {
          return make_token(TokenType::BitwiseAndAssignment);
        } else {
          return make_token(TokenType::BitwiseAnd);
        }
      }

      case '|': {
        if (match('|')) {
          return make_token(TokenType::LogicalOr);
        } else if (match('=')) {
          return make_token(TokenType::BitwiseOrAssignment);
        } else {
          return make_token(TokenType::BitwiseOr);
        }
      }

      default: {
        return make_token(TokenType::Error);
      }
    }
  }

  TokenType identifier_type() {
#if DEBUG
    TRACE;
#endif
    std::string_view lexeme = source.substr(start, current - start);
    if (lexeme.empty()) return TokenType::Identifier;

    switch (lexeme[0]) {
      case 'a': {
        if (lexeme == "auto") {
          return TokenType::Auto;
        }
        if (lexeme == "asm") {
          return TokenType::Asm;
        }
        break;
      }

      case 'b': {
        if (lexeme == "break") {
          return TokenType::Break;
        }
        if (lexeme == "bool") {
          return TokenType::Bool;
        }
        break;
      }

      case 'c': {
        if (lexeme.length() > 1) {
          switch (lexeme[1]) {
            case 'a': {
              if (lexeme == "case") {
                return TokenType::Case;
              }
              break;
            }
            case 'h': {
              if (lexeme == "char") {
                return TokenType::Char;
              }
              break;
            }
            case 'o': {
              if (lexeme == "const") {
                return TokenType::Const;
              }
              if (lexeme == "continue") {
                return TokenType::Continue;
              }
              break;
            }
          }
        }
        break;
      }

      case 'd': {
        if (lexeme == "default") {
          return TokenType::Default;
        }
        if (lexeme == "do") {
          return TokenType::Do;
        }
        if (lexeme == "double") {
          return TokenType::Double;
        }
        break;
      }

      case 'e': {
        if (lexeme == "else") {
          return TokenType::Else;
        }
        if (lexeme == "enum") {
          return TokenType::Enum;
        }
        if (lexeme == "extern") {
          return TokenType::Extern;
        }
        break;
      }

      case 'f': {
        if (lexeme == "for") {
          return TokenType::For;
        }
        if (lexeme == "float") {
          return TokenType::Float;
        }
        if (lexeme == "false") {
          return TokenType::False;
        }
        break;
      }

      case 'g': {
        if (lexeme == "goto") {
          return TokenType::Goto;
        }
        break;
      }

      case 'i': {
        if (lexeme == "if") {
          return TokenType::If;
        }
        if (lexeme == "int") {
          return TokenType::Int;
        }
        if (lexeme == "import") {
          return TokenType::Import;
        }
        break;
      }

      case 'l': {
        if (lexeme == "long") {
          return TokenType::Long;
        }
        break;
      }

      case 'r': {
        if (lexeme == "return") {
          return TokenType::Return;
        }
        if (lexeme == "register") {
          return TokenType::Register;
        }
        break;
      }

      case 's': {
        if (lexeme.length() > 1) {
          switch (lexeme[1]) {
            case 'h': {
              if (lexeme == "short") {
                return TokenType::Short;
              }
              break;
            }

            case 'i': {
              if (lexeme == "sizeof") {
                return TokenType::Sizeof;
              }
              if (lexeme == "signed") {
                return TokenType::Signed;
              }
              break;
            }

            case 't': {
              if (lexeme == "static") {
                return TokenType::Static;
              }
              if (lexeme == "struct") {
                return TokenType::Struct;
              }
              break;
            }

            case 'w': {
              if (lexeme == "switch") {
                return TokenType::Switch;
              }
              break;
            }
          }
        }
        break;
      }

      case 't': {
        if (lexeme == "typedef") {
          return TokenType::Typedef;
        }
        if (lexeme == "true") {
          return TokenType::True;
        }
        break;
      }

      case 'u': {
        if (lexeme == "unsigned") {
          return TokenType::Unsigned;
        }
        if (lexeme == "union") {
          return TokenType::Union;
        }
        break;
      }

      case 'v': {
        if (lexeme == "void") {
          return TokenType::Void;
        }
        if (lexeme == "volatile") {
          return TokenType::Volatile;
        }
        break;
      }

      case 'w': {
        if (lexeme == "while") {
          return TokenType::While;
        }
        break;
      }
    }

    return TokenType::Identifier;
  }

  Token identifier() {
#if DEBUG
    TRACE;
#endif
    while (is_alnum(peek())) {
      next();
    }

    TokenType type = identifier_type();
    std::string_view lexeme = source.substr(start, current - start);

    return Token{type, std::string(lexeme), lexeme, position, line, column};
  }

  Token number() {
#if DEBUG
    TRACE;
#endif
    bool floating = false;

    while (is_digit(peek())) {
      next();
    }

    // floating point number
    if (peek() == '.' && is_digit(peek_next())) {
      floating = true;
      next();
      while (is_digit(peek())) {
        next();
      }
    }

    auto lexeme = source.substr(start, current - start);

    if (floating) {
      auto literal = std::stod(std::string(lexeme));
      return Token{
          TokenType::Floating, literal, lexeme, position, line, column};
    } else {
      auto literal = std::stoll(std::string(lexeme));
      return Token{TokenType::Integer, literal, lexeme, position, line, column};
    }
  }

  Token string() {
#if DEBUG
    TRACE;
#endif
    std::string literal;
    while (peek() != '"' && !end()) {
      if (peek() == '\n') {
        line++;
        column = 1;
      }

      if (peek() == '\\') {
        next();
        switch (peek()) {
          case 'n': {
            literal += '\n';
            break;
          }

          case 't': {
            literal += '\t';
            break;
          }
          case 'r': {
            literal += '\r';
            break;
          }
          case '\\': {
            literal += '\\';
            break;
          }
          case '"': {
            literal += '"';
            break;
          }

          default: {
            literal += peek();
            break;
          }
        }
      } else {
        literal += peek();
      }
      next();
    }
    if (end()) {
      return Token{TokenType::Error,
                   "Unterminated string literal",
                   "",
                   position,
                   line,
                   column};
    }

    next();

    auto lexeme = source.substr(start, current - start);
    return Token{TokenType::String, literal, lexeme, position, line, column};
  }

  Token character() {
#if DEBUG
    TRACE;
#endif
    char literal = 0;

    if (end()) {
      return Token{TokenType::Error,
                   "Unterminated character literal",
                   "",
                   position,
                   line,
                   column};
    }

    if (peek() == '\'') {
      return Token{TokenType::Error,
                   "Empty character literal",
                   "",
                   position,
                   line,
                   column};
    }

    if (peek() == '\\') {
      next();  // consume '\'
      char escape = next();
      switch (escape) {
        case 'n':
          literal = '\n';
          break;
        case 't':
          literal = '\t';
          break;
        case 'r':
          literal = '\r';
          break;
        case '0':
          literal = '\0';
          break;
        case '\\':
          literal = '\\';
          break;
        case '\'':
          literal = '\'';
          break;
        case '\"':
          literal = '\"';
          break;
        default:
          return Token{TokenType::Error,
                       "Unknown escape sequence",
                       "",
                       position,
                       line,
                       column};
      }
    } else {
      literal = next();
    }

    if (!match('\'')) {
      return Token{TokenType::Error,
                   "Unterminated character literal",
                   "",
                   position,
                   line,
                   column};
    }

    auto lexeme = source.substr(start, current - start);

    return Token{TokenType::Character,
                 static_cast<long long>(literal),
                 lexeme,
                 position,
                 line,
                 column};
  }

  Token scan() {
#if DEBUG
    TRACE;
#endif
    skip();
    start = current;

    if (end()) {
      return make_token(TokenType::Eof);
    }

    const char c = next();

    if (is_alpha(c)) {
      return identifier();
    } else if (is_digit(c)) {
      return number();
    } else if (c == '"') {
      return string();
    } else if (c == '\'') {
      return character();
    } else {
      return operators(c);
    }
  }
};

}  // namespace nem
