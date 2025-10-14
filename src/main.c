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

#include "cli.h"
#include "compiler.h"
#include "dbg.h"

#define DEFAULT_TEST_FILE "tests/e2e/test_00001.c"

static char *nem_read_file( const char *path ) {
    FILE *file = fopen( path, "rb" );
    if ( !file ) {
        fprintf( stderr, "Could not open file\n" );
        exit( EXIT_FAILURE );
    }

    if ( !strrchr( path, '.' ) ) {
        fprintf( stderr, "Input file must end in '.c'\n" );
        exit( EXIT_FAILURE );
    }

    fseek( file, 0L, SEEK_END );
    size_t fileSize = ftell( file );
    rewind( file );

    // Important: remember to free this buffer
    char *buffer = malloc( fileSize + 1 );
    if ( !buffer ) {
        fprintf( stderr, "Could not allocate memory\n" );
        exit( EXIT_FAILURE );
    }

    size_t bytesRead = fread( buffer, sizeof( char ), fileSize, file );
    if ( bytesRead < fileSize ) {
        fprintf( stderr, "Could not read file\n" );
        exit( EXIT_FAILURE );
    }
    buffer[bytesRead] = '\0';

    fclose( file );
    return buffer;
}

static void nem_run( const char *path ) {
    // PERF: remember to free these buffers
    // NOTE: freed in nem_lexer_destroy
    char *file = malloc( sizeof *file * ( strlen( path ) + 1 ) );
    if ( file == NULL ) { return; }
    memcpy( file, path, sizeof *file * ( strlen( path ) + 1 ) );
    char *buffer = nem_read_file( file );

    nem_compiler_run( buffer, file );
}

int main( int argc, char **argv ) {

    NemCLI *cli = nem_cli_create( argc, argv );

    nem_cli_destroy( &cli );

    dbg( DEFAULT_TEST_FILE );

    char *input = DEFAULT_TEST_FILE;

    nem_run( DEFAULT_TEST_FILE );

    return EXIT_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////
// Notes
////////////////////////////////////////////////////////////////////////////////

/*
 * compilers - takes source code and translates it into machine language
 * compilation stages:
 * lexer - tokenize the source code
 * parser - convert tokens to ast
 * assembly - convert ast to assembly
 * code emission - write assembly to file
 * compiler driver calls the preprocessor, compiler, assembler, and linker
 * clang, gcc are compiler drivers
 * compiler takes .c and outputs .o
 * linker takes all .o and generates executable
 * ld - GNU linker
 * as - GNU assembler
 * syntactic analysis - done during compile time and outputs a tree data
 *  structure in accordance to syntax rules
 * semantic evaluation - during run time, takes the tree as input
 * BNF grammar - Backus-Naur Form, a list of syntax rules
 * parsing - checks if a string is in the grammar
 * every derivation has a corresponding parse tree
 * parse trees can be built top down or bottom up from the derivation
 * parse trees contain all the information in a derivation of a string
 * abstract syntax tree (AST) - a parse tree with non-essential nodes left out
 */

////////////////////////////////////////////////////////////////////////////////
