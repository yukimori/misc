#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
http://www.geocities.jp/m_hiroi/light/pyalgo02.html

queueの最後尾にデータの追加
queueの先頭からデータの取り出し
"""

class Queue:
    # セルの定義
    class Cell:
        def __init__(self, x, y = None):
            self.data = x
            self.next = y

    def __init__(self):
        # データ数
        self.size = 0
        # 最後尾のセルの参照
        self.rear = None

    # データの追加
    def enqueue(self, x):
        if self.size == 0:
            self.rear = Queue.Cell(x)
            self.rear.next = self.rear # 循環リスト 自分自身を次のデータとして参照する
        else:
            new_cell = Queue.Cell(x, self.rear.next)
            self.rear.next = new_cell
            self.rear = new_cell # 最後のデータ情報を更新する（参照渡し？）
        print "rear.data:"+str(self.rear.data)+ " rear.next.data:"+str(self.rear.next.data)
        self.size += 1

    # データの取り出し
    def dequeue(self):
        if self.size == 0:
            raise IndexError
        front = self.rear.next
        self.rear.next = front.next
        self.size -= 1
        if self.size == 0:
            self.rear = None
        return front.data

    # キューを回転する
    def rotate(self, n = 1):
        if self.size == 0 or n < 1:
            raise IndexError
        while n > 0:
            self.rear = self.rear.next
            n -= 1

    def isEmpty(self):
        return self.size == 0

    # 先頭のデータを求める
    def peek(self):
        if self.size == 0:
            raise IndexError
        return self.rear.next.data

    # キューの表示
    def __str__(self):
        if self.size == 0:
            return 'Queue()'
        cp = self.rear.next
        n = self.size
        buff = 'Queue('
        while n > 1:
            buff += '%s, ' % cp.data
            cp = cp.next
            n -= 1
        buff += '%s)' % cp.data
        return buff

# 簡単なテスト
if __name__ == '__main__':
    q = Queue()
    print q.isEmpty()
    for x in range(5):
        q.enqueue(x)
    print q
    q.rotate()
    print q.peek()
    q.rotate()
    print q.peek()
    q.rotate()
    print q.peek()
    while not q.isEmpty():
        print q.dequeue(),
        print q
    print q
