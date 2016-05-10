#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import division
import sys
import os.path

DIV_FILE_TEMPLATE = ".frac.{0}"

class Dataset(object):
    
    def generate_3classification(self, num_incluster=50, save_file="3classification.dat"):
        import numpy as np
        import matplotlib.pylab as plt
        # 傾向の違う3つのデータ集合を作成
        # 正規分布で乱数を作成しx,y座標値とする。1つの集合にデータは50
        n0 = np.random.normal(loc=0.0, scale=0.5, size=(num_incluster,2))
        n1 = np.random.normal(loc=-2.0, scale=0.5, size=(num_incluster,2))
        n2 = np.random.normal(loc=2.0, scale=0.5, size=(num_incluster,2))

        # add label(cluster_num)
        label = np.ones((num_incluster,1), dtype=np.int)
        n0 = np.hstack((n0,label*0))
        n1 = np.hstack((n1,label))
        n2 = np.hstack((n2,label*2))

        # データの結合
        data = np.vstack((n0,n1,n2))
        np.random.shuffle(data)

        np.savetxt(save_file, data, delimiter=",")
        return data
    
    def generate_testdata_with_name(self, linenum, filename):
        #import os.path
        # if(os.path.isfile(filename)):
        #     return 
        with open(filename, "w") as f:
            import csv
            from faker import Factory
            csv_writer = csv.writer(f)
            fake = Factory.create()
            for i in range(linenum):
                l = [fake.md5(), fake.random_number(10)]
                l.extend(fake.words(10))
                csv_writer.writerow(l)
        
    
    # サイズに基づくファイル分割
    def bin_div(self, f, size=1024*1024):
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

    def bin_cat(self, f, num):
        out = open(f + '.out', 'wb')
        for i in range(num):
            frac = open(f + '.frac' + str(i), 'rb')
            out.write(frac.read())
            frac.close()
        out.close()

    # 指定した分割数に分割する
    # なるべき均等の行数で分割
    def line_div_av(self, f, div_num):
        num_lines = sum(1 for line in open(f))
        #print num_lines
        #なるべく均等に分割できるように分割する行数を決定
        div_nums_lines = [(num_lines + i) // div_num for i in range(div_num) ]

        frac_files = []
        with open(f, "r") as file:
            for i in range(len(div_nums_lines)):
                #print os.path.dirname(f)
                #print os.path.basename(f) + DIV_FILE_TEMPLATE.format(i)
                with open(f + DIV_FILE_TEMPLATE.format(i), "w") as frac_file:
                    for j in range(div_nums_lines[i]):
                        line = file.readline()
                        if(not line):
                            break
                        frac_file.write(line)
                    frac_files.append(f + DIV_FILE_TEMPLATE.format(i))
        return frac_files
