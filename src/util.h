/*
 * File: util.h
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 */

#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

// File I/O
extern char *nem_read_file( const char *path );
extern void  nem_write_file( const char *path, const char *buffer );
extern void  nem_append_file( const char *path, const char *buffer );

// prints error message
extern void nem_error( const char *file, const int line, const char *func,
                       const char *fmt, ... );

// prints error message and exits
extern void nem_panic( const char *file, const int line, const char *func,
                       const char *fmt, ... );

extern void nem_log( const char *file, const int line, const char *func,
                     const char *fmt, ... );

// check for successful dynamic memory allocation
extern void nem_alloc_check( void *ptr, size_t size, const char *file,
                             const int line, const char *func );

#ifdef __cplusplus
}
#endif

#endif // UTIL_H
