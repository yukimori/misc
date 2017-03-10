# -*- coding:utf-8 -*-
"""
ref:
http://aidiary.hatenablog.com/entry/20150518/1431954329
"""

import theano
import theano.tensor as T

x = T.dscalar('x')

# 微分される数式のシンボル
y = x ** 2

# yをxに関して微分
# cost:微分される数式のシンボル
# wrt:微分する変数のシンボル
# T.grad:微分の数式のシンボルを返却
gy = T.grad(cost=y, wrt=x)

# 微分係数を求める関数を定義
# function:シンボルから関数化する
f = theano.function(inputs=[x], outputs=gy)
# theano.pp:数式を表示
print(theano.pp(f.maker.fgraph.outputs[0]))

print(f(2))
print(f(3))
print(f(4))

y = T.exp(x)
gy = T.grad(cost=y, wrt=x)
f = theano.function(inputs=[x], outputs=gy)
print(theano.pp(f.maker.fgraph.outputs[0]))

print(f(2))
print(f(3))
print(f(4))

# 微分される数式のシンボルを定義
y = (x - 4) * (x ** 2 + 6)

# yをxに関して微分
gy = T.grad(cost=y, wrt=x)

# 微分係数を求める関数を定義
f = theano.function(inputs=[x], outputs=gy)
print(theano.pp(f.maker.fgraph.outputs[0]))

# 具体的なxを与えて微分係数を求める
print(f(0))
print(f(1))
print(f(2))
