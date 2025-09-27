/*
 * File: util.c
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 */

#include "util.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void nem_panic( const char *file, const int line, const char *func,
                const char *fmt, ... ) {
    fprintf( stderr, "PANIC " );
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
    exit( EXIT_FAILURE );
}

void nem_error( const char *file, const int line, const char *func,
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

void nem_log( const char *file, const int line, const char *func,
              const char *fmt, ... ) {
    fprintf( stderr, "LOG " );
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

void nem_alloc_check( void *ptr, size_t size, const char *file, const int line,
                      const char *func ) {
    if ( !ptr ) {
        nem_panic( __FILE__, __LINE__, __func__,
                   "Memory allocation error. Failed to allocate %lu bytes to "
                   "memory address %p." );
    }
}

// FILE *fopen (const char *file_name, const char *mode)
// r - open file in read mode, set pointer at first character
// w - open file in write mode, if file exists it will be overwritten
// a - open file in append mode, new data will be added to the end of old data
// r+ - open file in read mode and write mode, does not delete existing file or
// create non-existent file
// w+ - open file in read mode and write mode,
// a+ - open file in append mode

char *nem_read_file( const char *path ) {
    FILE *file = fopen( path, "rb" );
    if ( !file ) {
        nem_panic( __FILE__, __LINE__, __func__, "Could not open file \"%s\".",
                   path );
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
        nem_panic( __FILE__, __LINE__, __func__, "Could not read file \"%s\".",
                   path );
    }
    buffer[bytesRead] = '\0';

    fclose( file );
    return buffer;
}

void nem_write_file( const char *path, const char *buffer ) {}
void nem_append_file( const char *path, const char *buffer ) {}
