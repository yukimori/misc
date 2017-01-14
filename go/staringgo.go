package main

import (
	"fmt" // 入出力フォーマットを実装したパッケージ
	"runtime" // goランタイム自身の情報を取得するなど
)

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

func printSubtitle(subtitle string) {
	fmt.Println()
	fmt.Println("-- ", subtitle)
}

func printComment(comment string) {
	fmt.Printf("    # %s\n", comment)
}

func returnFunc() func() {
	return func() {
		fmt.Println("I'm a function")
	}
}

func callFunc(f func()) {
	f()
}

func later() func(string) string {
	// 1つ前に与えられた文字列を保存するための変数
	// クロージャ内から参照されるためクロージャに属する変数としてコンパイラに扱われる
	var store string
	// 引数に文字列をとり(1つ前の)文字列を返す関数を返却
	return func(next string) string {
		s := store
		store = next
		return s
	}
}

// クロージャを使ったジェネレータ
// 1ずつ増分して返却するクロージャ
func integers() func() int {
	i := 0
	return func() int {
		i += 1
		return i
	}
}

func init() {
	fmt.Println("init()")
}

var S = ""

func init() {
	S = S + "A"
}

func init() {
	S = S + "B"
}

func init() {
	S = S + "C"
}

func runDefer(flag bool) {
	if flag == true {
		fmt.Println("defer登録前にreturnしたときにどうなるか") // deferは実行されない
		return
	}
	defer fmt.Println("defer")
	fmt.Println("execute RunDefer")
}

func sub() {
	for i:=0; i<100000; i++ {
		fmt.Println(i, " sub loop")
	}
	fmt.Println("exit sub")
}

func testSliceCopy() {
	s1 := []int{1, 2, 3, 4, 5}
	s2 := []int{10, 11}
	n := copy(s1, s2)
	printComment("コピー先の要素数だけコピーが成功する")
	fmt.Println(n)
	printComment("コピーした要素数が返却される")
}

func testSliceFor() {
	s := []string{"apple", "banana", "cherry"}
	for i, v := range s {
		fmt.Printf("[%d] => %s\n", i, v)
	}
}

func sum(s ...int) int {
	n := 0
	for _, v := range s {
		n += v
	}
	return n
}

func variable_arg_slice() {
	s := []int{1, 2, 3}
	fmt.Println(sum(s...))
}

