/*
 * File: main.c
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 *
 */

#include "dbg.h"
#include "lexer.h"
#include "util.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_TEST_FILE "../tests/test_00.c"
#define NEM               "nem"

static void nem_run( char *file );

static void nem_run( char *file ) {
    // Important: remember to free this buffer
    char            *buffer    = nem_read_file( file );
    size_t           buf_len   = strlen( buffer );
    struct NemLexer *nem_lexer = nem_lexer_create( buffer );
    assert( buf_len == nem_lexer->buffer_size );
    assert( strcmp( buffer, nem_lexer->buffer ) == 0 );

    nem_lexer_tokenize( &nem_lexer );

    nem_lexer_destroy( &nem_lexer );
    free( buffer );
    buffer = NULL;
}

int main( int argc, char **argv ) {
    nem_log( __FILE__, __LINE__, __func__, "Starting %s:", NEM );

    dbg( DEFAULT_TEST_FILE );

    nem_run( DEFAULT_TEST_FILE );

    return EXIT_SUCCESS;
}
