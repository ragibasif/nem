/*
 * File: lexer.c
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 */

#include "lexer.h"

#include "dbg.h"
#include "util.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Lexer *lexer_create( const char *buffer ) {
    struct Lexer *lexer = malloc( sizeof *lexer );
    nem_alloc_check( lexer, sizeof *lexer, __FILE__, __LINE__, __func__ );
    lexer->buffer_size = strlen( buffer );
    lexer->buffer = malloc( sizeof *lexer->buffer * lexer->buffer_size + 1 );
    nem_alloc_check( lexer->buffer,
                     sizeof *lexer->buffer * lexer->buffer_size + 1, __FILE__,
                     __LINE__, __func__ );
    strcpy( lexer->buffer, buffer );
    lexer->buffer[lexer->buffer_size] = '\0';
    lexer->position                   = 0;
    lexer->line                       = 1;
    lexer->column                     = 1;
    lexer->offset                     = 0;
    lexer->c                          = '\0';
    return lexer;
}

void lexer_destroy( struct Lexer **lexer ) {
    assert( lexer != NULL && *lexer != NULL );
    // free and null all memory
    ( *lexer )->buffer_size = 0;
    ( *lexer )->c           = '\0';
    ( *lexer )->position    = 0;
    ( *lexer )->line        = 0;
    ( *lexer )->column      = 0;
    ( *lexer )->offset      = 0;
    free( ( *lexer )->buffer );
    ( *lexer )->buffer = NULL;
    free( *lexer );
    *lexer = NULL;
}

void lexer_tokenize( struct Lexer **lexer ) {
    while ( ( *lexer )->position < ( *lexer )->buffer_size ) {
        dbg( ( *lexer )->buffer[( *lexer )->position++] );
    }
}
