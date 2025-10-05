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

struct NemLexer;

extern struct NemLexer *nem_lexer_create( const char *buffer,
                                          const char *file );
extern void             nem_lexer_tokenize( struct NemLexer **lexer );
extern void             nem_lexer_destroy( struct NemLexer **lexer );

#ifdef __cplusplus
}
#endif
#endif // LEXER_H
