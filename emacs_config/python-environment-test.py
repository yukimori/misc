#!/usr/bin/env python

print "foo"
print "bar"


def add(x,y):
    return x + y


class A(object):
    def foo(self):
        print "A.foo()"

print add(10, 20)

A().foo()
