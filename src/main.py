#!/usr/bin/env python3

from collections import Counter, deque
from typing import Union
from utils import trace, timer

# Types

Symbol = str
Number = Union[int, float]
Atom = Union[Symbol, Number]
List = list[Atom | None]
Exp = Union[Atom, List]
Env = dict


def tokenize(src: str) -> list[str]:
    buf: list[str] = (
        src.replace("(", " ( ")
        .replace(
            ")",
            " ) ",
        )
        .split()
    )
    ptr = 0
    while ptr < len(buf):
        if ";" in buf[ptr]:  # skip comments
            while ptr < len(buf) and buf[ptr] != "(":
                buf[ptr] = ""
                ptr += 1
        else:
            ptr += 1
    stk: list[str] = []
    for item in buf[::-1]:
        if len(item) > 0:
            stk.append(item)
    return stk


def expr(tokens: list[str]) -> Exp:
    if len(tokens) == 0:
        raise SyntaxError("Unexpected EOF")
    token = tokens.pop()
    if token == "(":
        stk = []
        while tokens[-1] != ")":
            stk.append(expr(tokens))
        tokens.pop()  # pop off ')'
        return stk
    elif token == ")":
        raise SyntaxError("Unexpected ')'")
    else:
        return atom(token)


def parse(src: str) -> Exp:
    tokens: list[str] = tokenize(src)
    return expr(tokens)


def atom(token: str) -> Atom:
    try:
        return int(token)
    except ValueError:
        try:
            return float(token)
        except ValueError:
            return str(token)


def test():
    tests = [
        ("(+ 5 (* 2 3) (- 10 7))", 14),
        ("(define radius 10)", None),
        ("(* 3.14 (* radius radius))", 314.0),
        ("(if (> 10 5) 1 0)", 1),
        ("(define fact (lambda (n) (if (<= n 1) 1 (* n (fact (- n 1))))))", None),
        ("(fact 5)", 120),
        ("((lambda (r) (* 3.14 (* r r))) 10)", 314.0),
    ]
    for idx, (source, expected) in enumerate(tests):
        parsed = parse(source)
        print(f"Test {idx}:  {parsed=} | {expected=}")


def main():
    test()


if __name__ == "__main__":
    main()
