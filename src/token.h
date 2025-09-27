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
enum NemTokenType {
    // Special tokens
    NTT_UNKNOWN,
    NTT_EOF,
    NTT_COMMENT,

    // Literals
    NTT_IDENTIFIER, // main
    NTT_NUMBER,     // 12345
    NTT_DIGIT,      // [0-9]
    NTT_INTEGER,    // 12345
    NTT_DOULBE,
    NTT_FLOAT,     // 123.45
    NTT_CHARACTER, // 'a'
    NTT_STRING,    // "abc"

    // Operators
    NTT_PLUS,   // +
    NTT_MINUS,  // -
    NTT_STAR,   // *
    NTT_SLASH,  // /
    NTT_MODULO, // %
    NTT_INVERT, // ~

    NTT_BITWISE_AND,         // &
    NTT_BITWISE_OR,          // |
    NTT_BITWISE_XOR,         // ^
    NTT_BITWISE_SHIFT_LEFT,  // <<
    NTT_BITWISE_SHIFT_RIGHT, // >>

    NTT_PLUS_ASSIGNMENT,   // +=
    NTT_MINUS_ASSIGNMENT,  // -=
    NTT_STAR_ASSIGNMENT,   // *=
    NTT_SLASH_ASSIGNMENT,  // /=
    NTT_MODULO_ASSIGNMENT, // %=

    NTT_BITWISE_AND_ASSIGNMENT,         // &=
    NTT_BITWISE_OR_ASSIGNMENT,          // |=
    NTT_BITWISE_XOR_ASSIGNMENT,         // ^=
    NTT_BITWISE_SHIFT_LEFT_ASSIGNMENT,  // <<=
    NTT_BITWISE_SHIFT_RIGHT_ASSIGNMENT, // >>=

    NTT_LOGICAL_AND, // &&
    NTT_LOGICAL_OR,  // ||
    NTT_ARROW,       // ->
    NTT_INCREMENT,   // ++
    NTT_DECREMENT,   // --

    NTT_EQUAL,      // ==
    NTT_LESS,       // <
    NTT_GREATER,    // >
    NTT_ASSIGNMENT, // =
    NTT_NOT,        // !
    NTT_QUESTION,   // ?

    NTT_NOT_EQUAL,     // !=
    NTT_LESS_EQUAL,    // <=
    NTT_GREATER_EQUAL, // >=
    NTT_DEFINE,        // :=
    NTT_ELLIPSIS,      // ...

    // Delimiters
    NTT_OPEN_PARENTHESIS,     // (
    NTT_OPEN_SQUARE_BRACKET,  // [
    NTT_OPEN_CURLY_BRACE,     // {
    NTT_CLOSE_PARENTHESIS,    // )
    NTT_CLOSE_SQUARE_BRACKET, // ]
    NTT_CLOSE_CURLY_BRACE,    // }

    NTT_COMMA,     // ,
    NTT_PERIOD,    // .
    NTT_SEMICOLON, // ;
    NTT_COLON,     // :

    // Keywords
    NTT_AUTO,
    NTT_BREAK,
    NTT_CASE,
    NTT_CONST,
    NTT_CONTINUE,
    NTT_PRINT,
    NTT_TRUE,
    NTT_FALSE,

    NTT_DEFAULT,
    NTT_DO,
    // NTT_DEFER,
    NTT_ELSE,
    NTT_FOR,
    NTT_ENUM,
    NTT_EXTERN,
    NTT_INT,
    NTT_CHAR,
    NTT_LONG,
    NTT_REGISTER,
    NTT_SHORT,
    NTT_SIGNED,
    NTT_SIZEOF,
    NTT_STATIC,
    NTT_STRUCT,
    NTT_TYPEDEF,
    NTT_UNION,
    NTT_UNSIGNED,
    NTT_VOLATILE,
    NTT_WHILE,

    NTT_FUNCTION,
    NTT_GOTO,
    NTT_IF,
    NTT_IMPORT,

    NTT_RETURN,

    NTT_SWITCH,
    NTT_VARIABLE, // [A-Za-z_]+ [A-Za-z0-9_]*
    NTT_TYPE,

    // built-in data types
    NTT_VOID,
    NTT_BOOL,
    NTT_INT8,   // char
    NTT_UINT8,  // unsigned char
    NTT_INT16,  // short
    NTT_UINT16, // unsigned short
    NTT_INT32,  // int
    NTT_UINT32, // unsigned int
    NTT_INT64,  // long long
    NTT_UINT64, // unsigned long long
    NTT_FLT32,  // float
    NTT_FLT64,  // double

    // Internal
    NTT_COUNT
};

struct NemToken {
    enum NemTokenType type;
    char             *name;
    char             *literal;
};

extern void nem_token_create( struct NemToken *nem_token, char *literal );
extern void nem_token_print( struct NemToken *nem_token );
extern void nem_token_destroy( struct NemToken *nem_token );

#ifdef __cplusplus
}
#endif

#endif // TOKEN_H
