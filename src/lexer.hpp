#pragma once

#include "token.hpp"

#include <string>
#include <vector>

class Lexer {
  private:
    std::vector< Token > tokens{};
    std::string          source{};
    size_t               position = 0;
    size_t               offset   = 0;

    char next() {
        if ( position + 1 >= source.size() ) { return '\0'; }
        return source[position++];
    }

    char peek() {
        if ( position >= source.size() ) { return '\0'; }
        return source[position];
    }

    char peek_next() {
        if ( position + 1 >= source.size() ) { return '\0'; }
        return source[position + 1];
    }

    void eat_white_space() {
        while ( true ) {
            const char ch = peek();
            switch ( ch ) {
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
                    next();
                    break;
                }
                default: {
                    return;
                }
            }
        }
    }

    static bool is_alpha( const char ch ) {
        return ( ch >= 'a' && ch <= 'z' ) || ( ch >= 'A' && ch <= 'Z' ) ||
               ch == '_';
    }

    static bool is_digit( const char ch ) { return ch >= '0' && ch <= '9'; }

    static bool is_alnum( const char ch ) {
        return is_alpha( ch ) || is_digit( ch );
    }

    void tokenize() {
        eat_white_space();
        const char ch = next();
        switch ( ch ) {

            // Delimiters
            case '(': {
                tokens.emplace_back( Token::OpenParenthesis );
                break;
            }

            case '[': {
                tokens.emplace_back( Token::OpenSquareBracket );
                break;
            }

            case '{': {
                tokens.emplace_back( Token::OpenCurlyBrace );
                break;
            }

            case ')': {
                tokens.emplace_back( Token::CloseParenthesis );
                break;
            }

            case ']': {
                tokens.emplace_back( Token::CloseSquareBracket );
                break;
            }

            case '}': {
                tokens.emplace_back( Token::CloseCurlyBrace );
                break;
            }

            case ',': {
                tokens.emplace_back( Token::Comma );
                break;
            }

            case '.': {
                tokens.emplace_back( Token::Dot );
                break;
            }

            case ';': {
                tokens.emplace_back( Token::Semicolon );
                break;
            }

            case ':': {
                tokens.emplace_back( Token::Colon );
                break;
            }

            default: {
                tokens.emplace_back( Token::Error );
                break;
            }
        }
    }

  public:
    Lexer( std::string source ) : source( source ) {}

    std::vector< Token > &scan() {
        while ( position < source.size() ) { tokenize(); }

        tokens.emplace_back( Token::Eof );

        return tokens;
    }
};
