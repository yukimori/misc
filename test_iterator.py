#!/usr/bin/env python
# -*- coding: utf-8 -*-

class CountDownIter(object):
    def __init__(self, num):
        self.num = num
    def __iter__(self): # in演算子などで利用可能にする
        return self
    def next(self):
        self.num -= 1
        if self.num == 0:
            raise StopIteration
        return self.num

iterator = CountDownIter(5)
print iterator
print iterator.next()
print iterator.next()

for i in iterator:
    print i
