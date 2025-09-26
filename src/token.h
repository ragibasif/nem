/*
 * File: token.h
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 */

#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

// The list of tokens.
enum TokenType {
    // Special tokens
    TT_UNKNOWN,
    TT_EOF,
    TT_COMMENT,

    // Literals
    TT_IDENTIFIER, // main
    TT_NUMBER,     // 12345
    TT_DIGIT,      // [0-9]
    TT_INTEGER,    // 12345
    TT_DOULBE,
    TT_FLOAT,     // 123.45
    TT_CHARACTER, // 'a'
    TT_STRING,    // "abc"

    // Operators
    TT_PLUS,   // +
    TT_MINUS,  // -
    TT_STAR,   // *
    TT_SLASH,  // /
    TT_MODULO, // %
    TT_INVERT, // ~

    TT_BITWISE_AND,         // &
    TT_BITWISE_OR,          // |
    TT_BITWISE_XOR,         // ^
    TT_BITWISE_SHIFT_LEFT,  // <<
    TT_BITWISE_SHIFT_RIGHT, // >>

    TT_PLUS_ASSIGNMENT,   // +=
    TT_MINUS_ASSIGNMENT,  // -=
    TT_STAR_ASSIGNMENT,   // *=
    TT_SLASH_ASSIGNMENT,  // /=
    TT_MODULO_ASSIGNMENT, // %=

    TT_BITWISE_AND_ASSIGNMENT,         // &=
    TT_BITWISE_OR_ASSIGNMENT,          // |=
    TT_BITWISE_XOR_ASSIGNMENT,         // ^=
    TT_BITWISE_SHIFT_LEFT_ASSIGNMENT,  // <<=
    TT_BITWISE_SHIFT_RIGHT_ASSIGNMENT, // >>=

    TT_LOGICAL_AND, // &&
    TT_LOGICAL_OR,  // ||
    TT_ARROW,       // ->
    TT_INCREMENT,   // ++
    TT_DECREMENT,   // --

    TT_EQUAL,      // ==
    TT_LESS,       // <
    TT_GREATER,    // >
    TT_ASSIGNMENT, // =
    TT_NOT,        // !
    TT_QUESTION,   // ?

    TT_NOT_EQUAL,     // !=
    TT_LESS_EQUAL,    // <=
    TT_GREATER_EQUAL, // >=
    TT_DEFINE,        // :=
    TT_ELLIPSIS,      // ...

    // Delimiters
    TT_OPEN_PARENTHESIS,     // (
    TT_OPEN_SQUARE_BRACKET,  // [
    TT_OPEN_CURLY_BRACE,     // {
    TT_CLOSE_PARENTHESIS,    // )
    TT_CLOSE_SQUARE_BRACKET, // ]
    TT_CLOSE_CURLY_BRACE,    // }

    TT_COMMA,     // ,
    TT_PERIOD,    // .
    TT_SEMICOLON, // ;
    TT_COLON,     // :

    // Keywords
    TT_AUTO,
    TT_BREAK,
    TT_CASE,
    TT_CONST,
    TT_CONTINUE,
    TT_PRINT,
    TT_TRUE,
    TT_FALSE,

    TT_DEFAULT,
    TT_DO,
    // TT_DEFER,
    TT_ELSE,
    TT_FOR,
    TT_ENUM,
    TT_EXTERN,
    TT_INT,
    TT_CHAR,
    TT_LONG,
    TT_REGISTER,
    TT_SHORT,
    TT_SIGNED,
    TT_SIZEOF,
    TT_STATIC,
    TT_STRUCT,
    TT_TYPEDEF,
    TT_UNION,
    TT_UNSIGNED,
    TT_VOLATILE,
    TT_WHILE,

    TT_FUNCTION,
    TT_GOTO,
    TT_IF,
    TT_IMPORT,

    TT_RETURN,

    TT_SWITCH,
    TT_VARIABLE, // [A-Za-z_]+ [A-Za-z0-9_]*
    TT_TYPE,

    // built-in data types
    TT_VOID,
    TT_BOOL,
    TT_INT8,   // char
    TT_UINT8,  // unsigned char
    TT_INT16,  // short
    TT_UINT16, // unsigned short
    TT_INT32,  // int
    TT_UINT32, // unsigned int
    TT_INT64,  // long long
    TT_UINT64, // unsigned long long
    TT_FLT32,  // float
    TT_FLT64,  // double

    // Internal
    TT_COUNT
};

struct Token {
    enum TokenType type;
    char          *literal;
};

#ifdef __cplusplus
}
#endif

#endif // TOKEN_H
