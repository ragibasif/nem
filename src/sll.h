/*
 * File: sll.h
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 *
 */

#ifndef SLL_H
#define SLL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

struct sll;
extern struct sll *sll_append( struct sll *head, void *item );
extern int         sll_size( struct sll *sll );

#ifdef __cplusplus
}
#endif

#endif // SLL_H
