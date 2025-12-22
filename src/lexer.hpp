#pragma once

// Debug - disabled by default, can be enabled with -DDEBUG=1
#ifndef DEBUG
#define DEBUG 0
#endif

// Test - disabled by default, can be enabled with -DTEST=1
#ifndef TEST
#define TEST 0
#endif

#include "dbg.h"
#include "token.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Lexer {
  private:
    std::vector< Token > tokens{};
    std::string          source{};
    unsigned int         line{};
    unsigned int         column{};
    size_t               position{};

    void tokenize() {
        while ( position < source.size() ) {
            char        ch = source[position];
            std::string literal{};
            std::string lexeme{};
            Types       type{};
            switch ( ch ) {

                // Delimiters
                case '(': {
                    literal = "(";
                    lexeme  = "(";
                    type    = Types::OpenParenthesis;
                    position++;
                    break;
                }

                case '[': {
                    literal = "[";
                    lexeme  = "[";
                    type    = Types::OpenSquareBracket;
                    position++;
                    break;
                }

                case '{': {
                    literal = "{";
                    lexeme  = "{";
                    type    = Types::OpenCurlyBrace;
                    position++;
                    break;
                }

                case ')': {
                    literal = ")";
                    lexeme  = ")";
                    type    = Types::CloseParenthesis;
                    position++;
                    break;
                }

                case ']': {
                    literal = "]";
                    lexeme  = "]";
                    type    = Types::CloseSquareBracket;
                    position++;
                    break;
                }

                case '}': {
                    literal = "}";
                    lexeme  = "}";
                    type    = Types::CloseCurlyBrace;
                    position++;
                    break;
                }

                case ',': {
                    literal = ",";
                    lexeme  = ",";
                    type    = Types::Comma;
                    position++;
                    break;
                }

                case '.': {
                    literal = ".";
                    lexeme  = ".";
                    type    = Types::Period;
                    position++;
                    break;
                }

                case ';': {
                    literal = ";";
                    lexeme  = ";";
                    type    = Types::Semicolon;
                    position++;
                    break;
                }

                case ':': {
                    literal = ":";
                    lexeme  = ":";
                    type    = Types::Colon;
                    position++;
                    break;
                }

                default:
                    literal  = "";
                    lexeme   = "";
                    type     = Types::Error;
                    position = source.size();
            }

            Token token( type, literal, lexeme, line, column, position );
            tokens.push_back( token );
        }
    }

  public:
    Lexer( std::string source ) : source( source ) {
        line     = 1;
        column   = 1;
        position = 0;
        tokenize();
    }
};
