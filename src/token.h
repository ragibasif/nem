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
    TT_INTEGER,    // 12345
    TT_FLOAT,      // 123.45
    TT_CHARACTER,  // 'a'
    TT_STRING,     // "abc"

    // Operators
    TT_ADD,      // +
    TT_SUBTRACT, // -
    TT_MULTIPLY, // *
    TT_DIVIDE,   // /
    TT_MODULO,   // %

    TT_BITWISE_AND,         // &
    TT_BITWISE_OR,          // |
    TT_BITWISE_XOR,         // ^
    TT_BITWISE_SHIFT_LEFT,  // <<
    TT_BITWISE_SHIFT_RIGHT, // >>

    TT_ADD_ASSIGNMENT,      // +=
    TT_SUBTRACT_ASSIGNMENT, // -=
    TT_MULTIPLY_ASSIGNMENT, // *=
    TT_DIVIDE_ASSIGNMENT,   // /=
    TT_MODULO_ASSIGNMENT,   // %=

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
    TT_BREAK,
    TT_CASE,
    TT_CONST,
    TT_CONTINUE,

    TT_DEFAULT,
    TT_DEFER,
    TT_ELSE,
    TT_FOR,

    TT_FUNCTION,
    TT_GOTO,
    TT_IF,
    TT_IMPORT,

    TT_RETURN,

    TT_SWITCH,
    TT_VARIABLE,

    // Internal
    TT_COUNT
};

#ifdef __cplusplus
}
#endif

#endif // TOKEN_H
