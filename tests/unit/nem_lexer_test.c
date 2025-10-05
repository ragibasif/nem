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
#include "utils.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

int main( int argc, char **argv ) {
    struct NemLexer *nem_lexer = NULL;
    assert( nem_lexer == NULL );

    // invalid ,should return NULL
    nem_lexer = nem_lexer_create( NULL, NULL );
    assert( nem_lexer == NULL );
    nem_lexer = nem_lexer_create( "", NULL );
    assert( nem_lexer == NULL );
    nem_lexer = nem_lexer_create( NULL, "" );
    assert( nem_lexer == NULL );

    static char *input_buffer = "int main() { return 0; }";
    static char *input_file   = "main.c";

    nem_lexer = nem_lexer_create( input_buffer, input_file );
    nem_lexer_destroy( &nem_lexer );
    assert( nem_lexer == NULL );

    TEST_PASSED();
}
