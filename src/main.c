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

#include "alloc.h"
#include "common.h"

int main( int argc, char **argv ) {

    int *a = nem_malloc( 42342 );
    LOG( "test" );
    TRACE( "TRACE" );
    nem_free( a );
    atexit( nem_memory_cleanup );
    return EXIT_SUCCESS;
}
