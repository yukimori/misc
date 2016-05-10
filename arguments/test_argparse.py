# -*- coding:utf-8 -*-

from __future__ import print_function
import argparse

p = argparse.ArgumentParser()
# p.add_argument("foo") # 位置引数fooを定義
# args = p.parse_args() # デフォルトでsys.argvを解析
# print(args.foo)

p.add_argument("-s", "--soge", help="test option")
args = p.parse_args()
print(args.soge)
