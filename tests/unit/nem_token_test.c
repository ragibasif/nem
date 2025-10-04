/*
 * File: nem_token_test.c
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 *
 */

#include "../../src/token.h"
#include "utils.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

int main( int argc, char **argv ) {
    struct NemToken *nem_token = NULL;
    assert( nem_token == NULL );

    // invalid token, should return NULL
    nem_token = nem_token_create( NTT_UNKNOWN - 1, "illegal", 100,
                                  strlen( "illegal" ), "main.c", 23 );
    assert( nem_token == NULL );

    nem_token = nem_token_create( NTT_UNKNOWN, "error", 0, strlen( "error" ),
                                  "main.c", 32 );
    assert( nem_token_type( nem_token ) == NTT_UNKNOWN );
    assert( strcmp( nem_token_lexeme( nem_token ), "error" ) == 0 ); // equal
    assert( nem_token_position( nem_token ) == 0 );
    assert( nem_token_length( nem_token ) == strlen( "error" ) );
    assert( strcmp( nem_token_file( nem_token ), "main.c" ) == 0 ); // equal
    assert( nem_token_line( nem_token ) == 32 );
    nem_token_destroy( &nem_token );
    assert( nem_token == NULL );

    nem_token =
        nem_token_create( NTT_EOF, "EOF", 1, strlen( "EOF" ), "main.c", 56 );
    assert( nem_token_type( nem_token ) == NTT_EOF );
    assert( strcmp( nem_token_lexeme( nem_token ), "EOF" ) == 0 ); // equal
    assert( nem_token_position( nem_token ) == 1 );
    assert( nem_token_length( nem_token ) == strlen( "EOF" ) );
    assert( strcmp( nem_token_file( nem_token ), "main.c" ) == 0 ); // equal
    assert( nem_token_line( nem_token ) == 56 );
    nem_token_destroy( &nem_token );
    assert( nem_token == NULL );

    TEST_PASSED();
}
