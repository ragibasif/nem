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

#include "dbg.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TEST_FILE "./test_input/input.c"
#define NEM               "nem"

static void run( char *file );

static void run( char *file ) {
    char *buffer = Read( file );
    printf( "%s", buffer );
}

int main( int argc, char **argv ) {
    Log( __FILE__, __LINE__, __func__, "Starting %s:", NEM );

    dbg( DEFAULT_TEST_FILE );

    run( DEFAULT_TEST_FILE );

    Panic( __FILE__, __LINE__, __func__, "Panic!" );

    // if ( argc != 2 ) {
    //     run( DEFAULT_TEST_FILE );
    // } else if ( argc == 2 ) {
    //     run( argv[1] );
    // } else {
    //     fprintf( stderr, "Usage: thal [path]\n" );
    // }

    return EXIT_SUCCESS;
}
