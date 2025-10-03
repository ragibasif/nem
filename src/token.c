/*
 * File: token.c
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 */

#include "nem.h"

#include <stdio.h>

void nem_token_create( struct NemToken *token, char *literal );

void nem_token_destroy( struct NemToken *token );

void nem_token_print( struct NemToken *token ) {
    printf( "%s\n", token->name );
    printf( "%s\n", token->literal );
}
