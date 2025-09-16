/*
 * File: utils.c
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 */

#include "utils.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

void thal_error_message( const char *file, const int line, const char *func,
                         const char *fmt, ... ) {
    fprintf( stderr, "ERROR " );
    time_t now                       = time( NULL );
    char  *time_str                  = ctime( &now );
    time_str[strlen( time_str ) - 1] = '\0';
    fprintf( stderr, "[%s] ", time_str );
    fprintf( stderr, "[%s:%d:(%s)] ", file, line, func );
    fprintf( stderr, "\n>>\n\t" );
    va_list args;
    va_start( args, fmt );
    vfprintf( stderr, fmt, args );
    fprintf( stderr, "\n<<\n" );
    va_end( args );
}

void thal_alloc_check( void *ptr, size_t size, const char *file, const int line,
                       const char *func ) {
    if ( !ptr ) {
        T_ERROR( "Memory allocation error. Failed to allocate %lu bytes to "
                 "memory address %p." );
        exit( EXIT_FAILURE );
    }
}
