#!/usr/bin/env python3

import signal
import atexit
import sys
from collections import Counter, deque
import time
import inspect
from functools import wraps


# Types

Symbol = str
List = list
Number = (int, float)
Atom = (Symbol, Number)


def trace(func):
    """Decorator to trace recursive functions."""
    level = 0

    @wraps(func)
    def wrapper(*args, **kwargs):
        nonlocal level
        indent = "  | " * level
        arg_str = ", ".join(map(repr, args))
        print(f"{indent}+-- {func.__name__}({arg_str})", file=sys.stderr)
        level += 1
        res = func(*args, **kwargs)
        level -= 1
        print(f"{indent}+-- return {repr(res)}", file=sys.stderr)
        return res

    return wrapper


def timer(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        start = time.perf_counter()
        result = func(*args, **kwargs)
        end = time.perf_counter()
        duration = end - start
        print(f"[{func.__name__}] {duration:.4f}s ({duration * 1000:.2f}ms)")
        return result

    return wrapper


class Lexer:
    def __init__(self, src: str):
        self.src = src

    @timer
    def tokenize(self) -> deque[str]:
        buf = (
            self.src.replace("(", " ( ")
            .replace(
                ")",
                " ) ",
            )
            .split()
        )
        ptr = 0
        while ptr < len(buf):
            if ";" in buf[ptr]:
                while ptr < len(buf) and buf[ptr] != "(":
                    buf[ptr] = None
                    ptr += 1
            else:
                ptr += 1
        res = deque([])
        for item in buf:
            if item:
                res.append(item)
        return res


class Parser:
    def __init__(self, src: str):
        self.src = src
        self.tokens = Lexer(self.src).tokenize()

    def parse(self):
        while self.tokens:
            node = self.expr()
            print(node)
            for item in node:
                print(item)

    @trace
    def expr(self):
        if len(self.tokens) == 0:
            raise SyntaxError("Unexpected EOF")
        token = self.tokens.popleft()
        if token == "(":
            stack = []
            while self.tokens[0] != ")":
                stack.append(self.expr())
            self.tokens.popleft()  # pop off ')'
            return stack
        elif token == ")":
            raise SyntaxError("Unexpected ')'")
        else:
            return self.atom(token)

    def atom(self, token: str) -> Atom:
        try:
            return int(token)
        except ValueError:
            try:
                return float(token)
            except ValueError:
                return str(token)


def test():
    scheme_tests = [
        # 1. Basic Arithmetic
        ("(+ 5 (* 2 3) (- 10 7))", 14),
        # 2. Variable Definition
        ("(define radius 10)", None),
        ("(* 3.14 (* radius radius))", 314.0),
        # 3. Conditional Logic
        ("(if (> 10 5) 1 0)", 1),
        # 4. Factorial (Recursion)
        ("(define fact (lambda (n) (if (<= n 1) 1 (* n (fact (- n 1))))))", None),
        ("(fact 5)", 120),
        # 5. Lambda Functions
        ("((lambda (r) (* 3.14 (* r r))) 10)", 314.0),
    ]
    for idx, (source, expected) in enumerate(scheme_tests):
        parsed = Parser(source).parse()
        print(idx, parsed, expected)


def main():
    def handler(signum, frame):
        raise Exception("Time Limit Exceeded (TLE)")

    signal.signal(signal.SIGALRM, handler)

    signal.alarm(2)  # Limit each test to 2 seconds

    test()

    signal.alarm(0)  # Reset


if __name__ == "__main__":
    atexit.register(sys.stdout.flush)
    main()