func test_map() {
	printComment("map[キーの型]要素の型")
	m := make(map[int]string)
	m[1] = "us"
	m[81] = "jp"
	m[86] = "cn"
	fmt.Println(m)

	printComment("マップのリテラル make[int]string{}")
	m2 := map[int]string{1: "Taro", 2:"Hanako", 3:"Jiro"}
	fmt.Println(m2)

	fmt.Println(m[1])
	fmt.Println(m[2])

	printComment("参照した際にキーが存在しない場合は型の初期値が返却される")
	printComment("string型の場合は空文字")
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

	printTitle("無名関数")
	f := func(x, y int) int {
		return x+y
	}
	fmt.Printf("f(3,5) : %d\n", f(3,5))
	fmt.Printf("type of func(x, y int) : %T\n", func(x, y int) int { return x+y })
	fmt.Printf("無名関数の型と値(メモリ上のアドレス) : %#v\n", func(x, y int) int { return x+y })
	fmt.Printf("無名関数の演算結果(2+3) : %#v\n", func(x, y int) int { return x+y }(2, 3))

	printSubtitle("戻り値として関数を返却する")
	f2 := returnFunc()
	f2()
	printSubtitle("戻り値の関数を直接呼び出す ex)returnFunc()()")
	returnFunc()()
	printSubtitle("引数に関数をとる関数")
	callFunc(func() {
		fmt.Println("called via callFunc()")
	})
	printSubtitle("クロージャ")
	f3 := later()
	fmt.Println(f3("Golang"))
	fmt.Println(f3("is"))
	fmt.Println(f3("awesome"))
	printComment("一つ前に指定した引数が返却されている")
	printSubtitle("クロージャを使ったジェネレータ例:1ずつ増分するジェネレータ")
	ints := integers()
	fmt.Println(ints())
	fmt.Println(ints())
	fmt.Println(ints())
	printComment("クロージャを新しく生成すると変数領域も新しく確保される")
	other := integers()
	fmt.Println(other())
	printTitle("3.14 制御構文")
	printSubtitle("defer 関数の終了時に実行される式の登録")
	runDefer(false)
	runDefer(true)
	printSubtitle("go 並行処理")
	// go sub() // goroutinue開始

	// go func() {
	// 	for {
	// 		fmt.Println("noname sub loop")
	// 	}
	// }() //  関数呼び出しなので()が必要

	// for i:=0; i<10000; i++ {
	// 	fmt.Println(i, " main loop")
	// }
	// printComment("mainスレッドが終了するとgoで呼び出した関数も終了する？")
	// printComment("mainでのループが少なすぎる（早く終了する）とsubの処理（表示）がされない")

	printSubtitle("runtimeによる情報収集")
	fmt.Printf("NumCPU: %d\n", runtime.NumCPU())
	fmt.Printf("NumGoroutine: %d\n", runtime.NumGoroutine())
	fmt.Printf("Version: %s\n", runtime.Version())

	printSubtitle("init パッケージの初期化")
	printComment("init関数はmain関数に先立ち実行される")
	printComment("init関数は複数定義可能")
	printComment("定義順に実行される")
	fmt.Println(S)

	printTitle("4.3 slice 可変長配列を表現")
	// var s []int
	s := make([]int, 10)
	fmt.Println(s)
	fmt.Printf("%#v\n", s)
	s[1] = 1
	fmt.Println(s)
	s[2] = 2
	fmt.Println(s)
	fmt.Printf("len : %d\n", len(s))
	fmt.Printf("cap : %d\n", cap(s))

	printSubtitle("要素5, 容量10のスライス")
	s2 := make([]int, 5, 10)
	fmt.Println(len(s2))
	fmt.Println(cap(s2))
	printComment("容量まではメモリ確保が必要ない．メモリ上の領域に移動させるのはコストが高い")
	s3 := []int{1, 2, 3, 4, 5}
	fmt.Printf("s3 len : %d\n", len(s3))
	fmt.Printf("s3 cap : %d\n", cap(s3))
	printComment("配列と見た目は非常に類似")
	var a [10]int
	fmt.Println(a)
	fmt.Printf("%#v\n", a)

	printSubtitle("簡易スライス式")
	a2 := [5]int{1, 2, 3, 4, 5}
	s4 := a2[0:2]  // 変数s4は[]int型
	fmt.Printf("%v\n", s4)
	printComment("簡易スライス式は文字列にも適用可能．文字数ではなくバイト数になることに注意")
	s_str := "あいうえお"
	fmt.Println(s_str[3:9])
	printComment("utf-8なので1文字3バイト")

	printSubtitle("append")
	s3 = append(s3, 6, 7, 8, 9)
	fmt.Printf("s3 : %v\n", s3)
	printComment("任意の数の値を追加できる")
	var b []byte
	b = append(b, "あいうえお"...)
	b = append(b, "かきくけこ"...)
	b = append(b, "さしすせそ"...)
	printComment("別のスライスを追加するときは s2... という特殊な書き方になる")
	fmt.Println(b)

	printSubtitle("copy")
	testSliceCopy()

	printSubtitle("sliceとfor")
	testSliceFor()

	printSubtitle("可変長引数")
	fmt.Printf("sum:%d\n",sum(1, 2, 3, 4, 5))
	printComment("可変長引数は引数の末尾に1つだけ定義できる")

	printComment("スライスを可変長引数として使える．引数のときは...を追加")
	variable_arg_slice()

	printComment("配列からスライスを生成するとスライスの値は配列を参照している")
	printComment("そのため配列の値の変更はスライスにも影響する")
	printComment("ただし，スライスが自動拡張されるとメモリ領域が新しく割り当てられるので配列との関係がきれる")

	printTitle("Map 連想配列")
	test_map()
}
