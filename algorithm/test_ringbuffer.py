#!/usr/bin/env python
# -*- coding: utf-8 -*-

class RingBuffer:
    def __init__(self, n=16):
        # キューの大きさ
        self.size  = n
        # バッファ（配列）
        self.buffer  = [None] * n
        self.front = 0 # データを取り出す dequeueで使う
        self.rear  = 0 # データを追加 enqueueで使う
        # キューに格納されたデータ数
        self.count = 0

    # データの追加
    def enqueue(self, x):
        # キューにデータが格納できるかチェック
        # 満杯の場合はエラー
        if self.count == self.size:
            raise IndexError
        # データはrearの位置に格納
        self.buffer[self.rear] = x
        self.rear += 1
        # キューを全て使うと位置を最初に戻す（リング）
        if self.rear == self.size:
            self.rear = 0
        self.count += 1

    # データの取り出し
    def dequeue(self):
        # キューにデータがあるかどうかチェック
        if self.count == 0:
            raise IndexError
        data = self.buffer[self.front]
        self.front += 1
        # キューを最後まで取り出すと最初に戻る
        if self.front == self.size:
            self.front = 0
        self.count -= 1
        return data

    # 先頭のデータを求める
    def peek(self):
        if self.count == 0:
            raise IndexError
        return self.buffer[self.front]

    # 空チェック
    def isEmpty(self):
        return self.count == 0

    # 満杯チェック
    def isFull(self):
        return self.count == self.size

    # 表示
    def __str__(self):
        if self.count == 0:
            return 'Queue()'
        buffer = 'Queue('
        n = self.count
        i = self.front
        while n > 1:
            buffer += '%s, ' % self.buffer[i]
            i += 1
            if i == self.size:
                i = 0
            n -= 1
        buffer += '%s)' % self.buffer[i]
        return buffer

# テスト
if __name__ == '__main__':
    r = RingBuffer(8)
    x = 0
    while not r.isFull():
        r.enqueue(x)
        x += 1
        print r
    while not r.isEmpty():
        print r.dequeue()
        print r
