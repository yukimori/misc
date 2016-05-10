#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
from sklearn.datasets import make_classification

# サンプルデータの作成
print "n_samples:データ個数"
print "n_features:特徴数（特徴量の次元数）"
print "n_informative:正規分布から作成される特徴量の次元数"
print "n_redundant:n_informativeの線形和で表される特徴量の次元数"
print "n_classes:クラス数"
print "n_clusters_per_class:クラスないのクラスタの数（分布数）"
data = make_classification(n_samples=1000, n_features=20, n_informative=5,
                           n_redundant=2, n_classes=2, n_clusters_per_class=10)

x = data[0]
y = data[1]
#print data
print "X shape {0}".format(x.shape)
print "Y shape {0}".format(y.shape)
