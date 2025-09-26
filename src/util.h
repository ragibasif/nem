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
extern char *Read( const char *path );
extern void  Write( const char *path, const char *buffer );
extern void  Append( const char *path, const char *buffer );

// prints error message
extern void Error( const char *file, const int line, const char *func,
                   const char *fmt, ... );

// prints error message and exits
extern void Panic( const char *file, const int line, const char *func,
                   const char *fmt, ... );

extern void Log( const char *file, const int line, const char *func,
                 const char *fmt, ... );

// check for successful dynamic memory allocation
extern void AllocCheck( void *ptr, size_t size, const char *file,
                        const int line, const char *func );

#ifdef __cplusplus
}
#endif

#endif // UTIL_H
