
from __future__ import print_function
import chainer
import numpy as np

# 変数の宣言
x_data = np.array([5], dtype=np.float32)
print("x_data:{0}".format(x_data))

# chainerで使用するための変数としてchainer.Variableを使用
x = chainer.Variable(x_data)
print("x:{0}".format(x))
# xの値はx.dataで確認
print("x.data:{0}".format(x.data))

# xの関数yの宣言
y = x ** 2 - 2 * x + 1
print("y:{0}".format(y))
print("y.data:{0}".format(y.data))

# 微分が計算できるようになる
y.backward()

# back-propergationのための勾配を求める
print("x.grad:{0}".format(x.grad))
print("dy/dx = 2x -2にx(x_data)=5を代入したときの値が上記の8")

# xが多次元配列の場合、勾配計算の前に初期化
print("xが多次元の場合")
x = chainer.Variable(np.array([[1,2,3],[4,5,6]], dtype=np.float32))
y = x**2 - 2*x + 1
y.grad = np.ones((2,3), dtype=np.float32)
y.backward()
print("x.grad")
print(x.grad)

# NNモデル
import chainer.links as L


