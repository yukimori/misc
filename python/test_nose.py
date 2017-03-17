# coding:utf-8

"""
ref:
http://d.hatena.ne.jp/kuma8/20110323/1300886960

usage:
nosetests test_nose.py
"""

def add(x, y):
    return x + y

def sub(x, y):
    return x -y

from nose.tools import ok_, eq_, with_setup

def debug_write(message):
    debug_file = open('test_nose_debug.log', 'a')
    debug_file.write(message)
    debug_file.close()


def setup():
    debug_write("module setup\n")


def teardown():
    debug_write("module teardown\n")


def b_setup():
    debug_write("func b setup\n")


def b_teardown():
    debug_write("func b teardown\n")


# def a_test():
#     """ テストaの呼び出し確認  """
#     debug_write(test_nose.__str__() + "\n")
#     ok_(True)


# def b_test():
#     """ テストbの呼び出し確認 """
#     debug_write(test_nose.__str__() + "\n")
#     ok_(True)


def add_test():
    eq_(add(1, 2), 3)


def sub_test():
    """ sub test """
    eq_(sub(1, 1), 0)


def if_test():
    ok_(1 == 1)
   
