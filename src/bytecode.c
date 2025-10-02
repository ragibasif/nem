/*
 * File: bytecode.c
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 */

#include "bytecode.h"

#include "util.h"

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_CAPACITY 8

void chunk_init( struct Chunk *chunk ) {
    chunk->size     = 0;
    chunk->capacity = 0;
    chunk->code     = NULL;
    chunk->lines    = NULL;
    values_create( &chunk->constants );
}

void chunk_push( struct Chunk *chunk, uint8_t byte, int line ) {
    if ( chunk->size >= chunk->capacity ) {
        if ( !chunk->capacity ) {
            chunk->capacity = DEFAULT_CAPACITY;
        } else {
            chunk->capacity <<= 1;
        }
        uint8_t *code_buffer =
            realloc( chunk->code, sizeof *chunk->code * chunk->capacity );
        nem_alloc_check( code_buffer, sizeof *chunk->code * chunk->capacity,
                         __FILE__, __LINE__, __func__ );
        chunk->code = code_buffer;

        int *line_buffer =
            realloc( chunk->lines, sizeof *chunk->lines * chunk->capacity );
        nem_alloc_check( line_buffer, sizeof *chunk->lines * chunk->capacity,
                         __FILE__, __LINE__, __func__ );
        chunk->lines = line_buffer;
    }
    chunk->code[chunk->size]  = byte;
    chunk->lines[chunk->size] = line;
    chunk->size++;
}

void chunk_cleanup( struct Chunk *chunk ) {
    if ( !chunk ) {
        nem_panic( __FILE__, __LINE__, __func__, "address points to NULL" );
    }
    values_destroy( &chunk->constants );
    chunk->size     = 0;
    chunk->capacity = 0;
    free( chunk->code );
    chunk->code = NULL;
    free( chunk->lines );
    chunk->lines = NULL;
}

size_t constant_add( struct Chunk *chunk, Value value ) {
    // add the constant and return its index
    values_push( &chunk->constants, value );
    return chunk->constants.size - 1;
}

// debug
void chunk_disassemble( struct Chunk *chunk, const char *name ) {
    printf( " == %s ==\n", name );

    for ( size_t offset = 0; offset < chunk->size; ) {
        offset = instruction_disassemble( chunk, offset );
    }
}

static size_t instruction_constant( const char *name, struct Chunk *chunk,
                                    size_t offset ) {
    uint8_t constant = chunk->code[offset + 1];
    printf( "%-16s %4d '", name, constant );
    value_print( chunk->constants.values[constant] );
    printf( "'\n" );
    return offset + 2;
}
static size_t instruction_simple( const char *name, size_t offset ) {
    printf( "%s\n", name );
    return offset + 1;
}

size_t instruction_disassemble( struct Chunk *chunk, size_t offset ) {
    printf( "%04zu ", offset );

    if ( offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1] ) {
        printf( "    | " );
    } else {
        printf( "%4d ", chunk->lines[offset] );
    }

    // returns the offset of the next instruction
    uint8_t instruction = chunk->code[offset];
    switch ( instruction ) {
        case OP_CONSTANT:
            return instruction_constant( "OP_CONSTANT", chunk, offset );
        case OP_RETURN: return instruction_simple( "OP_RETURN", offset );
        default:
            printf( "Unknown opcode %d\n", instruction );
            return offset + 1;
    }
}
