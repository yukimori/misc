#!/usr/bin/env python

"""
http://postd.cc/fibonacci/
"""

def fib(n):
    return (4 << n*(3+n)) // ((4 << 2*n) - (2 << n) -1) & ((2 << n) - 1)

if __name__ == '__main__':
    print fib(1)
    print fib(2)
    print fib(3)
    print fib(4)
