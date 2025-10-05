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
    struct NemToken nem_token;

    nem_token = nem_token_init( NTT_ERROR, 100, strlen( "illegal" ), 23 );
    assert( nem_token_type( &nem_token ) == NTT_ERROR );
    assert( nem_token_index( &nem_token ) == 100 );
    assert( nem_token_size( &nem_token ) == strlen( "illegal" ) );
    assert( nem_token_line( &nem_token ) == 23 );

    nem_token = nem_token_init( NTT_EOF, 200, strlen( "EOF" ), 32 );
    assert( nem_token_type( &nem_token ) == NTT_EOF );
    assert( nem_token_index( &nem_token ) == 200 );
    assert( nem_token_size( &nem_token ) == strlen( "EOF" ) );
    assert( nem_token_line( &nem_token ) == 32 );

    TEST_PASSED();
}
