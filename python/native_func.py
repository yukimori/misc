import ctypes
from ctypes import cdll
from ctypes import c_float, CFUNCTYPE, sizeof, POINTER, c_int


"""
ref:
http://d.hatena.ne.jp/podhmo/20120720/1342800080

20160526 rdrand()でエラーが発生。未解決
"""


def native_func(bytecode):
    libc = ctypes.CDLL('libc.so.6')
    libc.mmap.restype = ctypes.c_void_p
    buf = libc.mmap(None, len(bytecode), 7, 0x22, -1, 0)
    libc.memcpy(ctypes.c_void_p(buf), ctypes.c_char_p(bytecode), len(bytecode))
    return ctypes.CFUNCTYPE(ctypes.c_void_p)(buf)

if __name__ == '__main__':
    rdrand = native_func('\x48\x0f\xc7\xf0\xc3')  # rdrand rax; ret
    print hex(rdrand())
