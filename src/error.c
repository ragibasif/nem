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

#include "log.h"

void nem_error_msg( const char *file, const int line, const char *func,
                    const char *msg ) {
    fprintf( stderr, "[ERROR] " );
    nem_log_msg( file, line, func, msg );
}
