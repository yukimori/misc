#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
inspectはpythonのcodereadingに役立つ
"""

import inspect
import numpy as np
import os

# tile()のソースコードが表示される
# printで表示すると改行された形式で表示される
print inspect.getsource(np.tile)
print inspect.getsource(np.repeat)

# numpyモジュール内部で定義されたオブジェクト一覧を出力
print inspect.getmembers(np)
# クラス・オブジェクトに絞って表示
print inspect.getmembers(np, inspect.isclass)

# インストール済みモジュールのソースファイルのローカル環境内格納先パスを表示
print inspect.getfile(os)


