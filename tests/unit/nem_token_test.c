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
#include <string.h>

void nem_token_test_helper( NemTokenType type, const char *lexeme, size_t size,
                            size_t position, const unsigned int line,
                            const unsigned int column ) {
    NemToken *token;
    token = nem_token_create( type, lexeme, size, position, line, column );
    assert( token->type == type );
    assert( strcmp( lexeme, token->lexeme ) == 0 );
    assert( token->position == position );
    assert( token->size == size );
    assert( token->line == line );
    assert( token->column == column );
    nem_token_destroy( &token );
    assert( token == NULL );
}

int main( int argc, char **argv ) {
    nem_token_test_helper( NTT_ERROR, "illegal", strlen( "illegal" ), 100, 23,
                           29 );
    nem_token_test_helper( NTT_EOF, "EOF", strlen( "EOF" ), 200, 2432, 9 );
    nem_token_test_helper( NTT_INT, "int", strlen( "int" ), 9274382, 2,
                           734289 );

    TEST_PASSED();
}
