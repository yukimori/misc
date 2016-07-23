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

def log(message):
    print message

def dump(obj):
    if type(obj) == dict:
        for k in obj:
            log("%30s | %s" %(k, obj[k]))
    else:
        log(obj)

def application(env, res):
    res("200 OK", [("Content-type", "text/plain")])
    dump("env")
    dump(env)
    dump("res")
    dump(res)
    return ["first\n","second\n","third\n"]

from wsgiref import simple_server

if __name__ == "__main__":
    sv = simple_server.make_server("", 8080, application)
    sv.serve_forever()









