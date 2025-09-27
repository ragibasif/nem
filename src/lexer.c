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

struct NemLexer *nem_lexer_create( const char *buffer ) {
    struct NemLexer *nem_lexer = malloc( sizeof *nem_lexer );
    nem_alloc_check( nem_lexer, sizeof *nem_lexer, __FILE__, __LINE__,
                     __func__ );
    nem_lexer->buffer_size = strlen( buffer );
    nem_lexer->buffer =
        malloc( sizeof *nem_lexer->buffer * nem_lexer->buffer_size + 1 );
    nem_alloc_check( nem_lexer->buffer,
                     sizeof *nem_lexer->buffer * nem_lexer->buffer_size + 1,
                     __FILE__, __LINE__, __func__ );
    strcpy( nem_lexer->buffer, buffer );
    nem_lexer->buffer[nem_lexer->buffer_size] = '\0';
    nem_lexer->position                       = 0;
    nem_lexer->line                           = 1;
    nem_lexer->column                         = 1;
    nem_lexer->offset                         = 0;
    nem_lexer->c                              = '\0';
    return nem_lexer;
}

void nem_lexer_destroy( struct NemLexer **nem_lexer ) {
    assert( nem_lexer != NULL && *nem_lexer != NULL );
    // free and null all memory
    ( *nem_lexer )->buffer_size = 0;
    ( *nem_lexer )->c           = 0;
    ( *nem_lexer )->position    = 0;
    ( *nem_lexer )->line        = 0;
    ( *nem_lexer )->column      = 0;
    ( *nem_lexer )->offset      = 0;
    free( ( *nem_lexer )->buffer );
    ( *nem_lexer )->buffer = NULL;
    free( *nem_lexer );
    *nem_lexer = NULL;
}

void nem_lexer_tokenize( struct NemLexer **nem_lexer ) {
    dbg( nem_lexer );
    dbg( &nem_lexer );
    dbg( ( *nem_lexer ) );
    dbg( ( *nem_lexer )->buffer );
    dbg( ( *nem_lexer )->buffer_size );
    while ( ( *nem_lexer )->position < ( *nem_lexer )->buffer_size ) {
        dbg( ( *nem_lexer )->buffer[( *nem_lexer )->position++] );
    }
}
