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
enum {
    // Special tokens
    UNKNOWN,
    EOF,
    COMMENT,

    // Literals
    IDENTIFIER, // main
    INTEGER,    // 12345
    FLOAT,      // 123.45
    CHARACTER,  // 'a'
    STRING,     // "abc"

    // Operators
    ADD,      // +
    SUBTRACT, // -
    MULTIPLY, // *
    DIVIDE,   // /
    MODULO,   // %

    BITWISE_AND,         // &
    BITWISE_OR,          // |
    BITWISE_XOR,         // ^
    BITWISE_SHIFT_LEFT,  // <<
    BITWISE_SHIFT_RIGHT, // >>
    BITWISE_AND_NOT,     // &^

    ADD_ASSIGNMENT,      // +=
    SUBTRACT_ASSIGNMENT, // -=
    MULTIPLY_ASSIGNMENT, // *=
    DIVIDE_ASSIGNMENT,   // /=
    MODULO_ASSIGNMENT,   // %=

    BITWISE_AND_ASSIGNMENT,         // &=
    BITWISE_OR_ASSIGNMENT,          // |=
    BITWISE_XOR_ASSIGNMENT,         // ^=
    BITWISE_SHIFT_LEFT_ASSIGNMENT,  // <<=
    BITWISE_SHIFT_RIGHT_ASSIGNMENT, // >>=

    LOGICAL_AND, // &&
    LOGICAL_OR,  // ||
    ARROW,       // ->
    INCREMENT,   // ++
    DECREMENT,   // --

    EQUAL,      // ==
    LESS,       // <
    GREATER,    // >
    ASSIGNMENT, // =
    NOT,        // !

    NOT_EQUAL,     // !=
    LESS_EQUAL,    // <=
    GREATER_EQUAL, // >=

    // Delimiters
    OPEN_PARENTHESIS,    // (
    OPEN_SQUARE_BRACKET, // [
    OPEN_CURLY_BRACE,    // {

    CLOSE_PARENTHESIS,    // )
    CLOSE_SQUARE_BRACKET, // ]
    CLOSE_CURLY_BRACE,    // }

    COMMA,     // ,
    PERIOD,    // .
    SEMICOLON, // ;
    COLON,     // :

    // Keywords
    BREAK,
    CASE,
    CONST,
    CONTINUE,

    DEFAULT,
    DEFER,
    ELSE,
    FOR,

    FUNCTION,
    GOTO,
    IF,
    IMPORT,

    RETURN,

    SWITCH,
    VARIABLE,

    // Internal
    COUNT
};

#ifdef __cplusplus
}
#endif

#endif // TOKEN_H
