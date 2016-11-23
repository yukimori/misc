#!/usr/bin/env python
#-*- coding:utf-8 -*-

"""
ref:
https://github.com/bslatkin/effectivepython
"""

a = [1, 2, 3, 4, 5]

# リストの要素の平方を計算する
squares = [x ** 2 for x in a]
print squares
# mapで実装
squares = map(lambda x: x**2, a)
print squares



# 2で割れる数だけ平方を計算する
even_squares = [ x**2 for x in a if x%2 == 0]
print even_squares

# map,filterで実装
alt = map(lambda x: x**2, filter(lambda x: x%2==0, a))
assert even_squares == list(alt)

# 辞書と集合でのlist comprehension
chile_ranks = {'gost':1, 'habanero':2,  'cayenne':3}
rank_dict = {rank: name for name, rank in chile_ranks.items()}
chile_len_set = {len(name) for name in rank_dict.values()}
print rank_dict
print chile_len_set

# 複数レベルのループ　行列（リストを要素とするリスト）を平坦化して全ての要素を1つのリストに含める
matrix = [[1,2,3], [4,5,6], [7,8,9]]
## 式の実行順序は左から右
flat = [x for row in matrix for x in row]
print flat

# 深さ2の入力リストをコピーする倍。2次元行列の各要素を自乗
squared = [[x**2 for x in row] for row in matrix]
print squared

my_lists = [
    [[1,2,3],[4,5,6]],
    [[7,8,9],[10,11,12]]
]
flat = [x for sublist1 in my_lists for sublist2 in sublist1
            for x in sublist2]
print flat

flat = []
for sublist1 in my_lists:
    for sublist2 in sublist1:
        flat.extend(sublist2)
print flat

# 複数のif条件
a = [1,2,3,4,5,6,7,8]
b = [x for x in a if x > 4 if x % 2 == 0]
c = [x for x in a if x > 4 and x % 2 == 0]
print b
print c

# 複数レベルのif
matrix = [[1,2,3],[4,5,6],[7,8,9]]
filtered = [[x for x in row if x % 3 == 0]
                for row in matrix if sum(row) > 10]
print filtered

# 複数のif
a = [1,2,3,4,5,6,7,8,9,10]
b = [x for x in a if x > 4 if x % 2 == 0]
c = [x for x in a if x > 4 and x % 2 == 0]
print b
print c

matrix = [[1,2,3],[4,5,6],[7,8,9]]
filtered = [[x for x in row if x%3 == 0] for row in matrix if sum(row) >= 10]
print filtered
