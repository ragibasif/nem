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
enum Type {
    // Special tokens
    TYPE_UNKNOWN,
    TEOF,
    TYPE_COMMENT,

    // Literals
    TYPE_IDENTIFIER, // main
    TYPE_NUMBER,     // 12345
    TYPE_DIGIT,      // [0-9]
    TYPE_INTEGER,    // 12345
    TYPE_DOULBE,
    TYPE_FLOAT,     // 123.45
    TYPE_CHARACTER, // 'a'
    TYPE_STRING,    // "abc"

    // Operators
    TYPE_PLUS,   // +
    TYPE_MINUS,  // -
    TYPE_STAR,   // *
    TYPE_SLASH,  // /
    TYPE_MODULO, // %
    TYPE_INVERT, // ~

    TYPE_BITWISE_AND,         // &
    TYPE_BITWISE_OR,          // |
    TYPE_BITWISE_XOR,         // ^
    TYPE_BITWISE_SHIFT_LEFT,  // <<
    TYPE_BITWISE_SHIFT_RIGHT, // >>

    TYPE_PLUS_ASSIGNMENT,   // +=
    TYPE_MINUS_ASSIGNMENT,  // -=
    TYPE_STAR_ASSIGNMENT,   // *=
    TYPE_SLASH_ASSIGNMENT,  // /=
    TYPE_MODULO_ASSIGNMENT, // %=

    TYPE_BITWISE_AND_ASSIGNMENT,         // &=
    TYPE_BITWISE_OR_ASSIGNMENT,          // |=
    TYPE_BITWISE_XOR_ASSIGNMENT,         // ^=
    TYPE_BITWISE_SHIFT_LEFT_ASSIGNMENT,  // <<=
    TYPE_BITWISE_SHIFT_RIGHT_ASSIGNMENT, // >>=

    TYPE_LOGICAL_AND, // &&
    TYPE_LOGICAL_OR,  // ||
    TYPE_ARROW,       // ->
    TYPE_INCREMENT,   // ++
    TYPE_DECREMENT,   // --

    TYPE_EQUAL,      // ==
    TYPE_LESS,       // <
    TYPE_GREATER,    // >
    TYPE_ASSIGNMENT, // =
    TYPE_NOT,        // !
    TYPE_QUESTION,   // ?

    TYPE_NOT_EQUAL,     // !=
    TYPE_LESS_EQUAL,    // <=
    TYPE_GREATER_EQUAL, // >=
    TYPE_DEFINE,        // :=
    TYPE_ELLIPSIS,      // ...

    // Delimiters
    TYPE_OPEN_PARENTHESIS,     // (
    TYPE_OPEN_SQUARE_BRACKET,  // [
    TYPE_OPEN_CURLY_BRACE,     // {
    TYPE_CLOSE_PARENTHESIS,    // )
    TYPE_CLOSE_SQUARE_BRACKET, // ]
    TYPE_CLOSE_CURLY_BRACE,    // }

    TYPE_COMMA,     // ,
    TYPE_PERIOD,    // .
    TYPE_SEMICOLON, // ;
    TYPE_COLON,     // :

    // Keywords
    TYPE_AUTO,
    TYPE_BREAK,
    TYPE_CASE,
    TYPE_CONST,
    TYPE_CONTINUE,
    TYPE_PRINT,
    TYPE_TRUE,
    TYPE_FALSE,

    TYPE_DEFAULT,
    TYPE_DO,
    // TYPE_DEFER,
    TYPE_ELSE,
    TYPE_FOR,
    TYPE_ENUM,
    TYPE_EXTERN,
    TYPE_INT,
    TYPE_CHAR,
    TYPE_LONG,
    TYPE_REGISTER,
    TYPE_SHORT,
    TYPE_SIGNED,
    TYPE_SIZEOF,
    TYPE_STATIC,
    TYPE_STRUCT,
    TYPE_TYPEDEF,
    TYPE_UNION,
    TYPE_UNSIGNED,
    TYPE_VOLATILE,
    TYPE_WHILE,

    TYPE_FUNCTION,
    TYPE_GOTO,
    TYPE_IF,
    TYPE_IMPORT,

    TYPE_RETURN,

    TYPE_SWITCH,
    TYPE_VARIABLE, // [A-Za-z_]+ [A-Za-z0-9_]*
    TYPE_TYPE,

    // built-in data types
    TYPE_VOID,
    TYPE_BOOL,
    TYPE_INT8,   // char
    TYPE_UINT8,  // unsigned char
    TYPE_INT16,  // short
    TYPE_UINT16, // unsigned short
    TYPE_INT32,  // int
    TYPE_UINT32, // unsigned int
    TYPE_INT64,  // long long
    TYPE_UINT64, // unsigned long long
    TYPE_FLT32,  // float
    TYPE_FLT64,  // double

    // Internal
    TYPE_COUNT
};

struct Token {
    enum Type type;
    char     *name;
    char     *literal;
};

extern void token_create( struct Token *token, char *literal );
extern void token_print( struct Token *token );
extern void token_destroy( struct Token *token );

#ifdef __cplusplus
}
#endif

#endif // TOKEN_H
