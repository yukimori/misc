from ctypes import cdll
from ctypes import c_float, CFUNCTYPE, sizeof, POINTER, c_int

libc = cdll.LoadLibrary("libc.so.6")
import random


FloatArray10 = c_float * 10

xs = [random.random() for i in xrange(10)]
fa = FloatArray10(*xs)


def cmp_fn(px, py):
    x = px[0]
    y = py[0]
    return 0 if x == y else (-1 if x < y else 1)

qsort = libc.qsort
qsort.resttype = None

print """original"""

class IterateProxy(object):
    def __init__(self, arr):
        self.arr = arr

    def __len__(self):
        return len(self.arr)

    def __iter__(self):
        return iter(self.arr)

    def __repr__(self):
        return "<%r %s>" % (self.__class__, [x for x in self])

print IterateProxy(fa)
qsort(fa, len(fa), sizeof(c_float), CFUNCTYPE(c_int, POINTER(c_float), POINTER(c_float))(cmp_fn))
print IterateProxy(fa)
