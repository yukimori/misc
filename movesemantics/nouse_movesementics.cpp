#include <iostream>
#include <string.h>

"""
http://qiita.com/go_astrayer/items/5d85565e992487daa618

一部修正しないと動かない
"""

using namespace std;

struct Array
{
  typedef int ValueType;

  ValueType *p;
  int length;

  // コンストラクタ
  Array(int _length)
    : p(new ValueType[_length])
    , length(_length)
  {
	memset(p, 0, sizeof(ValueType) * length);
	p[0] = 123;
	cout << "constructor(" << this << ")" << endl;
  }

  // コピーコンストラクタ
  Array(const Array& o)
	: p(new ValueType[o.length])
	, length(o.length)
  {
	memcpy(p, o.p, sizeof(ValueType) * length);
	cout << "copy constructor(" << this << ")" << " <- " << &o << endl;
  }

  // デストラクタ
  ~Array() {
	if (p != nullptr) {
	  delete p, p = nullptr;
	  length = 0;
	}
	cout << "destructor(" << this << ")" << endl;
  }

  // 代入演算子(コピー)
  Array operator = (Array o)
  {
	length = o.length;
	memcpy(p, o.p, sizeof(ValueType) * length);
	cout << "copy(" << this << ")" << " <- " << &o << endl;
	return (*this);
  }
};

// Array を受け取り、それをそのまま返すだけ
Array Func(Array array) {
  return array;
}

int main()
{
  Array array(32);
  array = Func(array);

  return 0;
}
