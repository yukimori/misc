# -*- coding:utf-8 -*-

import numpy as np

def test_generate_sequence(step):
    """
    任意の数列を作成するテストコード
    """

    # rangeでは小数の数列は作成できない
    # seq = range(0.01, 1, step)
    # print(seq)

    print("numpyを使うと小数の数列が作れる")
    seq = np.arange(step, 1, step)
    print(seq)

    print("別のリストに結合する")
    all_list = [0.0]
    all_list.extend(np.arange(step, 1, step))
    print(all_list)
    

if __name__ == '__main__':
    test_generate_sequence(0.05)
