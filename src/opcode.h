/*
 * File: opcode.h
 * Author: Ragib Asif
 * Email: ragibasif@tuta.io
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 */

#ifndef OPCODE_H
#define OPCODE_H

#ifdef __cplusplus
extern "C" {
#endif

// The list of tokens.
enum OpCodeType {
    // internal
    OCT_COUNT,
};

struct OpCode {
    enum OpCodeType type;
    char           *literal;
};

#ifdef __cplusplus
}
#endif

#endif // OPCODE_H
