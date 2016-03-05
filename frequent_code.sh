#!/usr/bin/env bash

# ref:
# http://lambdalisue.hatenablog.com/entry/2013/07/06/023040 

title() {
	make_paragraph
	echo "# $1"
}

comment() {
	echo " $1"
}

make_paragraph() {
	echo ""
}

title "対話処理で環境変数に設定する"
if [ -z "${ID}" ]; then
	printf "ID: "
	read ID
fi

if [ -z "${PASSWORD}" ]; then
	comment "stty -echoにより表示抑制？"
	stty -echo
	printf "PASSWORD:"
	read PASSWORD
	stty echo
fi

make_paragraph
echo "ID:${ID}"
echo "PASSWORD:${PASSWORD}"

title "サブコマンド（引数処理）"
start_test() {
	echo "start"
}
function stop_test {
	echo "stop"
}
usage() {
	echo "usage"
	echo $0 start|stop|restart
}
comment "第一引数をサブコマンドとする"
case ${1} in
	start)
		start_test
		;;
	stop)
		stop_test
		;;
	restart)
		start_test && stop_test
		;;
	help|--help|-h)
		comment "複数マッチ(--help,-h）にも対応"
		usage_test
		;;
	version|--version|-v)
		version
		;;
	*)
		echo "[ERROR]Invalid subcommand '${1}'"
		usage
#		exit 1
		;;
esac

title "オプションを複数とる場合はwhileでまわす"
while [ $# -gt 0 ];
do
	case ${1} in
		--debug|-d)
			set -x
			;;
		--host|-h)
			HOST=${2}
			shift
			;;
		--port|-p)
			PORT=${2}
			shift
			;;
		*)
			echo "[ERROR] Invalid option '${1}'"
			usage
#			exit 1
			;;
	esac
	shift
done


title "起動スクリプトのパスを取得"
comment "1行で記述する"
ROOT=$(cd $(dirname $0);pwd) 
echo $ROOT

commnet "分かりやすい書き方で取得"
ROOT=`dirname $0`
ROOT=`cd $ROOT;pwd`
echo $ROOT


title "出力に色をつける"
echo "基本構文 \033[{属性値}m{文字列}\033[m"
red=31
green=32
yello=33
blue=34

function cecho {
	color=$1
	shift
	echo -e "\033[${color}m$@\033[m"
}
cecho $red "hello"


make_paragraph
echo "# ヘルプメッセージを表示する"
usage() {
	cat <<EOF
$(basename ${0}) is tool for ...

Usage:
     $(basename ${0}) [command] [<options>]

Options:
     --version, -v     print $(basename ${0}) version
     --help, -h        print this
EOF
}

usage


make_paragraph
echo "# バージョンを表示する"
version() {
	echo "$(basename ${0}) version 0.0.1"
}

version


title "ファイルの存在確認"
if [ -f "~/.emacs.d/init.el" ]; then
	echo "~/.emacs.d/init.el exists"
fi

if [ ! -f "~/.vimrc" ]; then
	echo "~/.vimrc does not exist"
fi

title "ディレクトリの存在確認"
if [ -d "~/.emacs.d" ]; then
	echo "~/.emacs.d exists"
fi

title "アプリケーションの存在確認"
which emacs > /dev/null 2>&1
if [ $? -eq 0 ]; then
	echo "emacs process launch"
else
	echo "emacs process does not launch"
fi

echo "プラットフォームによる処理の分離"
UNAME=`uname`  #-rでバージョン、-pでアーキテクチャにも提供可能

if [ "$UNAME" = "Darwin" ]; then
	echo "you use mac."
elif [ "$UNAME" = "Linux" ]; then 
	echo "you use linux"
fi

title "ユーザに入力を求める"
askYesOrNo() {
	while true ; do
		read -p "$1 (y/n)?" answer
		case $answer in
			[yY] | [yY]es | YES )
				return 0;;
			[nN] | [nN]o | NO )
				return 1;;
			* ) echo "Please answer yes or no.";;
		esac
	done
}

askYesOrNo "please input yes or no!"
if [ $? -eq 0 ]; then
	#シェルスクリプトの返り値は$?で取得
	yes | echo "you input yes"
else
	yes | echo "you input no"
fi

title "環境変数で事前に設定されているかチェックし、なければ入力を要求"
if [ -z "${SHELL}" ]; then
	printf "SHELL: "
	read SHELL
fi
echo "SHELL: ${SHELL}"

if [ -z "${ID}" ]; then
	printf "ID: "
	read ID
fi

if [ -z "${PASSWORD}" ]; then
	stty -echo
	printf "PASSWORD: "
	read PASSWORD
	stty echo
fi

make_paragraph
echo "ID: ${ID}"
echo "PASSWORD: ${PASSWORD}"


echo "複数の選択肢（番号）から処理を選択させる場合"
while true; do
	cat <<EOF
which editor dou you want to use
1.Vim
2.GVim
3.Emacs
4.Nano 
EOF

	read ACTION
	case ${ACTION} in
		1)
			yes | echo "you chose Vim"
			break;;
		2)
			yes | echo "you chose GVim"
			break;;
		3)
			yes | echo "you chose Emacs"
			break;;
		4)
			yes | echo "you chose nano"
			break;;
		*)
			echo "Please input the number"
	esac
done

echo ""
echo "# 配列に追加していき一気に処理する"
INSTALL_LIST=("vim") #初期値が空の場合はINSTALL_LIST=()
askYesOrNo "Emacsをイントールしますか？"
if [ $? -eq 0 ]; then
	INSTALL_LIST=("${INSTALL_LIST[@]}" "emacs")
fi

INSTALL_LIST=("${INSTALL_LIST[@]}" "zsh")

echo "インストールの代わりに表示する"
for INSTALL in ${INSTALL_LIST[@]}; do
	yes | echo ${INSTALL}
done

