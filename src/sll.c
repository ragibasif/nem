/*
 * File: sll.c
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 *
 */

#include "sll.h"

#include "memory.h"

struct sll {
    void       *item;
    struct sll *next;
};

static struct sll *sll_create( void *item ) {
    struct sll *sll = nem_malloc( sizeof *sll );
    sll->item       = item;
    sll->next       = NULL;
    return sll;
}

struct sll *sll_append( struct sll *head, void *item ) {
    struct sll *sll = sll_create( item );
    sll->next       = head;
    head            = sll;
    return head;
}

int sll_size( struct sll *sll ) {
    struct sll *curr = sll;
    int         size = 0;
    while ( curr ) {
        size++;
        curr = curr->next;
    }
    return size;
}
