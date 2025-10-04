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
    struct NemToken *nem_token = nem_token_create( 0, NULL );
    assert( nem_token == NULL );
    nem_token_destroy( &nem_token );
    assert( nem_token == NULL );

    nem_token = nem_token_create( 1, "EOF" );
    assert( nem_token_type( nem_token ) == 1 );
    assert( strcmp( nem_token_lexeme( nem_token ), "EOF" ) == 0 );
    nem_token_destroy( &nem_token );
    assert( nem_token == NULL );

    TEST_PASSED();
}
