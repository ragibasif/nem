/*
 * File: cli.c
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 */

#include "cli.h"

#include <stdio.h>
#include <string.h>

#define NEM_VERSION "1.0.0"

#define NEM_USAGE "usage: nem [options] <file>\n"

#define NEM_HELP                                                               \
    "NAME\n"                                                                   \
    "    nem - a lightweight C compiler frontend\n"                            \
    "\n"                                                                       \
    "SYNOPSIS\n"                                                               \
    "    nem [options] <file>\n"                                               \
    "\n"                                                                       \
    "DESCRIPTION\n"                                                            \
    "    The nem command compiles C source files with optional "               \
    "preprocessing,\n"                                                         \
    "    assembly, and linking phases. It supports custom include paths,\n"    \
    "    macro definitions, and library linking similar to GCC or Clang.\n"    \
    "\n"                                                                       \
    "OPTIONS\n"                                                                \
    "    -o, --output <file>\n"                                                \
    "        Specify the output file to write to.\n"                           \
    "\n"                                                                       \
    "    -I, --include-dir <dir>\n"                                            \
    "        Add <dir> to the list of directories searched for #include "      \
    "files.\n"                                                                 \
    "\n"                                                                       \
    "    -D, --define <name>=<value>\n"                                        \
    "        Define a new object-like macro.\n"                                \
    "\n"                                                                       \
    "    -L, --library-path <dir>\n"                                           \
    "        Add <dir> to the library search paths (passed as -L<dir> to the " \
    "linker).\n"                                                               \
    "\n"                                                                       \
    "    -l, --library <name>\n"                                               \
    "        Link against a shared library with <name> (passed as -l<name> "   \
    "to the linker).\n"                                                        \
    "\n"                                                                       \
    "    -E, --preprocess-only\n"                                              \
    "        Stop after preprocessing and print the preprocessed source.\n"    \
    "\n"                                                                       \
    "    -S, --compile-only\n"                                                 \
    "        Stop after compilation and produce an assembly (.s) file.\n"      \
    "\n"                                                                       \
    "    -c, --no-link\n"                                                      \
    "        Stop after assembling and produce an object (.o) file.\n"         \
    "\n"                                                                       \
    "        --dump-ast\n"                                                     \
    "        Display the abstract syntax tree (AST) produced by the parser\n"  \
    "        while compiling as usual.\n"                                      \
    "\n"                                                                       \
    "        --no-color\n"                                                     \
    "        Print diagnostics without ANSI color formatting.\n"               \
    "\n"                                                                       \
    "    -h, --help\n"                                                         \
    "        Display this help information and exit.\n"                        \
    "\n"                                                                       \
    "    -v, --version\n"                                                      \
    "        Display version information and exit.\n"                          \
    "\n"                                                                       \
    "FILES\n"                                                                  \
    "    One or more C source files to be compiled.\n"                         \
    "\n"                                                                       \
    "EXAMPLES\n"                                                               \
    "    nem -o main main.c\n"                                                 \
    "    nem -I include -DDEBUG=1 -c utils.c\n"                                \
    "\n"                                                                       \
    "SEE ALSO\n"                                                               \
    "    gcc(1), clang(1)\n"

static void nem_version_print( void ) {
    fprintf( stderr, "Version: %s\n", NEM_VERSION );
}

static void nem_usage_print( void ) { fprintf( stderr, "%s\n", NEM_USAGE ); }

static void nem_help_print( void ) { fprintf( stderr, "%s\n", NEM_HELP ); }

NemCLI *nem_cli_create( int argc, char **argv ) {
    NemCLI *cli = malloc( sizeof *cli );
    if ( cli == NULL ) { return NULL; }
    nem_version_print();
    nem_usage_print();
    nem_help_print();
    return cli;
}

void nem_cli_destroy( NemCLI **cli ) {
    if ( cli == NULL ) { return; }
    if ( *cli == NULL ) { return; }
    free( *cli );
    *cli = NULL;
}
