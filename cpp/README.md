# コピーコンストラクタ
オブジェクトを同じ型の別のオブジェクトで初期化する

# コピー代入演算子
オブジェクトを同じ型の別のオブジェクトで代入する

class Widget {
	  public:
		Widget();
		Widget(const Widget& rhs);  // コピーコンストラクタ

}
