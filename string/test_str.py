#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
ref:
https://gist.github.com/devlights/4561968
以下は引用:
ターミナル出力はうまくいくが
リダイレクトしてファイル出力するとエラーが発生する

pythonのunicode型は文字コードではないため
str型は文字コードに即したバイト列

unicode型.decode() ==> str型
str型.encode() ==> unicode型

unicode型は文字コードではないのでそのまま出力することはできない
decodeを行ってから出力すること
出力先がターミナルの場合、pythonは出力先のエンコードを
エンコーディングを認識してdecodeしてから出力する
（ファイル場合は何もしないのでunicode型を出力してエラーになる）

"""

if __name__ == '__main__':

    import codecs
    import sys
    import types

    s1 = '日本語文字列(s1)'
    s2 = u'日本語文字列(s2)'

    print s1
    print s2

    print type(s1)
    print type(s2)

    print s1.decode('utf-8')
    print s2.encode('utf-8')

    print s2.encode('utf-8').decode('utf-8')
