/*
 * File: symbol.h
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 *
 */

#ifndef SYMBOL_H
#define SYMBOL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "sll.h"

struct symbol {
    char              *name;
    int                scope;
    struct coordinate *src;
    struct symbol     *up;
    struct sll        *uses;
    int                sclass;
};

#ifdef __cplusplus
}
#endif

#endif // SYMBOL_H
