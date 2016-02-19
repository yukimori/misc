#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
ref:
http://qiita.com/Tsutomu-KKE@github/items/a172137e80593a3005b3
"""

from pulp import *
r = [0, 1, 3] # 水準
for N in [20, 40, 60, 120]: # 最低数
    m = LpProblem()
    # casesに購入費用が5万円以下の総ケースが入っているものとする
    v = [LpVariable('v%d'%i, cat=LpBinary) for i in range(len(cases))]
    m += lpSum(v)
    for j in range(len(cases[0])):
        for k in r:
            m += lpSum(v[i] for i in range(len(cases)) if cases[i][j] == k) >= N
    m.solve()
    print(N, LpStatus[m.status], value(m.objective)) # 最低数、ステータス、ケース数
