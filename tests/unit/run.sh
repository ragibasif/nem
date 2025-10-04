#!/bin/sh

clang -DNEM_DEBUG nem_token_test.c ../../src/token.c -o nem_token_test && ./nem_token_test && rm -f nem_token_test
