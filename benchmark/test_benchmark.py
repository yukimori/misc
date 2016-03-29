#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import division
import sys
import os.path

DIV_FILE_TEMPLATE = ".frac.{0}"

class Dataset(object):
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

class ClassifierLogic:
    def sample_train(self, datafile):
        with open(datafile) as f:
            f.read()
        
    def a9a_train(self,datafile):
        #print datafile
        print "a9a_train not implemented yet."

    def iris_train(self, datafile):
        print "iris_train not implemented yet."

class Processor(object):
    def say(self,greeting):
        import time
        for i in range(5):
            print "{0}:{1}".format((i+1),greeting)
            time.sleep(1)

            
    def execute(self, num, target, datafiles):
        import random
        from multiprocessing import Process, Array

        processes = []
        for i,datafile in enumerate(datafiles):
            processes.append(Process(target=target, args=(datafile,)))
        for process in processes:
            process.start()
        for process in processes:
            process.join()

class Benchmark(object):
    def add_time_decorator(self, logic_obj, logic_func_name):
        def time_decorator(*args):
            #print args
            import time
            start_time = time.time()
            #logic_func(*args)
            logic_func = getattr(logic_obj, logic_func_name)
            logic_func(*args)
            end_time = time.time()
            import os
            print "{3}:start:{0} end:{1} elapsed:{2}".format(start_time,end_time,(end_time-start_time),os.getpid())
        return time_decorator
        
    
    def bench_classifier(self, filepath, parallel):
        import time
        print "start classifier benchmark"
        dataset = Dataset()
        frac_files = dataset.line_div_av(filepath, parallel) # [TODO]who should operate file
        print frac_files
        import random
        logic = self.add_time_decorator(ClassifierLogic(), "sample_train")
        processor = Processor()
        start_time = time.time()
        processor.execute(parallel, logic, datafiles=frac_files)
        end_time = time.time()
        print "start:{0} end:{1} elapsed:{2}".format(start_time,end_time,(end_time-start_time))

if __name__=="__main__":
    filepath = sys.argv[1]
    parallel = int(sys.argv[2])
    dataset = Dataset()
    dataset.generate_testdata_with_name(10000,filepath)
    Benchmark().bench_classifier(filepath, parallel)
