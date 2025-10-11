/*
 * File: token.c
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 */

#include "token.h"

#include <string.h>

NemToken *nem_token_create( const NemTokenType type, const char *lexeme,
                            const size_t size, const size_t position,
                            const unsigned int line,
                            const unsigned int column ) {

    NemToken *token = malloc( sizeof *token );
    if ( token == NULL ) { return NULL; }

    token->type = type;

    token->size   = size;
    token->lexeme = malloc( sizeof *token->lexeme * ( token->size + 1 ) );
    if ( token->lexeme == NULL ) { return NULL; }
    memcpy( token->lexeme, lexeme,
            sizeof *token->lexeme * ( token->size + 1 ) );

    token->position = position;
    token->line     = line;
    token->column   = column;

    return token;
}

void nem_token_destroy( NemToken **token ) {
    if ( token == NULL ) { return; }
    if ( *token == NULL ) { return; }

    free( ( *token )->lexeme );
    ( *token )->lexeme   = NULL;
    ( *token )->type     = 0;
    ( *token )->position = 0;
    ( *token )->size     = 0;
    ( *token )->line     = 0;
    ( *token )->column   = 0;
    free( *token );
    *token = NULL;
}

static const char *nem_token_keywords[] = {
    [NTT_AUTO]     = "auto",
    [NTT_BOOL]     = "bool",
    [NTT_BREAK]    = "break",
    [NTT_CASE]     = "case",
    [NTT_CHAR]     = "char",
    [NTT_CONST]    = "const",
    [NTT_CONTINUE] = "continue",
    [NTT_DEFAULT]  = "default",
    [NTT_DO]       = "do",
    [NTT_ELSE]     = "else",
    [NTT_ENUM]     = "enum",
    [NTT_EXTERN]   = "extern",
    [NTT_FALSE]    = "false",
    [NTT_FLOAT]    = "float",
    [NTT_DOUBLE]   = "double",
    [NTT_FOR]      = "for",
    [NTT_GOTO]     = "goto",
    [NTT_IF]       = "if",
    [NTT_INT]      = "int",
    [NTT_INT8]     = "int8",
    [NTT_INT16]    = "int16",
    [NTT_INT32]    = "int32",
    [NTT_INT64]    = "int64",
    [NTT_LONG]     = "long",
    [NTT_REGISTER] = "register",
    [NTT_RETURN]   = "return",
    [NTT_SHORT]    = "short",
    [NTT_SIGNED]   = "signed",
    [NTT_SIZEOF]   = "sizeof",
    [NTT_STATIC]   = "static",
    [NTT_STRUCT]   = "struct",
    [NTT_SWITCH]   = "switch",
    [NTT_TRUE]     = "true",
    [NTT_TYPEDEF]  = "typedef",
    [NTT_UINT8]    = "uint8",
    [NTT_UINT16]   = "uint16",
    [NTT_UINT32]   = "uint32",
    [NTT_UINT64]   = "uint64",
    [NTT_UNION]    = "union",
    [NTT_UNSIGNED] = "unsigned",
    [NTT_VOID]     = "void",
    [NTT_VOLATILE] = "volatile",
    [NTT_WHILE]    = "while",
};

bool nem_token_check_keyword( const NemTokenType type, const char *buffer ) {
    const char *keyword_literal = nem_token_keywords[type];
    return strcmp( buffer, keyword_literal ) == 0;
}

////////////////////////////////////////////////////////////////////////////////
// Notes
////////////////////////////////////////////////////////////////////////////////

/*
 * tokens are a single lexical unit
 * lexemes are the original string that comprises the token
 * double dereferencing - there is overhead, possibility of two cache misses
 */

////////////////////////////////////////////////////////////////////////////////
