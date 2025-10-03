/*
 * File: error.h
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 */

#ifndef ERROR_H
#define ERROR_H
#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////

#include "common.h"

extern void nem_error_msg( const char *file, const int line, const char *func,
                           const char *msg );

////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif
#endif // ERROR_H
