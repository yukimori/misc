# coding:utf-8

"""
tensorflowはじめましたを参照
"""

import tensorflow as tf

# 処理がデータフローグラフとして構築される
# ノードをオペレーションと呼ぶ
const1 = tf.constant(2)
const2 = tf.constant(3)
# add_opもおpレーション（ノード）
add_op = tf.add(const1, const2)
mul_op = tf.mul(add_op, const2)

print("add_op", add_op)

with tf.Session() as sess:
#    result = sess.run(add_op)
    result, result2 = sess.run([mul_op, add_op])
    print("result:", result)
    print("result2:", result2)
