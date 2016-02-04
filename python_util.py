#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
pythonの役立つ書き方
ref:
http://nonbiri-tereka.hatenablog.com/entry/2016/01/25/073521
"""

print "List"
list = [1,2,3,4,5,6]

print "基本的な書き方"
for i in xrange(len(list)):
    print i,list[i]

print "enumerate関数を使って番号と値を同時に取得する"
for i,number in enumerate(list):
    print i,number

print "同時に2つのオブジェクトでループ"
list,list2 = [1,2,3,4],[5,6,7,8]
for i in xrange(len(list)):
    print list[i],list2[i]

print "zipを使って2つのオブジェクトをループ"
for num1,num2 in zip(list,list2):
    print num1,num2

print "zipとenumerateの組み合わせ"
for index,(num1,num2) in enumerate(zip(list,list2)):
    print index, num1, num2

print "yieldにより途中で一旦返す。バッチ学習"
print "list[i:i+batch]が表示される"
def iteration_list(list, batch=2):
    for i in xrange(0, len(list), batch):
        yield list[i:i+batch]
for obj in iteration_list(list):
    print obj

print "リスト内包表記"
print [i for i in xrange(10)]

print "リスト内包表記:条件式を使って特定の値を取得"
print [i for i in xrange(10) if i == 2]

print "Collections"
import collections
counter_list = ["a","b","c","d","e","a","a"]

print "listの要素数をカウントする"
counter = collections.Counter(counter_list)
print counter
print type(counter)
print "指定した要素値の要素数を取得する"
print counter["a"]

print "辞書のデフォルト値設定"
print "基本の記述方式"
dict = {}
if "a" in dict:
    dict["a"] += 1
else:
    dict["a"] = 0
print dict
print dict["a"]
print "collectionsを使って簡単に記述"
dict = collections.defaultdict(int)
dict["a"] += 1
print dict
print dict["a"]

print "# Sort"
list = [1,4,3,6,5,8]
print sorted(list)
print sorted(list, reverse=True)
print "辞書のソート"
dict = {"a":1,"b":2,"c":1}
print sorted(dict.items(), key=lambda x:x[0], reverse=True)
print sorted(dict.items(), key=lambda x:x[1], reverse=True)

print "# if"
a = 70
if a > 10 and a < 100:
    print "True"
else:
    print "False"
print "条件を連結して書くことができる"
if 100 > a > 10:
    print "True"
else:
    print "False"

print "# File"
f = open("test.txt")
f.close()

print "with statementの導入により自分でクローズする必要がなくなる"
with open("test.txt") as f:
    print f.read()

print "# in"
print "基本的な書き方"
searched_number = 4
for i in [1,2,3,4,5,6]:
    if i == searched_number:
        print "find!"
        break
print "ifステートメントを使って簡単にする"
if searched_number in list:
    print "find!"

print "関数について"
print "返り値を複数返す"
def return_function(a,b):
    return a,b
print return_function("a","b")

print "関数のオブジェクト化"
def sum(a,b):
    return a + b
def diff(a,b):
    return a - b
func_obj = sum
print func_obj(1,2)


