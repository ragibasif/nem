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
#include "nem.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_TEST_FILE "tests/test_01.c"

static void nem_run( char *file );

static void nem_run( char *file ) {
    // Important: remember to free this buffer
    char           *buffer  = nem_read_file( file );
    size_t          buf_len = strlen( buffer );
    struct NemLexer lexer;
    nem_lexer_create( &lexer, buffer );
    assert( buf_len == lexer.buffer_size );
    assert( strcmp( buffer, lexer.buffer ) == 0 );

    nem_lexer_tokenize( &lexer );

    nem_lexer_destroy( &lexer );
    free( buffer );
    buffer = NULL;
}

int main( int argc, char **argv ) {
    nem_log( __FILE__, __LINE__, __func__, "Starting" );

    dbg( DEFAULT_TEST_FILE );

    nem_run( DEFAULT_TEST_FILE );

    return EXIT_SUCCESS;
}
