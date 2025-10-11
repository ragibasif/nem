/*
 * File: nem_lexer_test.c
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 *
 */

#include "../../src/lexer.h"
#include "../../src/token.h"
#include "utils.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

void nem_lexer_helper( const char *input_buffer, const char *input_file ) {
    char *buffer = malloc( sizeof *buffer * ( strlen( input_buffer ) + 1 ) );
    assert( buffer != NULL );
    memcpy( buffer, input_buffer,
            sizeof *buffer * ( strlen( input_buffer ) + 1 ) );
    char *file = malloc( sizeof *file * ( strlen( input_file ) + 1 ) );
    assert( file != NULL );
    memcpy( file, input_file, sizeof *file * ( strlen( input_file ) + 1 ) );

    NemLexer *lexer = nem_lexer_create( buffer, file );
    while ( 1 ) {
        NemToken *token = nem_lexer_scan( &lexer );
        if ( token->type == NTT_EOF ) {
            nem_token_destroy( &token );
            break;
        }
        for ( size_t i = token->position; i < token->position + token->size;
              i++ ) {
            assert( buffer[i] == token->lexeme[i - token->position] );
        }
        nem_token_destroy( &token );
    }
    nem_lexer_destroy( &lexer );
}

int main( int argc, char **argv ) {
    nem_lexer_helper( "int main() { return 0; }", "main.c" );
    nem_lexer_helper( "//", "main.c" );
    nem_lexer_helper( "/**/", "main.c" );

    TEST_PASSED();
}
