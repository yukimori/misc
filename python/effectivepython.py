#!/usr/bin/env python
# -*- coding:utf-8 -*-

from __future__ import print_function

# 16
def index_words_iter(text):
    if text:
        yield 0
    for index, letter in enumerate(text):
        if letter == ' ':
            yield index + 1

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
