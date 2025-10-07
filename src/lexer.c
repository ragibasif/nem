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

NemLexer *nem_lexer_create( char *buffer, char *file ) {
    NemLexer *lexer = malloc( sizeof *lexer );
    if ( lexer == NULL ) { return NULL; }

    lexer->buffer   = buffer;
    lexer->size     = strlen( buffer );
    lexer->file     = file;
    lexer->ch       = ' ';
    lexer->position = 0;
    lexer->line     = 0;
    lexer->column   = 0;

    return lexer;
}

void nem_lexer_destroy( NemLexer **lexer ) {
    if ( lexer == NULL ) { return; }
    if ( *lexer == NULL ) { return; }

    free( ( *lexer )->buffer );
    free( ( *lexer )->file );
    ( *lexer )->buffer   = NULL;
    ( *lexer )->file     = NULL;
    ( *lexer )->position = 0;
    ( *lexer )->size     = 0;
    ( *lexer )->line     = 1;
    ( *lexer )->column   = 1;
    ( *lexer )->ch       = '\0';
    free( *lexer );
    *lexer = NULL;
}

static char nem_lexer_next( NemLexer **lexer ) {
    if ( lexer == NULL ) { return '\0'; }
    if ( *lexer == NULL ) { return '\0'; }

    ( *lexer )->ch = ( *lexer )->buffer[( *lexer )->position];
    ( *lexer )->position++;
    ( *lexer )->column++;
    return ( *lexer )->ch;
}

static char nem_lexer_peek( NemLexer **lexer ) {
    if ( lexer == NULL ) { return '\0'; }
    if ( *lexer == NULL ) { return '\0'; }

    if ( ( *lexer )->position < ( *lexer )->size ) {
        return ( *lexer )->buffer[( *lexer )->position];
    }
    return '\0';
}

static char nem_lexer_double_peek( NemLexer **lexer ) {
    if ( lexer == NULL ) { return '\0'; }
    if ( *lexer == NULL ) { return '\0'; }

    if ( ( *lexer )->position + 1 < ( *lexer )->size ) {
        return ( *lexer )->buffer[( *lexer )->position + 1];
    }
    return '\0';
}

static void nem_lexer_skip_white_space( NemLexer **lexer ) {
    if ( lexer == NULL ) { return; }
    if ( *lexer == NULL ) { return; }

    while ( 1 ) {
        char ch = nem_lexer_peek( lexer );
        switch ( ch ) {
            case ' ':
            case '\t':
            case '\f':
            case '\r': nem_lexer_next( lexer ); break;
            case '\n':
                ( *lexer )->line++;
                nem_lexer_next( lexer );
                break;
            case '/': // C++ and C style comments get skipped
                if ( nem_lexer_double_peek( lexer ) == '/' ) {
                    while ( nem_lexer_peek( lexer ) != '\n' &&
                            ( ( *lexer )->position < ( *lexer )->size ) ) {
                        nem_lexer_next( lexer );
                    }
                    // TODO: test
                } else if ( nem_lexer_double_peek( lexer ) == '*' ) {
                    while ( ( *lexer )->position < ( *lexer )->size &&
                            ( nem_lexer_peek( lexer ) != '*' ||
                              nem_lexer_double_peek( lexer ) != '/' ) ) {
                        nem_lexer_next( lexer );
                    }
                    nem_lexer_next( lexer );
                    nem_lexer_next( lexer );
                } else {
                    return;
                }
            default: return;
        }
    }
}

static bool nem_lexer_match( NemLexer **lexer, const char ch ) {
    if ( lexer == NULL ) { return false; }
    if ( *lexer == NULL ) { return false; }
    if ( !( ( *lexer )->position < ( *lexer )->size ) ) { return false; }
    if ( nem_lexer_peek( lexer ) != ch ) { return false; }
    nem_lexer_next( lexer );
    return true;
}

