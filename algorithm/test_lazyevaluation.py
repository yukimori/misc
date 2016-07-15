#!/usr/bin/env python
# -*- coding:utf-8 -*-

import time

# 二重再帰のフィボナッチ関数
# 何回も同じ値を求めるため効率が悪い
def fibo(n):
    if n == 0 or n == 1:
        return 1
    # 自分自身を2回呼び出す二重再帰
    print "fibo(" + str(n-1) + ") + fibo(" + str(n-2) + ")"
    return fibo(n-1) + fibo(n-2)

# 末尾再帰のフィボナッチ関数
# 現在のフィボナッチ数をa1、ひとつ前の値をa2に格納
# a1とa2を足し算して新しいフィボナッチ数を計算
def fibo2(n, a1=1, a2=0):
    if n < 1:
        return a1
    print "fibo2(" + str(n-1) + "," + str(a1+a2) + "," + str(a1) + ")"
    return fibo2(n-1, a1+a2, a1)

# 繰り返しのフィボナッチ関数
# 末尾再帰を繰り返しに変換
def fibo3(n):
    a1,a2 = 1,0
    while n > 0:
        a1,a2 = a1 + a2,a1
        n -= 1
    return a1

# たらいまわし関数
def tarai(x, y, z):
    if x <= y:
        return y
    return tarai(tarai(x-1,y,z), tarai(y-1,z,x), tarai(z-1,x,y))

# たらいまわし関数
# クロージャによる遅延評価
def tarai_clojure(x, y, z):
    if x <= y:
        return y
    # 遅延評価したい処理をクロージャにつつんで引数zに渡す
    # x > yのときに引数zを評価（関数呼び出し）する。クロージャ内の処理が実行されてzの値を求めることができる
    zz = z()
    # lambda : 0をzに渡すとz()は返り値は0になる
    # lambda : xを渡すとxに格納されている値が返却される
    # lambda : tarai()を渡すと、関数taraiが実行されてその値が返却される
    return trai(tarai(x-1, y, lambda : zz),
                tarai(y-1, zz, lambda : x),
                lambda : tarai(zz-1, x, lambda : y))

class Stopwatch:
    def start(self):
        self.start = time.time()
        return self.start

    def stop(self):
        self.elapsed = time.time() - self.start
        return self.elapsed

if __name__ == '__main__':
    sw = Stopwatch()
    print fibo(5)
    print fibo2(5)
    print fibo3(5)
    sw.start()
    print tarai(12, 6, 0)
    print " " + str(sw.stop())
