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

#include "dbg.h"
#include "nem.h"
#include "util.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define ISSPACE( X ) isspace( (unsigned char)( X ) )
#define ISDIGIT( X ) isdigit( (unsigned char)( X ) )
#define ISALNUM( X ) isalnum( (unsigned char)( X ) )
#define ISALPHA( X ) isalpha( (unsigned char)( X ) )
#define ISUPPER( X ) isupper( (unsigned char)( X ) )
#define ISLOWER( X ) islower( (unsigned char)( X ) )

void nem_lexer_create( struct NemLexer *lexer, const char *buffer ) {
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
}

void nem_lexer_destroy( struct NemLexer *lexer ) {
    assert( lexer != NULL );
    // free and null all memory
    lexer->buffer_size = 0;
    lexer->c           = '\0';
    lexer->position    = 0;
    lexer->line        = 0;
    lexer->column      = 0;
    lexer->offset      = 0;
    free( lexer->buffer );
    lexer->buffer = NULL;
}

void nem_lexer_tokenize( struct NemLexer *lexer ) {
    while ( lexer->position < lexer->buffer_size ) {
        dbg( lexer->buffer[lexer->position++] );
    }
}
