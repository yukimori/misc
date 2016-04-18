from pyparsing import CaselessKeyword, MatchFirst, Word, alphas, alphanums, Forward, Optional, oneOf, ZeroOrMore, Regex

"""
http://qiita.com/knoguchi/items/ee949989d0a9f04bee6f
"""

# 1. reserved keyword
# 予約語の登録
# CONST = CaselessKeyword('CONST')
# VAR = CaselessKeyword('VAR') と書く代わりに以下のようにする
(CONST, VAR, PROCEDURE, CALL, BEGIN, END, IF, THEN, WHILE, DO, ODD) = map(CaselessKeyword,
"CONST, VAR, PROCEDURE, CALL, BEGIN, END, IF, THEN, WHILE, DO, ODD".replace(",", "").split())
keyword = MatchFirst((CONST, VAR, PROCEDURE, CALL, BEGIN, END, IF, THEN, WHILE, DO, ODD))

# 2. identifier
ident = ~keyword + Word(alphas, alphanums + "_")

# 3. expression
number = Regex(r"\d+(\.\d*)?([eE][+-]?\d+)?")
term = Forward()
factor = Forward()
expression = Optional(oneOf("+ -")) + term + ZeroOrMore(oneOf("+ -") + term)
term << (factor + ZeroOrMore(oneOf("* /") + factor))
factor << (ident | number | "(" + expression + ")")

if __name__ == '__main__':
    import sys
    with open(sys.argv[1], 'r') as fp:
        txt = fp.read()
        print program.parseString(txt)
