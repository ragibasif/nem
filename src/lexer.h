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

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

struct NemLexer {
    char  *buffer;      // input buffer
    size_t buffer_size; // size of the input
    char   c;           // current character under examination
    size_t position;    // position of the current character
    size_t line;        // current line number (starts at 1)
    size_t column;      // current column number (starts at 1)
    size_t offset;      // current offset (starts at 0)
};

extern struct NemLexer *nem_lexer_create( const char *buffer );
extern void             nem_lexer_destroy( struct NemLexer **nem_lexer );
extern void             nem_lexer_tokenize( struct NemLexer **nem_lexer );

#ifdef __cplusplus
}
#endif

#endif // LEXER_H
