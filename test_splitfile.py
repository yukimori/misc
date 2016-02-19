#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import division
import sys
import os.path

DIV_FILE_TEMPLATE = ".frac.{0}"

def bin_div(f, size=1024*1024):
    l = os.path.getsize(f)
    div_num = (l+size -1) / size
    last = (size*div_num) - 1

    b = open(f, "rb")
    for i in range(div_num):
        read_size = last if i==div_num-1 else size
        data = b.read(read.size)
        out = open(f + '.frac' + str(i), 'wb')
        out.write(data)
        out.close()
    b.close()

def bin_cat(f, num):
    out = open(f + '.out', 'wb')
    for i in range(num):
        frac = open(f + '.frac' + str(i), 'rb')
        out.write(frac.read())
        frac.close()
    out.close()

# 行数に基づくファイルの分割
def line_div_av(f, div_num):
    num_lines = sum(1 for line in open(f))
    print num_lines
    div_nums_lines = [(num_lines + i) // div_num for i in range(div_num) ] #なるべく均等に分割

    with open(f, "r") as file:
        for i in range(len(div_nums_lines)):
            #        print os.path.dirname(f)
            #        print os.path.basename(f) + DIV_FILE_TEMPLATE.format(i)
            with open(f + DIV_FILE_TEMPLATE.format(i), "w") as frac_file:
                for j in range(div_nums_lines[i]):
                    line = file.readline()
                    if(not line):
                        break
                    frac_file.write(line)

def main():
    filepath = sys.argv[1]
    div_num = int(sys.argv[2])
    line_div_av(filepath, div_num)

if __name__=="__main__":
    main()

