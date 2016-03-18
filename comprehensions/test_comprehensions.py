#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
ref:
http://qiita.com/y__sama/items/a2c458de97c4aa5a98e7
http://d.hatena.ne.jp/nihohi/20120831/1346376992
"""
print "イテレータ"
i = iter('12345')
print i
print i.next()
print i.next()
print i.next()

print "ジェネレータとは一旦何らかの値を戻して"
print "しばらく後にその時点から処理を再開できる関数"



# 通常のリスト生成
extension_1 = []
for i in range(10):
    extension_1.append(i)
print extension_1

# リスト内包表記
print "基本構文:[counter for counter in iterator]"
comprehension_1 = [i for i in range(10)]
print comprehension_1

# 後置if
extension_2 = []
for i in range(10):
    if i%2==0:
        extension_2.append(i)
print extension_2

comprehension_2 = [i for i in range(10) if i%2==0]
print comprehension_2

# if elseを含む場合（条件演算子）
extension_3 = []
for i in range(10):
    if i%2==0:
        extension_3.append(i)
    else:
        extension_3.append(str(i))
print extension_3

comprehension_3 = [i if i%2==0 else str(i) for i in range(10)]
print comprehension_3

print "辞書内包表記"
comprehension_dict = {str(i):i for i in range(10)}
print(comprehension_dict)

label = ["kinoko", "takenoko", "suginoko"]
feature = ["yama", "sato", "mura"]
print {i:j for i,j in zip(label, feature)}

print "セット内包表記"
comprehension_set = {i%5 for i in range(10)}
print comprehension_set

print "ジェネレータ式とタプル内包表記"
comprehension_gen=(i%5 for i in range(10))
print comprehension_gen
for i in comprehension_gen:print(i)

print "内包表記を使わない書き方"
# ジェネレータを生成する関数を作成
def gen_func():
    for i in range(10):
        yield i%5
extension_gen=gen_func()
print extension_gen

print "タプル内包表記"
print tuple([i for i in range(10)])
#print tuple((i for i in range())) # TODO: still error

print "map,filter"
print "python2系ではmap,filterはリストを返却するのでリスト内包表記と対応する"
print "python3系ではmap,filaterオブジェクトというイテレータを返却するためジェネレータと対応する"
print "mapでの書き換え"
print map(lambda i:i**2, range(1,11))

print "条件演算子を複数つなげる"
fizzbuzz = []
for i in range(1,16):
    if i%15 == 0:
        fizzbuzz.append("fizzbuzz")
    elif i%3 == 0:
        fizzbuzz.append("fizz")
    elif i%5 == 0:
        fizzbuzz.append("buzz")
    else:
        fizzbuzz.append(i)

["fizzbuzz" if i%15==0 else "fizz" if i%3==0 else "buzz" if i%5==0 else i for i in range(1,16)]
        
