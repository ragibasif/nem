/*
 * File: bytecode.h
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 */

#ifndef BYTECODE_H
#define BYTECODE_H

#include "value.h"

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum OpCode {
    OP_CONSTANT,
    OP_RETURN, // return from current function
    // internal
    OP_COUNT,
};

struct Chunk {
    size_t        size;
    size_t        capacity;
    uint8_t      *code;
    int          *lines;
    struct Values constants;
};

extern void chunk_init( struct Chunk *chunk );
extern void chunk_push( struct Chunk *chunk, uint8_t byte, int line );
extern void chunk_cleanup( struct Chunk *chunk );

extern size_t constant_add( struct Chunk *chunk, Value value );

// debug
extern void   chunk_disassemble( struct Chunk *chunk, const char *name );
extern size_t instruction_disassemble( struct Chunk *chunk, size_t offset );

#ifdef __cplusplus
}
#endif

#endif // BYTECODE_H
