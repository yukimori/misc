package main

import (
	"fmt"
	"math"
	"math/rand"
	"time"
)

// 型名は変数の後に
// https://blog.golang.org/gos-declaration-syntax
func add(x int, y int) int {
	return x + y
}

func main() {
	rand.Seed(time.Now().UnixNano())
	fmt.Println("My favorite number is", rand.Intn(10))
	// 最初が大文字は外部パッケージへ公開 exported names
	fmt.Println(math.Pi)
	fmt.Println(add(42, 13))
}
