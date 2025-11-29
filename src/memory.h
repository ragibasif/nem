/*
 * File: memory.h
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 *
 */

#ifndef MEMORY_H
#define MEMORY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

extern void *nem_malloc( const size_t size );
extern void *nem_realloc( void *old_ptr, const size_t size );
extern void *nem_calloc( const size_t count, const size_t size );
extern void  nem_free( void *ptr );
extern void  nem_memory_cleanup( void );

#ifdef __cplusplus
}
#endif

#endif // MEMORY_H
