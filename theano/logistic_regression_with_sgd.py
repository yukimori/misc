# -*- coding: utf-8 -*-

from __future__ import print_function
import theano
import theano.tensor as T
import numpy as np
import matplotlib.pyplot as plt

import six

"""
2クラスロジスティック回帰をtheanoで実装
with SGD/確率的勾配降下法
"""

def plot_data(X, y):
    # positive,negativeクラスのデータのインデックス
    positive = [i for i in range(len(y)) if y[i] == 1]
    negative = [i for i in range(len(y)) if y[i] == 0]

    plt.scatter(X[positive, 0], X[positive, 1], c='red', marker='o', label="positive")
    plt.scatter(X[negative, 0], X[negative, 1], c='blue', marker='o', label="negative")

if __name__ == "__main__":
    # 訓練データをロード
    data = np.genfromtxt("ex2data1.txt", delimiter=",")
    data_x = data[:, (0, 1)]
    data_y = data[:, 2]

    # 訓練データ数
    m = len(data_y)

    # 訓練データをプロット
    plt.figure(1)
    plot_data(data_x, data_y)

    # 訓練データの1列目に1を追加
    # バイアス項をパラメータthetaに含めるため
    data_x = np.hstack((np.ones((m, 1)), data_x))

    # Xは訓練データのシンボル
    X = theano.shared(np.asarray(data_x,
                                 dtype=theano.config.floatX), borrow=True)
    # yは訓練データの正解ラベルのシンボル
    y = theano.shared(np.asarray(data_y,
                                 dtype=theano.config.floatX), borrow=True)

    # パラメータを共有変数にし、0で初期化
    # 訓練データに1を加えたのでバイアスもthetaに含める
    theta = theano.shared(np.zeros(3, dtype=theano.config.floatX),
                          name='theta', borrow=True)
    print("theta:{0}".format(theta.get_value()))
