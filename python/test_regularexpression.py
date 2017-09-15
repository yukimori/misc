# -*- coding:utf-8 -*-

import re

def examin_regularexppression():
    pattern = r"ca"
    text = "caabsacasca"
    repatter = re.compile(pattern)
    matchOB = repatter.match(text)
    if matchOB:
        # group() 正規表現にマッチした文字列を返却
        print("{0}".format(matchOB.group()))

    html = u"""
    <h3>ここがほしい</h3>
    <h3>ここもほしい</h3>
    ここはいらない
    """
    pattern = r'<h3>(.*)</h3>'
    matches = re.finditer(pattern, html)
    for match in matches:
        print("{0}".format(match.groups()[0]))

    html = u"""
    <a href="http://www.google.co.jp">Google</a>
    <h3>ここがほしい</h3>
    <h3>ここもほしい</h3>
    ここはいらない
    """

    pattern = r'<a href="(.*)">(.*)</a>'
    matches = re.finditer(pattern, html)
    for match in matches:
        groups = match.groups()
        print("{0}".format(groups[0]))

if __name__ == '__main__':
    examin_regularexppression()
