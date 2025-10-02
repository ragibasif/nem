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

#include "bytecode.h"
#include "dbg.h"
#include "lexer.h"
#include "util.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_TEST_FILE "tests/test_01.c"
#define NEM               "nem"

static void nem_run( char *file );

static void nem_run( char *file ) {
    // Important: remember to free this buffer
    char         *buffer  = nem_read_file( file );
    size_t        buf_len = strlen( buffer );
    struct Lexer *lexer   = lexer_create( buffer );
    assert( buf_len == lexer->buffer_size );
    assert( strcmp( buffer, lexer->buffer ) == 0 );

    lexer_tokenize( &lexer );

    lexer_destroy( &lexer );
    free( buffer );
    buffer = NULL;
}

int main( [[maybe_unused]] int argc, [[maybe_unused]] char **argv ) {
    nem_log( __FILE__, __LINE__, __func__, "Starting %s:", NEM );

    dbg( DEFAULT_TEST_FILE );

    struct Chunk chunk;
    chunk_init( &chunk );

    int constant = constant_add( &chunk, 1.2 );
    chunk_push( &chunk, OP_CONSTANT, 123 );
    chunk_push( &chunk, constant, 123 );

    chunk_push( &chunk, OP_RETURN, 123 );
    chunk_disassemble( &chunk, "test" );
    chunk_cleanup( &chunk );

    // nem_run( DEFAULT_TEST_FILE );

    return EXIT_SUCCESS;
}
