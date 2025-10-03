/*
 * File: memory.h
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 */

#ifndef MEMORY_H
#define MEMORY_H
#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////

#include "common.h"

// check for successful dynamic memory allocation
extern void nem_alloc_check( void *ptr, size_t size, const char *file,
                             const int line, const char *func );

////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif
#endif // MEMORY_H
