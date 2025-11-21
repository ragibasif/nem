/*
 * File: main.c
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 *
 */

#include "common.h"
#include "dbg.h"

struct nem_memory_block {
    struct nem_memory_block *next;
    size_t                   size;
};

static struct nem_memory_block *block_head = NULL;

static void *nem_malloc( size_t size ) {
    assert( size >= 0 );
    if ( size < 0 ) { return NULL; }
    struct nem_memory_block *ptr = malloc( sizeof *ptr + size );
    assert( ptr != NULL );
    ptr->next  = block_head;
    ptr->size  = size;
    block_head = ptr;

    return (void *)ptr + sizeof *ptr;
}

static void *nem_realloc( void *ptr, size_t size ) {
    if ( ptr == NULL ) { return nem_malloc( size ); }

    struct nem_memory_block *block = (struct nem_memory_block *)ptr;
    block--;
    if ( block->size >= size ) { return ptr; }
    void *new_ptr = nem_malloc( size );
    memcpy( new_ptr, ptr, block->size );
    return new_ptr;
}

static void *nem_calloc( size_t count, size_t size ) {
    void *ptr = nem_malloc( count * size );
    memset( ptr, 0, count * size );
    return ptr;
}

static void nem_free( void *ptr ) {
    assert( ptr != NULL );
    struct nem_memory_block *new_ptr = (struct nem_memory_block *)ptr;
    new_ptr--;
    memset( ptr, 0, new_ptr->size );
}

static void nem_free_all( void ) {
    while ( block_head ) {
        struct nem_memory_block *next_block = block_head->next;
        free( block_head );
        block_head = next_block;
    }
}

int main( int argc, char **argv ) { return EXIT_SUCCESS; }
