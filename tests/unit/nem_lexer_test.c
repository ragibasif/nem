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

#include "../../src/dbg.h"
#include "../../src/lexer.h"
#include "../../src/token.h"
#include "utils.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

int main( int argc, char **argv ) {
    static char *input_buffer = "+ += // - * / \n % 432 /*~ & | ^ */ < 2.234 > "
                                "= ! ? else () { } [ ] , . ; :";
    static char *input_file   = "main.c";

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
        dbg( token->type );
        dbg( token->lexeme );
        dbg( token->size );
        dbg( token->position );
        dbg( token->line );
        dbg( token->column );
        if ( token->type == NTT_EOF ) {
            dbg( token->type );
            dbg( token->lexeme );
            dbg( token->size );
            dbg( token->position );
            dbg( token->line );
            dbg( token->column );
            nem_token_destroy( &token );
            dbg( token );
            break;
        }
        nem_token_destroy( &token );
        dbg( token );
    }
    nem_lexer_destroy( &lexer );

    TEST_PASSED();
}
