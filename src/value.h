/*
 * File: value.h
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 */

#ifndef VALUE_H
#define VALUE_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef double Value;

struct Values {
    size_t capacity;
    size_t size;
    Value *values;
};

extern void values_create( struct Values *values );
extern void values_push( struct Values *values, Value value );
extern void values_destroy( struct Values *values );

extern void value_print( Value value );

#ifdef __cplusplus
}
#endif

#endif // VALUE_H
