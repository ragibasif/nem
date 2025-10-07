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
    NemToken *token;

    token = nem_token_create( NTT_ERROR, "illegal", strlen( "illegal" ), 100,
                              23, 29 );
    assert( token->type == NTT_ERROR );
    assert( token->position == 100 );
    assert( token->size == strlen( "illegal" ) );
    assert( token->line == 23 );
    assert( token->column == 29 );
    nem_token_destroy( &token );
    assert( token == NULL );

    token = nem_token_create( NTT_EOF, "\0", strlen( "\0" ), 200, 2432, 9 );
    assert( token->type == NTT_EOF );
    assert( token->position == 200 );
    assert( token->size == strlen( "\0" ) );
    assert( token->line == 2432 );
    assert( token->column == 9 );
    nem_token_destroy( &token );
    assert( token == NULL );

    TEST_PASSED();
}
