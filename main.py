#!/usr/bin/env python3

import signal
import atexit
import os
import sys
import math
import heapq
from collections import deque, defaultdict, Counter
import string
import time
import itertools
import inspect
from functools import cache, wraps

class Dbg:
    def __init__(self,*args):
        frame = inspect.currentframe().f_back
        info = inspect.getframeinfo(frame)
        names = {id(v): k for k, v in frame.f_locals.items()}

        for var in args:
            name = names.get(id(var), "Unknown")
            print(
                f"\nLine: {info.lineno} -> ({hex(id(var))}) {name}: {type(var).__name__} = {var}\n",
                file=sys.stderr,
            )

            if isinstance(var, (dict, Counter)):
                self._hashmap(var)

            elif isinstance(var, list) and var and isinstance(var[0], list):
                self._matrix(var)

            elif hasattr(var, "next"):
                self._sll(var)

            elif hasattr(var, "left") or hasattr(var, "right"):
                self._tree(var)

            else:
                print(f"  {var}", file=sys.stderr)


    def _hashmap(self,hashmap):
        print(f"  {'KEY':<15} | {'VALUE'}", file=sys.stderr)
        print(f"  {'-' * 30}", file=sys.stderr)
        try:
            items = sorted(hashmap.items())
        except TypeError:
            items = hashmap.items()
        for k, v in items:
            print(f"  {str(k):<15} | {v}", file=sys.stderr)


    def _matrix(self,matrix):
        if not matrix or not matrix[0]:
            print("  Empty {matrix}", file=sys.stderr)
            return
        width = 5
        R = len(matrix)
        C = len(matrix[0])

        print(f"\n({R}x{C})", file=sys.stderr)

        # Create Column Header (0, 1, 2...)
        col_header = " " * 5 + "".join(f"{c:>{width}}" for c in range(C))
        print(col_header, file=sys.stderr)
        print(" " * 4 + "+" + "-" * (C * width), file=sys.stderr)

        for r in range(R):
            row_str = f"{r:3d} |"
            for c in range(C):
                val = matrix[r][c]
                char = "." if val is None else str(val)
                if len(char) > width - 1:
                    char = char[: width - 2] + "+"
                row_str += f"{char:>{width}}"
            print(row_str, file=sys.stderr)
        print(" " * 4 + "+" + "-" * (C * width) + "\n", file=sys.stderr)

    def _sll(self,head):
        res = []
        curr = head
        seen = set()
        bound = 25

        while curr:
            node_id = id(curr)
            if node_id in seen:
                res.append(f"Cycle({curr.val})")
                break

            seen.add(node_id)
            res.append(str(curr.val))
            curr = curr.next

            if len(res) >= bound:
                res.append("...")
                break

        if not curr and len(res) < bound + 1:
            res.append("None")

        res = " -> ".join(res)
        print(f"  {res}", file=sys.stderr)

    def _tree(self,root):
        lines = []

        def _build(node, prefix="", is_left=True, is_root=True):
            if node is None:
                label = "(L)" if is_left else "(R)"
                # Using \-- for bottom (left) and /-- for top (right)
                connector = "  \\-- " if is_left else "  /-- "
                lines.append(f"{prefix}{connector}{label} [N]")
                return

            if node.right or node.left:
                _build(
                    node.right,
                    prefix + ("  |       " if is_left and not is_root else "          "),
                    False,
                    False,
                )

            if is_root:
                connector = "  ROOT--- "
            else:
                label = "(L)" if is_left else "(R)"
                connector = "  \\-- " if is_left else "  /-- "
                connector += label + " "

            lines.append(f"{prefix}{connector}{node.val}")

            if node.left or node.right:
                _build(
                    node.left,
                    prefix + ("          " if is_left or is_root else "  |       "),
                    True,
                    False,
                )

        _build(root)
        print("\n" + "\n".join(lines) + "\n")



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


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
    def __repr__(self):
        return f"ListNode({self.val})"

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
    def __repr__(self):
        left_val = self.left.val if self.left else "null"
        right_val = self.right.val if self.right else "null"
        return f"TreeNode({self.val}, L:{left_val}, R:{right_val})"

class Lexer:
    def __init__(self,src:str):
        self.src = src
    def tokenize(self)->list:
        return self.src.replace('(', ' ( ').replace(')', ' ) ',).split()

class Parser:
    def __init__(self,src:str):
        self.src = src
    def parse(self):
        l = Lexer(self.src)
        tokens = l.tokenize()
        print(tokens)

def load(fileName:str)->str:
    with open(fileName,"r") as file:
        contents = file.read()
        return contents

def main():
    def handler(signum, frame):
        raise Exception("TLE: Test took too long!")

    signal.signal(signal.SIGALRM, handler)

    signal.alarm(2)  # Limit each test to 2 seconds
    start = time.perf_counter()

    src = load("input.scm")
    p = Parser(src)
    p.parse()

    end = time.perf_counter()
    print(f"Time: {end-start} seconds",file=sys.stderr)
    signal.alarm(0)  # Reset


atexit.register(sys.stdout.flush)

if __name__ == "__main__":
    main()
