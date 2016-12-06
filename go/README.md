# package
http://qiita.com/suin/items/f4ad02e4123c8a3c75eb
別パッケージに切り出す場合は
foo/foo.go
などとディレクトリを分ける
mainパッケージでは
import "./foo"
でimportできる

# scope/スコープ
変数，関数ともに大文字で始めるとpackage外から参照できる
小文字から始めるとpackage内でしか参照できない