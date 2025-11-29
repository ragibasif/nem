/*
 * File: common.h
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 *
 */

#ifndef COMMON_H
#define COMMON_H
#ifdef __cplusplus
extern "C" {
#endif

// Debug - disabled by default, can be enabled with -DDEBUG=1
#ifndef DEBUG
#define DEBUG 0
#endif

#define LOG( fmt, ... )                                                        \
    do {                                                                       \
        fprintf( stderr, "%s:%d in %s(): " fmt "\n", __FILE__, __LINE__,       \
                 __func__, ##__VA_ARGS__ );                                    \
        fflush( stderr );                                                      \
    } while ( 0 )

#if DEBUG
#define TRACE( fmt, ... ) LOG( fmt, ##__VA_ARGS__ )
#else
#define TRACE( fmt, ... )                                                      \
    do { (void)0; } while ( 0 )
#endif

#include <assert.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef __cplusplus
}
#endif
#endif // COMMON_H
