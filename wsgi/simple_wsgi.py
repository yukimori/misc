#!/usr/bin/env python
#-*- coding:utf-8 -*-

"""
wsgiアプリケーションの仕様は
・2つの引数を持った呼び出し可能なオブジェクト
・第2引数として渡されたオブジェクトにHTTPステータスコードと[(レスポンスヘッダ, 値)]という値を渡して呼び出す
・返り値にiterable objectを返す
・返り値のiterableをiterateすると，文字列を返す
ref:
http://d.hatena.ne.jp/ux00ff/20110919/1316415417
"""

def application(env, res):
    res("200 OK", [("Content-type", "text/plain")])
    return "Hello wsgi application\n"

from wsgiref import simple_server

if __name__ == "__main__":
    sv = simple_server.make_server("", 8080, application)
    sv.serve_forever()









