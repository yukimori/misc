#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
import random
import time
from multiprocessing import Process, Array

def say(greeting):
    for i in range(5):
        print "{0}:{1}".format((i+1),greeting)
        time.sleep(1)

def main():
    process_num = int(sys.argv[1])
    processes = []
    for i in range(process_num):
        processes.append(Process(target=say, args=("I am {0}".format(i),)))
    for process in processes:
        process.start()
    for process in processes:
        process.join()

if __name__ == "__main__":
    main()
            
        
