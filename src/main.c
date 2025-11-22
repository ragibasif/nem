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
#define NEM_MEMORY_REPORT

struct nem_memory_block {
    struct nem_memory_block *next;
    size_t                   size;
};

static struct nem_memory_block *block_head = NULL;

extern void *nem_malloc( const size_t size );
extern void *nem_realloc( void *old_ptr, const size_t size );
extern void *nem_calloc( const size_t count, const size_t size );
extern void  nem_free( void *ptr );
extern void  nem_free_all( void );

void *nem_malloc( const size_t size ) {
    if ( !( size > 0 ) ) { return NULL; }
    struct nem_memory_block *ptr = malloc( sizeof *ptr + size );
    assert( ptr != NULL );
    ptr->next  = block_head;
    ptr->size  = size;
    block_head = ptr;

    return (void *)ptr + sizeof *ptr;
}

void *nem_realloc( void *old_ptr, const size_t size ) {
    if ( old_ptr == NULL ) { return nem_malloc( size ); }

    struct nem_memory_block *block = (struct nem_memory_block *)old_ptr;
    block--;
    if ( block->size >= size ) { return old_ptr; }
    void *new_ptr = nem_malloc( size );
    memcpy( new_ptr, old_ptr, block->size );
    return new_ptr;
}

void *nem_calloc( const size_t count, const size_t size ) {
    void *ptr = nem_malloc( count * size );
    memset( ptr, 0, count * size );
    return ptr;
}

void nem_free( void *ptr ) {
    assert( ptr != NULL );
    struct nem_memory_block *new_ptr = (struct nem_memory_block *)ptr;
    new_ptr--;
    memset( ptr, 0, new_ptr->size );
}

static size_t nem_allocation_count( void ) {
    size_t                   count = 0;
    struct nem_memory_block *block = block_head;
    while ( block ) {
        count++;
        block = block->next;
    }
    return count;
}

static size_t nem_total_allocated( void ) {
    size_t                   total = 0;
    struct nem_memory_block *block = block_head;
    while ( block ) {
        total += block->size;
        block = block->next;
    }
    return total;
}

static size_t nem_total_memory_usage( void ) {
    size_t                   total = 0;
    struct nem_memory_block *block = block_head;
    while ( block ) {
        total += sizeof *block + block->size;
        block = block->next;
    }
    return total;
}

void nem_free_all( void ) {
#ifdef NEM_MEMORY_REPORT
    size_t allocation_count       = nem_allocation_count();
    size_t total_memory_allocated = nem_total_allocated();
    size_t total_memory_usage     = nem_total_memory_usage();
    fprintf( stdout,
             "Nem Memory Report:\nAllocation Count: %zu\nMemory Allocated: "
             "%zu\nMemory Usage: %zu\n",
             allocation_count, total_memory_allocated, total_memory_usage );
#endif
    while ( block_head ) {
        struct nem_memory_block *next_block = block_head->next;
        free( block_head );
        block_head = next_block;
    }
}
int main( int argc, char **argv ) {
    int *a = nem_malloc( 42342 );
    nem_free( a );
    nem_free_all();
    return EXIT_SUCCESS;
}
