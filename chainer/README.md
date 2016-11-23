# test_chainer.py
chainer1.12あたりの書き方の解説

変数はnumpyの配列(float型)で宣言することが多い

chainer.Variable
 chainerで使用する変数クラス

関数yを宣言してy.backward()で微分が計算できるようになる
back-propagationのための勾配はgradで求められる
x.grad

公式リファレンスにはxを多次元配列とする場合にはy.gradを初期化してからx.gradを計算するようにとのこと
初期化しないと勾配の値が格納されている配列に加算されていくため
「勾配計算の前に初期化」