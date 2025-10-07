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

void nem_token_type_print( const NemTokenType type ) {
    switch ( type ) {
        case NTT_ERROR: printf( "error" ); break;
        case NTT_EOF: printf( "eof" ); break;
        case NTT_COMMENT: printf( "" ); break;
        case NTT_IDENTIFIER: printf( "" ); break;
        case NTT_NUMBER: printf( "" ); break;
        case NTT_DIGIT: printf( "" ); break;
        case NTT_INTEGER: printf( "" ); break;
        case NTT_DOUBLE: printf( "" ); break;
        case NTT_FLOAT: printf( "" ); break;
        case NTT_CHARACTER: printf( "" ); break;
        case NTT_STRING: printf( "" ); break;
        case NTT_CONSTANT: printf( "" ); break;
        case NTT_PLUS: printf( "" ); break;
        case NTT_MINUS: printf( "" ); break;
        case NTT_MULTIPLY: printf( "" ); break;
        case NTT_DIVIDE: printf( "" ); break;
        case NTT_MODULO: printf( "" ); break;
        case NTT_INVERT: printf( "" ); break;
        case NTT_BITWISE_AND: printf( "" ); break;
        case NTT_BITWISE_OR: printf( "" ); break;
        case NTT_BITWISE_XOR: printf( "" ); break;
        case NTT_BITWISE_SHIFT_LEFT: printf( "" ); break;
        case NTT_BITWISE_SHIFT_RIGHT: printf( "" ); break;
        case NTT_PLUS_ASSIGNMENT: printf( "" ); break;
        case NTT_MINUS_ASSIGNMENT: printf( "" ); break;
        case NTT_MULTIPLY_ASSIGNMENT: printf( "" ); break;
        case NTT_DIVIDE_ASSIGNMENT: printf( "" ); break;
        case NTT_MODULO_ASSIGNMENT: printf( "" ); break;
        case NTT_BITWISE_AND_ASSIGNMENT: printf( "" ); break;
        case NTT_BITWISE_OR_ASSIGNMENT: printf( "" ); break;
        case NTT_BITWISE_XOR_ASSIGNMENT: printf( "" ); break;
        case NTT_BITWISE_SHIFT_LEFT_ASSIGNMENT: printf( "" ); break;
        case NTT_BITWISE_SHIFT_RIGHT_ASSIGNMENT: printf( "" ); break;
        case NTT_LOGICAL_AND: printf( "" ); break;
        case NTT_LOGICAL_OR: printf( "" ); break;
        case NTT_ARROW: printf( "" ); break;
        case NTT_INCREMENT: printf( "" ); break;
        case NTT_DECREMENT: printf( "" ); break;
        case NTT_EQUAL: printf( "" ); break;
        case NTT_LESS: printf( "" ); break;
        case NTT_GREATER: printf( "" ); break;
        case NTT_ASSIGNMENT: printf( "" ); break;
        case NTT_NOT: printf( "" ); break;
        case NTT_QUESTION: printf( "" ); break;
        case NTT_NOT_EQUAL: printf( "" ); break;
        case NTT_LESS_EQUAL: printf( "" ); break;
        case NTT_GREATER_EQUAL: printf( "" ); break;
        case NTT_ELLIPSIS: printf( "" ); break;
        case NTT_DEFINE: printf( "" ); break;
        case NTT_POINTER: printf( "" ); break;
        case NTT_TYPE_NAME: printf( "" ); break;
        case NTT_TYPEDEF: printf( "" ); break;
        case NTT_OPEN_PARENTHESIS: printf( "" ); break;
        case NTT_OPEN_SQUARE_BRACKET: printf( "" ); break;
        case NTT_OPEN_CURLY_BRACE: printf( "" ); break;
        case NTT_CLOSE_PARENTHESIS: printf( "" ); break;
        case NTT_CLOSE_SQUARE_BRACKET: printf( "" ); break;
        case NTT_CLOSE_CURLY_BRACE: printf( "" ); break;
        case NTT_COMMA: printf( "" ); break;
        case NTT_PERIOD: printf( "" ); break;
        case NTT_SEMICOLON: printf( "" ); break;
        case NTT_COLON: printf( "" ); break;
        case NTT_AUTO: printf( "" ); break;
        case NTT_BREAK: printf( "" ); break;
        case NTT_CASE: printf( "" ); break;
        case NTT_CONST: printf( "" ); break;
        case NTT_CONTINUE: printf( "" ); break;
        case NTT_PRINT: printf( "" ); break;
        case NTT_TRUE: printf( "" ); break;
        case NTT_FALSE: printf( "" ); break;
        case NTT_DEFAULT: printf( "" ); break;
        case NTT_DO: printf( "" ); break;
        case NTT_ELSE: printf( "" ); break;
        case NTT_FOR: printf( "" ); break;
        case NTT_ENUM: printf( "" ); break;
        case NTT_EXTERN: printf( "" ); break;
        case NTT_INT: printf( "" ); break;
        case NTT_CHAR: printf( "" ); break;
        case NTT_LONG: printf( "" ); break;
        case NTT_REGISTER: printf( "" ); break;
        case NTT_SHORT: printf( "" ); break;
        case NTT_SIGNED: printf( "" ); break;
        case NTT_SIZEOF: printf( "" ); break;
        case NTT_STATIC: printf( "" ); break;
        case NTT_STRUCT: printf( "" ); break;
        case NTT_NTTDEF: printf( "" ); break;
        case NTT_UNION: printf( "" ); break;
        case NTT_UNSIGNED: printf( "" ); break;
        case NTT_VOLATILE: printf( "" ); break;
        case NTT_WHILE: printf( "" ); break;
        case NTT_DEFER: printf( "" ); break;
        case NTT_FUNCTION: printf( "" ); break;
        case NTT_GOTO: printf( "" ); break;
        case NTT_IF: printf( "" ); break;
        case NTT_IMPORT: printf( "" ); break;
        case NTT_RETURN: printf( "" ); break;
        case NTT_SWITCH: printf( "" ); break;
        case NTT_VARIABLE: printf( "" ); break;
        case NTT_VOID: printf( "" ); break;
        case NTT_BOOL: printf( "" ); break;
        case NTT_INT8: printf( "" ); break;
        case NTT_UINT8: printf( "" ); break;
        case NTT_INT16: printf( "" ); break;
        case NTT_UINT16: printf( "" ); break;
        case NTT_INT32: printf( "" ); break;
        case NTT_UINT32: printf( "" ); break;
        case NTT_INT64: printf( "" ); break;
        case NTT_UINT64: printf( "" ); break;
        case NTT_FLT32: printf( "" ); break;
        case NTT_FLT64: printf( "" ); break;
        case NTT_ID: printf( "" ); break;
        case NTT_COUNT: printf( "" ); break;
        default: printf( "<<<UNKNOWN TOKEN TYPE %d >>>\n", type ); break;
    }
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
