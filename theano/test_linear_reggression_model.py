# -*- coding: utf-8 -*-

import theano
import theano.tensor as T
import numpy as np

# 線形モデル
W = theano.shared(np.array([[1,2,3],[4,5,6]], dtype=theano.config.floatX),
                      name='W',
                      borrow=True)

b = theano.shared(np.array([1,2], dtype=theano.config.floatX),
                      name="b",
                      borrow=True)

# 共有変数の値を取得
print W.get_value()
print b.get_value()

# シンボルの作成
x = T.vector('x')

# シンボルと共有変数を組み立てて数式を定義
y = T.dot(W, x) + b
print type(y)

# 関数を定義
f = theano.function([x], y)

# 関数の使用
print f([1, 1, 1])
