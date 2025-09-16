/*
 * File: main.c
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 *
 */

#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

void         repl();
void         runFile( char *file );
static char *readFile( const char *path );

static char *readFile( const char *path ) {
    FILE *file = fopen( path, "rb" );
    if ( !file ) {
        T_ERROR( "Could not open file \"%s\".", path );
        exit( EXIT_FAILURE );
    }

    fseek( file, 0L, SEEK_END );
    size_t fileSize = ftell( file );
    rewind( file );

    char *buffer = malloc( fileSize + 1 );
    T_ALLOC_CHECK( buffer, fileSize + 1 );
    size_t bytesRead = fread( buffer, sizeof( char ), fileSize, file );
    if ( bytesRead < fileSize ) {
        T_ERROR( "Could not read file \"%s\".", path );
        exit( EXIT_FAILURE );
    }
    buffer[bytesRead] = '\0';

    fclose( file );
    return buffer;
}

int main( int argc, char **argv ) {
    printf( "thal\n" );
    readFile( "input_c" );
    // if ( argc == 1 ) {
    //     puts( "repl();" );
    // } else if ( argc == 2 ) {
    //     puts( "runFile(argv[1]);" );
    // } else {
    //     fprintf( stderr, "Usage: thal [path]\n" );
    // }

    return EXIT_SUCCESS;
}
