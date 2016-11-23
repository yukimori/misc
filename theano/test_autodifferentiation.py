# -*- coding: utf-8 -*-

from __future__ import print_function
import theano
import theano.tensor as T
import numpy as np
import matplotlib.pyplot as plt

# y = x^2の自動微分
# コスト関数と微分する変数を指定

x = T.dscalar('x')

# 微分される数式のシンボルを定義
y = x ** 2

# yをxに関して微分
# y' = 2x
# gyは微分の式のシンボル
gy = T.grad(cost=y, wrt=x)

# シンボルを使って微分係数を求める関数を定義
f = theano.function(inputs=[x], outputs=gy)
# theano.pp()で微分の数式を表示
print(theano.pp(f.maker.fgraph.outputs[0]))

# 具体的なxを与えて微分係数を求める
print(f(2))
print(f(3))
print(f(4))

# y = e^{x]
x = T.dscalar('x')

# 微分される数式のシンボルを定義
y = T.exp(x)

# yをxに関して微分
gy2 = T.grad(cost=y, wrt=x)

# 微分係数を求める関数を定義
f = theano.function(inputs=[x], outputs=gy2)
print(theano.pp(f.maker.fgraph.outputs[0]))

print(f(2))
print(f(3))
print(f(4))

# y = sin(x)を微分

# 微分される数式のシンボルを定義
y = T.sin(x)

# yをxに関して微分
gy = T.grad(cost=y, wrt=x)

# 微分係数を求める関数を定義
f = theano.function(inputs=[x], outputs=gy)
print(theano.pp(f.maker.fgraph.outputs[0]))

print(f(0))
print(f(np.pi / 2))
print(f(np.pi))


# y = (x-4)(x^2+6)を微分
y = (x - 4) * (x ** 2 + 6)
gy = T.grad(cost=y, wrt=x)
# 微分係数を求める関数を定義
f = theano.function(inputs=[x], outputs=gy)
print(theano.pp(f.maker.fgraph.outputs[0]))

print(f(0))
print(f(1))
print(f(2))

# y = (sqrt(x) + 1)^3
y = (T.sqrt(x) + 1) ** 3

# yをxに関して微分
gy = T.grad(cost=y, wrt=x)
f = theano.function(inputs=[x], outputs=gy)
print(theano.pp(f.maker.fgraph.outputs[0]))

print(f(2))
print(f(3))

# 偏微分の例を試してみる
# z = (x + 2 + y) ** 2

x = T.dscalar('x')
y = T.dscalar('y')

# 微分される数式のシンボルを定義
z = (x + 2 * y) ** 2
# zをxに関して微分
gx = T.grad(cost=z, wrt=x)
# zをyに関して微分
gy = T.grad(cost=z, wrt=y)

# 微分係数を求める関数の定義
fgx = theano.function(inputs=[x, y], outputs=gx)
fgy = theano.function(inputs=[x, y], outputs=gy)
print(theano.pp(fgx.maker.fgraph.outputs[0]))
print(theano.pp(fgy.maker.fgraph.outputs[0]))

print(fgx(1, 2))
print(fgx(2, 2))
print(fgy(1, 2))
print(fgy(2, 2))







    






