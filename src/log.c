/*
 * File: log.c
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 */

#include "log.h"

void nem_log_msg( const char *file, const int line, const char *func,
                  const char *msg ) {
    time_t now                       = time( NULL );
    char  *time_str                  = ctime( &now );
    time_str[strlen( time_str ) - 1] = '\0';
    fprintf( stderr, "[%s] ", time_str );
    fprintf( stderr, "[%s:%d:(%s)] ", file, line, func );
    fprintf( stderr, "%s\n", msg );
}
