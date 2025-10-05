/*
 * File: compiler.c
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 */

#include "compiler.h"

#include "lexer.h"

void nem_compiler_run( const char *buffer, const char *file ) {
    struct NemLexer *nem_lexer = nem_lexer_create( buffer, file );
    nem_lexer_tokenize( &nem_lexer );
    nem_lexer_destroy( &nem_lexer );
}
