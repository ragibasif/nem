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

#include "value.h"

#include "util.h"

#include <stdio.h>
#define DEFAULT_CAPACITY 8

void values_create( struct Values *values ) {
    values->values   = NULL;
    values->size     = 0;
    values->capacity = 0;
}

void values_push( struct Values *values, Value value ) {

    if ( values->size >= values->capacity ) {
        if ( !values->capacity ) {
            values->capacity = DEFAULT_CAPACITY;
        } else {
            values->capacity <<= 1;
        }
        Value *buffer = realloc( values->values,
                                 sizeof *values->values * values->capacity );
        nem_alloc_check( buffer, sizeof *values->values * values->capacity,
                         __FILE__, __LINE__, __func__ );
        values->values = buffer;
    }
    values->values[values->size++] = value;
}

void values_destroy( struct Values *values ) {
    if ( !values ) {
        nem_panic( __FILE__, __LINE__, __func__, "address points to NULL" );
    }
    values->size     = 0;
    values->capacity = 0;
    free( values->values );
    values->values = NULL;
}

void value_print( Value value ) { printf( "%g", value ); }
