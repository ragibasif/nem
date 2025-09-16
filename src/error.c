/*
 * File: error.c
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 */

#include "error.h"

#include <time.h>

void ErrorMessage( const char *file, const int line, const char *func,
                   const char *fmt, ... ) {
    fprintf( stderr, "ERROR " );
    char msg[50];
    strftime( msg, sizeof msg, "%T", localtime( &(time_t){ time( NULL ) } ) );
    fprintf( stderr, "[%s] ", msg );
    fprintf( stderr, "[%s:%d:(%s)] ", file, line, func );
    va_list args;
    va_start( args, fmt );
    vfprintf( stderr, fmt, args );
    fprintf( stderr, "\n" );
    va_end( args );
}
