# -*- coding:utf-8 -*-

from __future__ import print_function

# strだが7ビットASCII文字しか含まれないのでunicodeと結合できる
x = b'abcdefg'
y = x[::-1]
print(type(y))
print(y)

w = 'abcdefg'
x = w.encode('utf-8')
y = x[::-1]
z = y.decode('utf-8')
print(type(z))
print(z)

w = 'あいうえお'
print(w)
print("type(w):", type(w)) # str
# x = w.encode('utf-8') # encodeはunicode->strなのでerror!
# y = w[::-1]
z = w.decode('utf-8')
print("w is decoded utf-8 -> z")
print("type(z):",type(z))
print("z:", z)

def to_unicode(unicode_or_str):
    if isinstance(unicode_or_str, str):
        # strからunicodeへの変換
        value = unicode_or_str.decode('utf-8')
    else:
        value = unicode_or_str
    return value
