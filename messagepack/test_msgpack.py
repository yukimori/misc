#!/usr/bin/env python
# -*- coding: utf-8 -*-

import msgpack

"""
http://komaken.me/blog/2014/04/23/%E5%B0%8F%E3%83%8D%E3%82%BF%E3%83%90%E3%82%A4%E3%83%8A%E3%83%AA%E3%82%92%E6%96%87%E5%AD%97%E5%88%97%E3%81%A8%E3%81%97%E3%81%A6%E5%87%BA%E5%8A%9B%E3%81%99%E3%82%8Breprpython/
"""

# 1オブジェクトをシリアライズする
packed = msgpack.packb([1,2,3,u'テスト',"test","apple"])

# 変換後のバイト長表示
print len(packed)
# バイナリを文字列として表示
# 文字として表示できるものは変換　それ以外は16進数表記で出力
print repr(packed)

# デシリアライズ
ret = msgpack.unpackb(packed, encoding='utf-8')

print ret
for elem in ret:
    print elem

