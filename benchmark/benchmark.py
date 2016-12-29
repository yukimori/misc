#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import division
import sys
import os.path
from dataset import Dataset
from multiprocessing import Process, Array, Queue

class ClassifierLogic:
    def sample_train(self, datafile):
        with open(datafile) as f:
            f.read()

    def dim2_classifier_train(self, datafile):
        import jubatus
        from jubatus.common import Datum
        import pandas as pd

        host = "127.0.0.1"
        port = 9199
        name = "2dim_classifier"
        client = jubatus.Classifier(host, port, name)
        
        df = pd.read_csv(datafile, names=('x', 'y', 'label'))
        for ix, row in df.iterrows():
            client.train([(str(row['label']), Datum({'x':row['x'], 'y':row['y']}))])
            # print "ix:{0}".format(ix)
        self.query_num = ix+1
        self.query_type = "2dim_classifier_train"

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
        processes = []
        for i,datafile in enumerate(datafiles):
            processes.append(Process(target=target, args=(datafile,)))
        for process in processes:
            process.start()
        for process in processes:
            process.join()

class Benchmark(object):
    def add_time_decorator(self, logic_obj, logic_func_name, queue):
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
            print ""
            num = getattr(logic_obj, "query_num")
            query_type = getattr(logic_obj, "query_type")
            res = {"start":start_time, "end":end_time, "elapsed":(end_time-start_time),
                   "num":num, "query_type":query_type}

            queue.put(res)
        return time_decorator

    def bench_classifier(self, filepath, parallel):
        import time
        print "start classifier benchmark"
        dataset = Dataset()
        # [TODO]which class should operate file
        frac_files = dataset.line_div_av(filepath, parallel)
        print frac_files
        import random
        queue = Queue()
        logic = self.add_time_decorator(ClassifierLogic(), "dim2_classifier_train", queue)
        processor = Processor()
        start_time = time.time()
        processor.execute(parallel, logic, datafiles=frac_files)
        end_time = time.time()
        print "start:{0} end:{1} elapsed:{2}".format(start_time,end_time,(end_time-start_time))
        # for i in range(parallel):
        #     print queue.get()
        return queue

    # 結果を集計して表示/保存する
    def report(self, result, prallel,savefilepath="repot.dat"):
        num = []
        query_type = []
        start = []
        end = []
        for i in xrange(prallel):
            res = result.get()
            query_type.append(res["query_type"])
            num.append(res["num"])
            start.append(res["start"])
            end.append(res["end"])
        print "# query_type:{0}".format()

def parse_args():
    from optparse import OptionParser, OptionValueError
    p = OptionParser()
    p.add_option('-s', '--server_ip', action='store',
                 dest='server_ip', type='string', default='127.0.0.1')
    p.add_option('--server_port', action='store',
                 dest='server_port', type='int', default='9199')
    p.add_option('--name', action='store',
                 dest='name', type='string', default='benchmark')
    p.add_option('-c', '--case', action="store",
                 dest='case', type='string', default='classifier_3clusters_2dim',
                     help="select testcase. (default=classifier_3clusters_2dim.you can select)")
    p.add_option('-p', '--process', action="store",
                 dest='process', type='int', default="1")
    p.add_option('-n','--num', action="store",
                 dest='datanum', type='int', default='10000',
                 help="The number of test data (if test data has cluster it seems per cluster")
    p.add_option('--testdata_path', action="store",
                 dest='testdata_path', type="string", default='data/test_data.dat',
                 help="file path saved testdata")
    return p.parse_args()
            
if __name__=="__main__":
    options, remainder = parse_args()
    dataset = Dataset()
    dataset.generate_3classification(options.datanum,save_file=options.testdata_path)
    bench = Benchmark()
    result = bench.bench_classifier(options.testdata_path, options.process)
    bench.report(result, options.process)
