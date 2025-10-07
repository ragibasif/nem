/*
 * File: lexer.h
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 */

#ifndef LEXER_H
#define LEXER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "token.h"

typedef struct {
    char        *buffer;   // input buffer
    size_t       size;     // size of the input buffer
    char        *file;     // source file name
    char         ch;       // current character
    size_t       position; // position of the current character
    unsigned int line;     // current line number (starts at 1)
    unsigned int column;   // current column number (starts at 1)
} NemLexer;

extern NemLexer *nem_lexer_create( char *buffer, char *file );
extern void      nem_lexer_destroy( NemLexer **lexer );
NemToken        *nem_lexer_scan( NemLexer **lexer );

#ifdef __cplusplus
}
#endif
#endif // LEXER_H