NemToken *nem_lexer_scan( NemLexer **lexer ) {

    nem_lexer_skip_white_space( lexer );
    NemToken *token;

    // find longest match at start of input
    // convert matching substring into a token
    char ch = nem_lexer_next( lexer );
    switch ( ch ) {

        case '+': {
            if ( nem_lexer_match( lexer, '=' ) ) {
                token =
                    nem_token_create( NTT_PLUS_ASSIGNMENT, "+=", strlen( "+=" ),
                                      ( *lexer )->position - 1,
                                      ( *lexer )->line, ( *lexer )->column );
            } else {
                token = nem_token_create(
                    NTT_PLUS, "+", strlen( "+" ), ( *lexer )->position - 1,
                    ( *lexer )->line, ( *lexer )->column );
            }
            return token;
        }

        case '-': {
            if ( nem_lexer_match( lexer, '=' ) ) {
                token = nem_token_create(
                    NTT_MINUS_ASSIGNMENT, "-=", strlen( "-=" ),
                    ( *lexer )->position - 1, ( *lexer )->line,
                    ( *lexer )->column );
            } else {
                token = nem_token_create(
                    NTT_MINUS, "-", strlen( "-" ), ( *lexer )->position,
                    ( *lexer )->line, ( *lexer )->column );
            }
            return token;
        }

        case '*': {
            if ( nem_lexer_match( lexer, '=' ) ) {
                token = nem_token_create(
                    NTT_MULTIPLY_ASSIGNMENT, "*=", strlen( "*=" ),
                    ( *lexer )->position - 1, ( *lexer )->line,
                    ( *lexer )->column );
            } else {
                token = nem_token_create(
                    NTT_MULTIPLY, "*", strlen( "*" ), ( *lexer )->position,
                    ( *lexer )->line, ( *lexer )->column );
            }
            return token;
        }

        case '/': {
            if ( nem_lexer_match( lexer, '=' ) ) {
                token = nem_token_create(
                    NTT_DIVIDE_ASSIGNMENT, "/=", strlen( "/=" ),
                    ( *lexer )->position - 1, ( *lexer )->line,
                    ( *lexer )->column );
            } else {
                token = nem_token_create(
                    NTT_DIVIDE, "/", strlen( "/" ), ( *lexer )->position,
                    ( *lexer )->line, ( *lexer )->column );
            }
            return token;
        }

        case '%': {
            if ( nem_lexer_match( lexer, '=' ) ) {
                token = nem_token_create(
                    NTT_MODULO_ASSIGNMENT, "%=", strlen( "%=" ),
                    ( *lexer )->position - 1, ( *lexer )->line,
                    ( *lexer )->column );
            } else {
                token = nem_token_create(
                    NTT_MODULO, "%", strlen( "%" ), ( *lexer )->position,
                    ( *lexer )->line, ( *lexer )->column );
            }
            return token;
        }

        case '~': {
            if ( nem_lexer_match( lexer, '=' ) ) {
                token = nem_token_create(
                    NTT_INVERT_ASSIGNMENT, "~=", strlen( "~=" ),
                    ( *lexer )->position - 1, ( *lexer )->line,
                    ( *lexer )->column );
            } else {
                token = nem_token_create(
                    NTT_INVERT, "~", strlen( "~" ), ( *lexer )->position,
                    ( *lexer )->line, ( *lexer )->column );
            }
            return token;
        }

        case '&': {
            if ( nem_lexer_match( lexer, '=' ) ) {
                token = nem_token_create(
                    NTT_BITWISE_AND_ASSIGNMENT, "&=", strlen( "&=" ),
                    ( *lexer )->position - 1, ( *lexer )->line,
                    ( *lexer )->column );
            } else {
                token = nem_token_create(
                    NTT_BITWISE_AND, "&", strlen( "&" ), ( *lexer )->position,
                    ( *lexer )->line, ( *lexer )->column );
            }
            return token;
        }

        case '|': {
            if ( nem_lexer_match( lexer, '=' ) ) {
                token = nem_token_create(
                    NTT_BITWISE_OR_ASSIGNMENT, "|=", strlen( "|=" ),
                    ( *lexer )->position - 1, ( *lexer )->line,
                    ( *lexer )->column );
            } else {
                token = nem_token_create(
                    NTT_BITWISE_OR, "|", strlen( "|" ), ( *lexer )->position,
                    ( *lexer )->line, ( *lexer )->column );
            }
            return token;
        }

        case '^': {
            if ( nem_lexer_match( lexer, '=' ) ) {
                token = nem_token_create(
                    NTT_BITWISE_XOR_ASSIGNMENT, "^=", strlen( "^=" ),
                    ( *lexer )->position - 1, ( *lexer )->line,
                    ( *lexer )->column );
            } else {
                token = nem_token_create(
                    NTT_BITWISE_XOR, "^", strlen( "^" ), ( *lexer )->position,
                    ( *lexer )->line, ( *lexer )->column );
            }
            return token;
        }

        case '<': {
            if ( nem_lexer_match( lexer, '=' ) ) {
                token =
                    nem_token_create( NTT_LESS_EQUAL, "<=", strlen( "<=" ),
                                      ( *lexer )->position - 1,
                                      ( *lexer )->line, ( *lexer )->column );
            } else {
                token = nem_token_create(
                    NTT_LESS, "<", strlen( "<" ), ( *lexer )->position,
                    ( *lexer )->line, ( *lexer )->column );
            }
            return token;
        }

        case '>': {
            if ( nem_lexer_match( lexer, '=' ) ) {
                token =
                    nem_token_create( NTT_GREATER_EQUAL, ">=", strlen( ">=" ),
                                      ( *lexer )->position - 1,
                                      ( *lexer )->line, ( *lexer )->column );
            } else {
                token = nem_token_create(
                    NTT_GREATER, ">", strlen( ">" ), ( *lexer )->position,
                    ( *lexer )->line, ( *lexer )->column );
            }
            return token;
        }

        case '=': {
            if ( nem_lexer_match( lexer, '=' ) ) {
                token = nem_token_create(
                    NTT_EQUAL, "==", strlen( "==" ), ( *lexer )->position - 1,
                    ( *lexer )->line, ( *lexer )->column );
            } else {
                token = nem_token_create(
                    NTT_ASSIGNMENT, "=", strlen( "=" ), ( *lexer )->position,
                    ( *lexer )->line, ( *lexer )->column );
            }
            return token;
        }

        case '!': {
            if ( nem_lexer_match( lexer, '=' ) ) {
                token =
                    nem_token_create( NTT_NOT_EQUAL, "!=", strlen( "!=" ),
                                      ( *lexer )->position - 1,
                                      ( *lexer )->line, ( *lexer )->column );
            } else {
                token = nem_token_create(
                    NTT_NOT, "!", strlen( "!" ), ( *lexer )->position,
                    ( *lexer )->line, ( *lexer )->column );
            }
            return token;
        }

        case '?': {
            token = nem_token_create( NTT_QUESTION, "?", strlen( "?" ),
                                      ( *lexer )->position, ( *lexer )->line,
                                      ( *lexer )->column );
            return token;
        }

        case '(': {
            token = nem_token_create( NTT_OPEN_PARENTHESIS, "(", strlen( "(" ),
                                      ( *lexer )->position, ( *lexer )->line,
                                      ( *lexer )->column );
            return token;
        }

        case ')': {
            token = nem_token_create( NTT_CLOSE_PARENTHESIS, ")", strlen( ")" ),
                                      ( *lexer )->position, ( *lexer )->line,
                                      ( *lexer )->column );
            return token;
        }

        case '{': {
            token = nem_token_create( NTT_OPEN_CURLY_BRACE, "{", strlen( "{" ),
                                      ( *lexer )->position, ( *lexer )->line,
                                      ( *lexer )->column );
            return token;
        }

        case '}': {
            token = nem_token_create( NTT_CLOSE_CURLY_BRACE, "}", strlen( "}" ),
                                      ( *lexer )->position, ( *lexer )->line,
                                      ( *lexer )->column );
            return token;
        }

        case '[': {
            token = nem_token_create( NTT_OPEN_SQUARE_BRACKET, "[",
                                      strlen( "[" ), ( *lexer )->position,
                                      ( *lexer )->line, ( *lexer )->column );
            return token;
        }

        case ']': {
            token = nem_token_create( NTT_CLOSE_SQUARE_BRACKET, "]",
                                      strlen( "]" ), ( *lexer )->position,
                                      ( *lexer )->line, ( *lexer )->column );
            return token;
        }

        case ',': {
            token = nem_token_create( NTT_COMMA, ",", strlen( "," ),
                                      ( *lexer )->position, ( *lexer )->line,
                                      ( *lexer )->column );
            return token;
        }

        case '.': {
            token = nem_token_create( NTT_PERIOD, ".", strlen( "." ),
                                      ( *lexer )->position, ( *lexer )->line,
                                      ( *lexer )->column );
            return token;
        }

        case ';': {
            token = nem_token_create( NTT_SEMICOLON, ";", strlen( ";" ),
                                      ( *lexer )->position, ( *lexer )->line,
                                      ( *lexer )->column );
            return token;
        }

        case ':': {
            // TBD
            if ( nem_lexer_match( lexer, '=' ) ) {
                token = nem_token_create(
                    NTT_DEFINE, ":=", strlen( ":=" ), ( *lexer )->position - 1,
                    ( *lexer )->line, ( *lexer )->column );
            } else {
                token = nem_token_create(
                    NTT_COLON, ":", strlen( ":" ), ( *lexer )->position,
                    ( *lexer )->line, ( *lexer )->column );
            }
            return token;
        }

        case '\0': {
            token = nem_token_create( NTT_EOF, "\0", strlen( "\0" ),
                                      ( *lexer )->position, ( *lexer )->line,
                                      ( *lexer )->column );
            return token;
        }

        default: { // if no match is found, return error token
            token = nem_token_create( NTT_ERROR, "error", strlen( "error" ),
                                      ( *lexer )->position, ( *lexer )->line,
                                      ( *lexer )->column );
            return token;
        }
    }

    return token;
}
