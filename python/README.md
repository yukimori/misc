# nose
test_nose.pyにてテスト
公式サイトを参考に~/.nosercにて詳細オプションを指定
ref:http://nose.readthedocs.io/en/latest/usage.html

# bytes, str, unicode
ref:
 http://qiita.com/FGtatsuro/items/cf178bc44ce7b068d233
python2では
* str/バイト文字列
  - '...'リテラルで生成されるオブジェクト
  - UTF-8などの符号化方式によって各文字を符号化して得られるバイトを並べたもの
  - 1文字が複数バイトで表現されることも（日本語utf-8は3バイト）
  - 生の8ビット値を含む。インタプリタには文字のシーケンスではなくバイトのシーケンスとして認識
  - str文字列そのものは符号化に使われた符号化方式情報を持たない
  
* unicode/ユニコード文字列
  - u'...'リテラルで生成されるオブジェクト
  - 文字コードUCS-2上で各文字に対応する整数を並べたもの。符号化方式の違いを意識する必要がない
  - Unicodeのコードポインタを並べたもの
  - バイナリ符号化を伴っていない

python3では
- bytes インスタンスは生の8ビット値を含む
- str Unicode文字を含む　バイナリ符号化を伴っていない

Unicode文字をバイナリデータに変換するにはencodeメソッドを使う必要あり
バイナリデータをUnicode文字に変換するにはdecodeメソッドを使う必要あり

プログラムの核心ではUnicode文字型(python2:unicode, python3:str)を使い、
文字の符号化については仮定してはいけない

# リスト内包表記
test_listcomprehension.pyにてリスト内包表記のテストを作成

## ジェネレータ式の生成
メモリ不足を回避するためにリスト内包表記でジェネレータ式を生成する方法をtest_generator.pyでテスト

