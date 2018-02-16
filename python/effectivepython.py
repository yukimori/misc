#!/usr/bin/env python
# -*- coding:utf-8 -*-

from __future__ import print_function

def normalize(numbers):
    total = sum(numbers)
    result = []
    for value in numbers:
        percent = 100 * value / total
        result.append(percent)
    return result


def read_visits(data):
    for visit in data:
        yield visit


# 14
def divide(a, b):
    try:
        return a / b
    except ZeroDivisionError as e:
        raise ValueError('Invalid inputs')


# 15
def sort_priority(values, group):
    # クロージャの仕組みによりhelperクロージャがsort_priorityの引数groupにアクセスできる
    def helper(x):
        # タプルの比較に特別な規則をもつ
        # 最初に添字0の要素、添字1の要素...と比較する
        if x in group:
            return (0, x)
        return (1, x)
    values.sort(key=helper)


# 優先度の高い要素があったかどうか返却する
def sort_priority2(numbers, group):
    found = [False]  # リストにすることで変更可能にしている

    def helper(x):
        if x in group:
            # found = True  # helperクロージャ内でfound変数が定義されてしまう
            found[0] = True  # 外部スコープのfoundにアクセスする
            return (0, x)
        return (1, x)
    numbers.sort(key=helper)
    return found[0]


# 16
## 単語位置の添え字を見つけ出す
def index_words(text):
    result = []
    if text:
        result.append(0)
    for index, letter in enumerate(text):
        if letter == ' ':
            result.append(index + 1)  # 新たな結果が見つかるたびにappendメソッドを呼び出す
    return result


## ジェネレータ(yield式を使う関数)を使う
def index_words_iter(text):
    if text:
        yield 0
    for index, letter in enumerate(text):
        if letter == ' ':
            yield index + 1


def index_file(handle):
    offset = 0
    for line in handle:
        if line:
            yield offset
        for letter in line:
            offset += 1
            yield offset

if __name__ == '__main__':
    visits = [15, 35, 80]
    print("visits {0}".format(visits))
    percentages = normalize(visits)
    print("normalize {0}".format(percentages))
    it = read_visits(visits)
    print(it)
    print(it)
#    print("use generater(not work) {0}".format(normalize()))

    address = 'Four score and seven years ago...'
    print("address: {0}".format(address))
    result = list(index_words_iter(address))
    print("index_words_iter of address: {0}".format(result))

    print('#14')
    x, y = 5.0, 2.0
    a, b = 5.0, 0.0
    try:
        result = divide(x, y)
    except ValueError:
        print('Invalid inputs')
    else:
        print('Result is %.1f' % result)
    try:
        result = divide(a, b)
    except ValueError:
        print('Invalid inputs')
    else:
        print('Result is %.1f' % result)

    print('#15 スコープ処理バグ')
    numbers = [8, 3, 1, 2, 5, 4, 7, 6]
    group = {5, 7, 2, 3}
    sort_priority(numbers, group)
    print(numbers)

    print("#16 ジェネレータを返却する")
    address = 'Four score and serven years ago...'
    result = index_words(address)
    print(result)
    print("result[:3] {0}".format(result[:3]))

    result = list(index_words_iter(address))
    print("ジェネレータを使う {0}".format(result))
