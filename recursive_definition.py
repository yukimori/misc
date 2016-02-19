#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
ref:
http://www.geocities.jp/m_hiroi/light/pyalgo01.html
"""

"""
累乗を単純な繰り返しで実装
"""
def pow(x, n):
    value = 1
    while n > 0:
        value *= x
        n -= 1
    return value

"""
累乗の計算
再帰を使った場合
"""
def pow1(x, n):
    if n == 0:
        return 1
    value = pow1(x, n/2)
    value *= value
    if n%2 == 1:
        value *= x
    return value

print pow(2,3)
print pow1(2,3)

"""
再帰呼び出しを使った基本的なフィボナッチ関数
自分自身を2回呼び出している。二重再帰という
二重再帰は同じ値を何回も求めているので効率が悪い
  fibo(5) ┬ fibo(4) ┬ fibo(3) ┬ fibo(2) ┬ fibo(1)  
          │         │         │         │
          │         │         │         └ fibo(0)
          │         │         └ fibo(1)
          │         └ fibo(2) ┬ fibo(1)
          │                    │
          │                    └ fibo(0)
          │
          └ fibo(3) ┬ fibo(2) ┬ fibo(1)
                     │         │
                     │         └ fibo(0)
                     └ fibo(1)
"""
def fibo_basic(n):
    if n==0 or n==1:
        return 1
    return fibo(n-1) + fibo(n-2)

"""
二重再帰を末尾再帰へ変換したもの
無駄な計算を行っていないので値を高速に求めることが可能
末尾最適化を行う処理系ではプログラムを高速に実行することができる
pythonは末尾再帰最適化はサポートしていない
fibo(5)
  fibo(4, 1, 1)
    fibo(3, 2, 1)
      fibo(2, 3, 2)
        fibo(1, 5, 3)
          fibo(0, 8, 5)
          => a1 の値 8 を返す
        => 8
      => 8
    => 8
  => 8
=> 8
"""
def fibo(n, a1=1, a2=0):
    if n < 1:
        return a1
    return fibo(n-1, a1+a2, a1)

"""
末尾再帰を繰り返しに変換
"""
def fibo_repeat(n):
    a1,a2 = 1, 0
    while n > 0:
        a1, a2 = a1 + a2, a1
        n -= 1
    return a1

print fibo_basic(5)
print fibo(5)
print fibo_repeat(5)
