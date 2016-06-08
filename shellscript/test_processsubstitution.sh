#!/bin/bash

echo "case1 pipeを使っているのでwhile内で作成した変数をwhile外で参照することができない"
a=()
a+=( "a" "b" )

cat <<EOF | while read LINE
test
EOF
do
	a+=( `echo c` )
	echo ${a[@]}
	break
done

echo ${a[@]}

echo "case1-a リダイレクトとプレセス置換の合わせ技"
a=()
a+=( "a" "b" )

while read LINE
do
	a+=( `echo c` )
	echo ${a[@]}
	break
done < <(
cat <<EOF
test
EOF
)
# <( cat ... )` の部分は子プロセス
# 子プロセスのstdoutが `/dev/fd/123` みたいなファイルディスクリプタに置き換わる
echo ${a[@]}

# case2 http://qiita.com/kawaz/items/6fd4cd86ca98af644a05
# case1と同じ事象
# findで見つけたファイル名をfilesという配列変数に詰め込みたい
# pipeで繋げることでwhileがサブシェルで実行される
# while内でfilesを設定しても子プロセスが終了（whileが終了）した時点でbashプロセス上に設定された
# files変数の中身も消え去る
files=()
find -type f | while read -r f; do
	files+=("$f")
done
echo "${files[@]}" # 確かにfilesに値を入れた筈なのに空が出力される？？

# case2-a process substitutionを用いる
# findで見つけたファイル名をfilesという配列変数に詰め込みたい
files=()
while read -r f; do
	files+=("$f")
done < <(find -type f)
echo "${files[@]}" # 期待通りファイル名の一覧が出力される！
