# ref
http://aidiary.hatenablog.com/entry/20150518/1431954329

# y = x**2の計算
http://aidiary.hatenablog.com/entry/20150509/1431137590

シンボル(TensorVAriable)による数式定義を行う必要があるため、
数式としては簡単でもプログラムは結構複雑になる

test_theano01.pyにて実装

# テンソル/Tensor
スカラ、ベクトル、行列などを抽象化した概念

# theano.function
シンボルを組み立てた数式はそのままでは使えない
theano.functionで関数化する必要がある

# 共有変数/shared variable
プログラム実行中に値を保持しなければいけないようなデータは、
共有変数に格納する
具体的なデータを初期値として与える必要がある
共有変数に格納するとGPUメモリに自動的に格納される
GPUにのせるデータ型はtheadno.config.floatX型にする必要がある

# 自動微分
勾配降下法ではパラメータの更新式にコスト関数（誤差関数）Eの微分が必要
自動微分ではコスト関数とどの変数を微分するか指定すると自動的に微分を計算する

test_theano02.pyに実装
ref:http://aidiary.hatenablog.com/entry/20150518/1431954329

# theano install
el capitainのデフォルトのpythonのバージョンでは
theanoをインストールするために
バージョンの整合性をとるためにsixをアンインストールしようとして、
失敗してエラーとなる
2.7.11ではインストールできる。ただしfortranコンパイラが必要であるため、
homebrewでgccをインストールする。
これが非常に時間がかかるため注意する

# logistic_regression.py
ref:
 http://aidiary.hatenablog.com/entry/20150519/1432038633
2クラスロジスティック回帰の実装
ロジスティック回帰のコスト関数として交差エントロピー誤差関数を使う

回帰直線を描画している
100回では表示している領域に回帰直線を描画できるところまで収束しなかった
30000回では精度は悪いものの領域内に描画できた
