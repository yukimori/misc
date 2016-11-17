# -*- coding: utf-8 -*-

import theano
import theano.tensor as T
import numpy as np

# シンボルを定義
x = T.dmatrix('x')

# シンボルを組み合わせて数式を定義
s = 1 / (1 + T.exp(-x))
# s = T.nnet.sigmoid(x)でもOKらしい

# シンボルを使って関数化
sigmoid = theano.function(inputs=[x], outputs=s)

# 値を代入して計算
print sigmoid([[0, 1], [-1, -2]])

# データを共有変数に読み込む
data = np.array([[1, 2, 3], [4, 5, 6]], dtype=theano.config.floatX)
# borrowをTrueにするとdataの変更がXにも反映される
X = theano.shared(data, name='X', borrow=True)
print type(X)
print X.get_value()

# 線形モデル
W = theano.shared(np.array([[1,2,3],[4,5,6]], dtype=theano.config.floatX),
                      name='W',
                      borrow=True)

b = theano.shared(np.array([1,2], dtype=theano.config.floatX),
                      name="b",
                      borrow=True)


