package foo

const (
	MAX = 100
	internal_const = 1
)

func FooFunc(n int) int {
	return internalFunc(n)
}

func internalFunc(n int) int {
	return n + 1
}
