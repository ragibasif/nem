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

// TODO: add source file name
// TODO: add line number
struct NemToken {
    enum NemTokenType type;
    char             *lexeme;
};

struct NemToken *nem_token_create( enum NemTokenType type,
                                   const char       *lexeme ) {

    if ( type <= NTT_UNKNOWN || type >= NTT_COUNT || lexeme == NULL ) {
        errno = EINVAL;
        return NULL;
    }

    struct NemToken *nem_token = malloc( sizeof *nem_token );

    if ( nem_token == NULL ) {
        errno = ENOMEM;
        return NULL;
    }

    nem_token->type = type;

    const size_t lexeme_len =
        sizeof *nem_token->lexeme * ( strlen( lexeme ) + 1 );
    nem_token->lexeme = malloc( lexeme_len );

    if ( nem_token->lexeme == NULL ) {
        errno = ENOMEM;
        return NULL;
    }
    memcpy( nem_token->lexeme, lexeme, lexeme_len );

#ifdef NEM_DEBUG
    fprintf( stderr, "[%s:%d (%s)] type: %d -- lexeme: %s\n", __FILE__,
             __LINE__, __func__, nem_token->type, nem_token->lexeme );
#endif // NEM_DEBUG

    return nem_token;
}

void nem_token_destroy( struct NemToken **token ) {
    if ( token == NULL ) { return; }
    if ( *token == NULL ) { return; }

    free( ( *token )->lexeme );
    ( *token )->lexeme = NULL;

    ( *token )->type = 0;

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
