/*
 * File: utils.h
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 */

#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stdio.h>

extern char *NemReadFile( const char *path );
extern void  NemError( const char *file, const int line, const char *func,
                       const char *fmt, ... );
extern void  NemAllocCheck( void *ptr, size_t size, const char *file,
                            const int line, const char *func );

#define N_ERROR( fmt, ... )                                                    \
    NemError( __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__ )
#define N_ALLOC_CHECK( ptr, size )                                             \
    NemAllocCheck( ptr, size, __FILE__, __LINE__, __func__ )

#ifdef __cplusplus
}
#endif

#endif // UTILS_H
