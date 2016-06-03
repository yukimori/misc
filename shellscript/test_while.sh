#!/bin/sh

# whileのプロセス関係をテストする

OS=FreeBSD

# pipeが挟まることで別プロセスになり
# 変数が共有されない
# 501 66784 25393   0  5:47PM ttys015    0:00.00 bash test_while.sh
# 501 66786 66784   0  5:47PM ttys015    0:00.00 bash test_while.sh
# 501 66793 66786   0  5:47PM ttys015    0:00.00 sleep 100
echo |
while :
do
	OS=Linux
#	sleep 100
	break
done
echo ${OS}

# case1 whileは別プロセスであるためカウントした値iをwhile終了後に読み取ることはできない
i=0
grep AAA "test_while.dat" |
while read b
do
	i=$((i+1))
	echo "$i   $b"
done

# iを読み取ることができない
echo "total lines : $i"

# case1-A ファイルに記述する
tmp=./$$
i=0
grep AA "test_while.dat"         |
	while read b
	do
		i=$((i+1))
		echo $i > $tmp-count
		echo "$i        $b"
	done
echo "total lines : $(cat $tmp-count)"
rm $tmp-*

# case1-b awkで処理する
awk 'BEGIN {i=0;}
/AAA/ { i+=1;
print i" "$0}
END {print "total lines:"i}' "test_while.dat"

echo "case1-c pipeをつかない。ヒアドキュメントもリダイレクトの一種"
while read b
do
	i=$((i+1))
	echo "$i    $b"
done <<EOF
$(cat ./test_while.dat | grep "AAA")
EOF

echo "total lines : $i"
