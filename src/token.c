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

struct NemToken nem_token_init( const enum NemTokenType type, const int index,
                                const size_t size, const int line ) {

    struct NemToken nem_token;
    nem_token.type  = type;
    nem_token.index = index;
    nem_token.size  = size;
    nem_token.line  = line;

#ifdef NEM_DEBUG
    fprintf( stderr, "[%s:%d (%s)] ", __FILE__, __LINE__, __func__ );
    fprintf( stderr, "{type: %d, index: %d, size: %zu, line: %d}\n",
             nem_token.type, nem_token.index, nem_token.size, nem_token.line );
#endif // NEM_DEBUG

    return nem_token;
}

const enum NemTokenType nem_token_type( struct NemToken *token ) {
    if ( token == NULL ) { return -1; }
    return token->type;
}

const int nem_token_index( struct NemToken *token ) {
    if ( token == NULL ) { return -1; }
    return token->index;
}

const size_t nem_token_size( struct NemToken *token ) {
    if ( token == NULL ) { return 0; }
    return token->size;
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
