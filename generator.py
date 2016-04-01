#!/usr/bin/env python
# -*- coding: utf-8 -*-

def count_down_gen(num):
    while True:
        if num==0:
            raise StopIteration
        yield num
        num -= 1

g1 = count_down_gen(5)
print g1
print g1.next()
print g1.next()

g2 = count_down_gen(5)
for g in g2:
    print g

print "ジェネレータではイテレータでは不可能な無限数列なども実装できる"
