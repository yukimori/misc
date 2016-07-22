#!/usr/bin/env python
#-*- coding:utf-8 -*-

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
