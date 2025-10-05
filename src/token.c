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

struct NemToken {
    enum NemTokenType type;
    char             *lexeme;   // original literal value
    int               position; // starting index in the source buffer
    size_t            length;   // size (length) of the token
    char             *file;     // source file
    int               line;     // line number
};

struct NemToken *nem_token_create( const enum NemTokenType type,
                                   const char *lexeme, const int position,
                                   const size_t length, const char *file,
                                   const int line ) {

    if ( type < NTT_UNKNOWN || type >= NTT_COUNT || lexeme == NULL ) {
        return NULL;
    }

    struct NemToken *nem_token = malloc( sizeof *nem_token );

    if ( nem_token == NULL ) { return NULL; }

    nem_token->type     = type;
    nem_token->position = position;
    nem_token->length   = strlen( lexeme );
    nem_token->line     = line;

    nem_token->lexeme =
        malloc( sizeof *nem_token->lexeme * ( nem_token->length + 1 ) );

    if ( nem_token->lexeme == NULL ) { return NULL; }

    memcpy( nem_token->lexeme, lexeme,
            sizeof *nem_token->lexeme * ( nem_token->length + 1 ) );

    nem_token->file =
        malloc( sizeof *nem_token->file * ( strlen( file ) + 1 ) );

    if ( nem_token->file == NULL ) { return NULL; }

    memcpy( nem_token->file, file,
            sizeof *nem_token->file * ( strlen( file ) + 1 ) );

#ifdef NEM_DEBUG
    fprintf( stderr, "[%s:%d (%s)] ", __FILE__, __LINE__, __func__ );
    fprintf( stderr, "type: %d -- lexeme: %s\n", nem_token->type,
             nem_token->lexeme );
#endif // NEM_DEBUG

    return nem_token;
}

void nem_token_destroy( struct NemToken **token ) {
    if ( token == NULL ) { return; }
    if ( *token == NULL ) { return; }

    free( ( *token )->lexeme );
    ( *token )->lexeme = NULL;

    free( ( *token )->file );
    ( *token )->file = NULL;

    ( *token )->type     = -1;
    ( *token )->position = -1;
    ( *token )->length   = 0;
    ( *token )->line     = -1;

    free( *token );
    *token = NULL;
}

const enum NemTokenType nem_token_type( struct NemToken *token ) {
    if ( token == NULL ) { return -1; }
    return token->type;
}

const char *const nem_token_lexeme( struct NemToken *token ) {
    if ( token == NULL ) { return NULL; }
    if ( token->lexeme == NULL ) { return NULL; }
    return token->lexeme;
}

const int nem_token_position( struct NemToken *token ) {
    if ( token == NULL ) { return -1; }
    return token->position;
}

const size_t nem_token_length( struct NemToken *token ) {
    if ( token == NULL ) { return 0; }
    return token->length;
}

const char *const nem_token_file( struct NemToken *token ) {
    if ( token == NULL ) { return NULL; }
    if ( token->file == NULL ) { return NULL; }
    return token->file;
}

const int nem_token_line( struct NemToken *token ) {
    if ( token == NULL ) { return -1; }
    return token->line;
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
