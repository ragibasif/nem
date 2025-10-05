/*
 * File: lexer.c
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 */

#include "lexer.h"

#include "dbg.h"

struct NemLexer {
    char  *buffer;   // input buffer
    size_t size;     // size of the input buffer
    char  *file;     // source file name
    char   ch;       // current character under examination
    int    position; // position of the current character
    int    line;     // current line number (starts at 1)
    int    column;   // current column number (starts at 1)
    int    offset;   // current offset (starts at 0)
};

struct NemLexer *nem_lexer_create( const char *buffer, const char *file ) {
    if ( buffer == NULL ) { return NULL; }
    if ( file == NULL ) { return NULL; }

    struct NemLexer *nem_lexer = malloc( sizeof *nem_lexer );
    if ( nem_lexer == NULL ) { return NULL; }

    nem_lexer->size = strlen( buffer );

    nem_lexer->buffer =
        malloc( sizeof *nem_lexer->buffer * ( nem_lexer->size + 1 ) );
    if ( nem_lexer->buffer == NULL ) { return NULL; }
    memcpy( nem_lexer->buffer, buffer,
            sizeof *nem_lexer->buffer * ( nem_lexer->size + 1 ) );

    nem_lexer->file =
        malloc( sizeof *nem_lexer->file * ( strlen( file ) + 1 ) );
    if ( nem_lexer->file == NULL ) { return NULL; }
    memcpy( nem_lexer->file, file,
            sizeof *nem_lexer->file * ( strlen( file ) + 1 ) );

    nem_lexer->ch       = '\0';
    nem_lexer->position = 0;
    nem_lexer->line     = 1;
    nem_lexer->column   = 1;
    nem_lexer->offset   = 0;

#ifdef NEM_DEBUG
    fprintf( stderr, "-- Lexer --\n" );
    fprintf( stderr, "[%s:%d (%s)]\n", __FILE__, __LINE__, __func__ );
    fprintf( stderr, "\tbuffer: %s\n", nem_lexer->buffer );
    fprintf( stderr, "\tsize: %zu\n", nem_lexer->size );
    fprintf( stderr, "\tfile: %s\n", nem_lexer->file );
    fprintf( stderr, "\tch: %c\n", nem_lexer->ch );
    fprintf( stderr, "\tposition: %d\n", nem_lexer->position );
    fprintf( stderr, "\tline: %d\n", nem_lexer->line );
    fprintf( stderr, "\tcolumn: %d\n", nem_lexer->column );
    fprintf( stderr, "\toffset: %d\n", nem_lexer->offset );
    fprintf( stderr, "-- ----- --\n" );
#endif // NEM_DEBUG

    return nem_lexer;
}

void nem_lexer_destroy( struct NemLexer **lexer ) {
    if ( lexer == NULL ) { return; }
    if ( *lexer == NULL ) { return; }
    free( ( *lexer )->buffer );
    free( ( *lexer )->file );
    ( *lexer )->buffer   = NULL;
    ( *lexer )->file     = NULL;
    ( *lexer )->size     = 0;
    ( *lexer )->ch       = '\0';
    ( *lexer )->position = -1;
    ( *lexer )->line     = -1;
    ( *lexer )->column   = -1;
    ( *lexer )->offset   = -1;
    free( *lexer );
    *lexer = NULL;
}

static bool         nem_is_space( const char ch );
static bool         nem_is_new_line( const char ch );
static bool         nem_is_digit( const char ch );
static bool         nem_is_decimal( const char ch );
static bool         nem_is_hex( const char ch );
static bool         nem_is_upper( const char ch );
static bool         nem_is_lower( const char ch );
static bool         nem_is_alpha( const char ch );
static bool         nem_is_alnum( const char ch );
static char         nem_lower( const char ch );
static const size_t nem_skip_whitespace( const char  *buffer,
                                         const size_t start );
static const size_t nem_count_new_lines( const char *buffer, const size_t start,
                                         const size_t end );
static const size_t nem_count_spaces( const char *buffer, const size_t start,
                                      const size_t end );

void nem_lexer_tokenize( struct NemLexer **lexer ) {
    // while input isn't empty:
    ( *lexer )->ch = ( *lexer )->buffer[( *lexer )->position];
    dbg( ( *lexer )->buffer );

    while ( ( *lexer )->position < ( *lexer )->size &&
            ( *lexer )->buffer[( *lexer )->position] != '\0' ) {

        // skip white space and count the lines to be added
        const size_t start = ( *lexer )->position;
        const size_t end   = nem_skip_whitespace( ( *lexer )->buffer, start );
        const size_t lines =
            nem_count_new_lines( ( *lexer )->buffer, start, end );
        ( *lexer )->line += lines;
        if ( lines > 0 ) {
            ( *lexer )->column = 1;
        } else {
            ( *lexer )->column += end - start;
        }

        ( *lexer )->position = end;

        // get next char and increment pointer
        ( *lexer )->ch = ( *lexer )->buffer[( *lexer )->position++];

        // find longest match at start of input
        // convert matching substring into a token
        // if no match is found, make error token

        switch ( ( *lexer )->ch ) {}

        ( *lexer )->column++;
    }
}

static const size_t nem_skip_whitespace( const char  *buffer,
                                         const size_t start ) {
    size_t index = start;
    while ( nem_is_space( buffer[index] ) ) { index++; }
    return index;
}

static const size_t nem_count_new_lines( const char *buffer, const size_t start,
                                         const size_t end ) {
    size_t counter = 0;
    for ( size_t i = start; i < end; i++ ) {
        if ( nem_is_new_line( buffer[i] ) ) { counter++; }
    }
    return counter;
}

static bool nem_is_space( const char ch ) {
    return ch == ' ' || ch == '\t' || ch == '\r' || nem_is_new_line( ch );
}

static bool nem_is_new_line( const char ch ) { return ch == '\n'; }

static bool nem_is_digit( const char ch ) { return nem_is_decimal( ch ); }
static bool nem_is_decimal( const char ch ) { return '0' <= ch && ch <= '9'; }

static bool nem_is_hex( const char ch ) {
    return '0' <= ch && ch <= '9' ||
           'a' <= nem_lower( ch ) && nem_lower( ch ) <= 'f';
}

static bool nem_is_upper( const char ch ) { return 'Z' <= ch && ch <= 'Z'; }

static bool nem_is_lower( const char ch ) { return 'a' <= ch && ch <= 'z'; }

static bool nem_is_alpha( const char ch ) {
    return nem_is_lower( ch ) || nem_is_upper( ch );
}

static bool nem_is_alnum( const char ch ) {
    return nem_is_alpha( ch ) || nem_is_digit( ch );
}

// returns lowercase ch iff ch is ASCII letter
static char nem_lower( const char ch ) { return ( 'a' - 'A' ) | ch; }
