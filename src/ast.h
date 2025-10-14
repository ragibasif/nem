/*
 * File: ast.h
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 */

#ifndef AST_H
#define AST_H
#ifdef __cplusplus
extern "C" {
#endif

#include "token.h"

typedef enum {
    NNT_EXPR,
    NNT_DECL,
    NNT_STMT,
    NNT_COUNT,
} NemNodeType;

typedef struct {
    NemToken *token;
} NemNode;

typedef struct {
    NemNode *node;
} NemExpr;

typedef struct {
    NemNode *node;
} NemDecl;

typedef struct {
    NemNode *node;
} NemStmt;

#ifdef __cplusplus
}
#endif
#endif // AST_H

////////////////////////////////////////////////////////////////////////////////
// Notes
////////////////////////////////////////////////////////////////////////////////

/*

   - statement
   - expression
   - declaration

*/
