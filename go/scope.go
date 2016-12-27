package main

import (
	"./foo"
	"fmt"
)

func main() {
	fmt.Printf("test")
	//foo.internal_const  // コンパイルエラー．参照できない
	fmt.Print(foo.MAX)    // fooパッケージの定数MAXを参照

//	ret = foo.FooFunc(5)
//	fmt.Printf(ret)
	//foo.internalFunc(5)  // パッケージ内でしか参照できない
}
