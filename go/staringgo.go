package main

import fmt "fmt" // 入出力フォーマットを実装したパッケージ

func doSomething() (int, int) {
	return 0,1
}

func hasVarforReturnvalue() (x, y int) {
	y = 5
	return
}

func printTitle(title string) {
	fmt.Printf("\n")
	fmt.Printf("##### %s #####\n", title)
}

func main() {
    fmt.Printf("Hello, world; こんにちは 世界\n")
	x, y := 3, 5
	fmt.Printf("%+v\n", x)

	fmt.Printf("簡易文付きif\n")
	// ifの外側では変数nは未定義
	if n := x * y; n%2 == 0 {
		fmt.Printf("n(%d) is even\n", n)
	} else {
		fmt.Printf("n(%d) is odd\n", n)
	}

	fmt.Printf("doSomethingの2番目の戻り値がエラーの有無を返却するように定義\n")
	fmt.Printf("エラーを格納する変数errはifブロック内でのみ有効\n")
	if _, err := doSomething(); &err != nil {
		// doSomething()がエラーありと返却した場合の処理
	}

	var x_interface interface{}
	fmt.Printf("%#v\n", x_interface)

	printTitle("関数定義の戻り値で変数を宣言する")
	returnX, returnY := hasVarforReturnvalue()
	fmt.Printf("returnX %d, returnY %d\n",returnX, returnY)
}
