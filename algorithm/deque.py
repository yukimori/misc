#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
双方向リストによるdequeの実装
queueの先頭、最後尾の両方でデータの追加、削除ができる
"""

class Deque:
    # セルの定義
    class Cell2:
        def __init__(self, x, y = None, z = None):
            self.data = x
            self.next = y
            self.pref = z

    # 初期化
    def __init__(self):
        head = Deque.Cell2(None) # ヘッダ
        # 循環リストにする
        head.next = head
        head.prev = head
        self.size = 0
        self.head = head

    # 最後尾に追加
    def push_back(self, x):
        h = self.head
        p = h.prev
        # 追加するデータxのnextは先頭headなのでhを渡す
        q = Deque.Cell2(x, h, p)
        h.prev = q
        p.next = q
        self.size += 1

    # 先頭に追加
    def push_front(self, x):
        h = self.head
        q = h.next
        # 追加するデータのprevはheadを参照する
        p = Deque.Cell2(x, q, h)
        h.next = p
        q.prev = p
        self.size += 1
        
    # 最後尾のデータを取り出す
    def pop_back(self):
        if self.size == 0:
            raise IndexError
        h = self.head
        q = h.prev
        p = q.prev
        p.next = h
        h.prev = p
        self.size -= 1
        return q.data

    # 先頭のデータを取り出す
    def pop_front(self):
        if self.size == 0:
            raise IndexError
        h = self.head
        q = h.next
        p = q.next
        p.prev = h
        h.next = p
        self.size -= 1
        return q.data

    # 最後尾のデータを返す
    def peek_back(self):
        if self.size == 0:
            raise IndexError
        return self.head.prev.data

    # 先頭のデータを返す
    def peek_front(self):
        if self.size == 0:
            raise IndexError
        return self.head.next.data

    # 空チェック
    def isEmpty(self):
        return self.size == 0

    # 表示
    def __str__(self):
        if self.size == 0:
            return 'Deque()'
        buff = 'Deque('
        n = self.size
        cp = self.head.next
        while n > 1:
            buff += '%s, ' % cp.data
            cp = cp.next
            n -= 1
        buff += '%s)' % cp.data
        return buff

# テスト
if __name__ == '__main__':
    q = Deque()
    print q.isEmpty()
    for x in range(5):
        q.push_front(x)
        q.push_back(x * 10)
        print q
    print q.peek_front()
    print q.peek_back()
    
