/*
 * File: memory.c
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 */

#include "memory.h"

#include "error.h"

void nem_alloc_check( void *ptr, size_t size, const char *file, const int line,
                      const char *func ) {
    if ( !ptr ) {
        nem_error_msg( file, line, func, "Memory allocation error" );
        exit( EXIT_FAILURE );
    }
}
