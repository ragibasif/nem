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

#include "nem.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void nem_log( const char *file, const int line, const char *func,
              const char *msg ) {
    time_t now                       = time( NULL );
    char  *time_str                  = ctime( &now );
    time_str[strlen( time_str ) - 1] = '\0';
    fprintf( stderr, "[%s] ", time_str );
    fprintf( stderr, "[%s:%d:(%s)] ", file, line, func );
    fprintf( stderr, "%s\n", msg );
}

void nem_panic( const char *file, const int line, const char *func,
                const char *msg ) {
    fprintf( stderr, "[PANIC] " );
    nem_log( file, line, func, msg );
    exit( EXIT_FAILURE );
}

void nem_error( const char *file, const int line, const char *func,
                const char *msg ) {
    fprintf( stderr, "[ERROR] " );
    nem_log( file, line, func, msg );
}

void nem_warn( const char *file, const int line, const char *func,
               const char *msg ) {
    fprintf( stderr, "[WARN] " );
    nem_log( file, line, func, msg );
}

void nem_alloc_check( void *ptr, size_t size, const char *file, const int line,
                      const char *func ) {
    if ( !ptr ) { nem_panic( file, line, func, "Memory allocation error" ); }
}

char *nem_read_file( const char *path ) {
    FILE *file = fopen( path, "rb" );
    if ( !file ) {
        nem_panic( __FILE__, __LINE__, __func__, "Could not open file" );
    }

    if ( !strrchr( path, '.' ) ) {
        nem_panic( __FILE__, __LINE__, __func__,
                   "Input file must end in '.c'" );
    }

    fseek( file, 0L, SEEK_END );
    size_t fileSize = ftell( file );
    rewind( file );

    // Important: remember to free this buffer
    char *buffer = malloc( fileSize + 1 );
    nem_alloc_check( buffer, fileSize + 1, __FILE__, __LINE__, __func__ );

    size_t bytesRead = fread( buffer, sizeof( char ), fileSize, file );
    if ( bytesRead < fileSize ) {
        nem_panic( __FILE__, __LINE__, __func__, "Could not read file" );
    }
    buffer[bytesRead] = '\0';

    fclose( file );
    return buffer;
}
