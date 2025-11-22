/*
 * File: alloc.h
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 *
 * Description:
 *   Brief description of what this header file provides.
 *   Include its purpose and main functionality.
 *
 * Notes:
 *   - Any important implementation notes or caveats
 *   - Dependencies or requirements
 *   - Known limitations or future improvements
 *
 */

#ifndef ALLOC_H
#define ALLOC_H

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================
 * Includes
 * ============================================================================
 */

#include <stddef.h>

/* ============================================================================
 * Function Declarations
 * ============================================================================
 */

extern void *nem_malloc( const size_t size );
extern void *nem_realloc( void *old_ptr, const size_t size );
extern void *nem_calloc( const size_t count, const size_t size );
extern void  nem_free( void *ptr );
extern void  nem_memory_cleanup( void );

#ifdef __cplusplus
}
#endif

#endif /* ALLOC_H */
