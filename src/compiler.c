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

#include "dbg.h"
#include "lexer.h"
#include "token.h"

void nem_compiler_run( char *buffer, char *file ) {
    NemLexer *lexer = nem_lexer_create( buffer, file );
    while ( 1 ) {
        NemToken *token = nem_lexer_scan( &lexer );
        if ( token->type == NTT_EOF ) { break; }
        printf( "type: %d, lexeme: %s, size: %zu, position: %zu, "
                "line: %d, column: %d\n",
                token->type, token->lexeme, token->size, token->position,
                token->line, token->column );
        for ( size_t i = token->position; i < token->position + token->size;
              i++ ) {
            printf( "buffer[%zu]: %c\n", i, buffer[i] );
        }
        nem_token_destroy( &token );
    }
    nem_lexer_destroy( &lexer );
}
