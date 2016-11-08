# コピーコンストラクタ
オブジェクトを同じ型の別のオブジェクトで初期化する

Widget w2(w1);


# コピー代入演算子
オブジェクトを同じ型の別のオブジェクトで代入する

Widget w3 = w2;

class Widget {
	  public:
		Widget();
		Widget(const Widget& rhs);  // コピーコンストラクタ
		Widget& operator=(const Widget& rhs)  // コピー代入演算子
}

# クラスの定数
class testvector {
 public:
    testvector();
    static const int CONST_H_PB = 1;
    // staticでない変数は初期化できない
    // static int CONST_H_PB;
 private:
    static const int CONST_H_PV = 2;
};

testvector::testvector() {
    std::cout << "testvector constructor" << std::endl;
    std::cout << "CONST_H_PV:" << CONST_H_PV << std::endl;
}

}  // namespace my

int main() {

    my::testvector tv = my::testvector();
    // private変数は参照できない
    // std::cout << "CONST_H_PV:" << tv.CONST_H_Pv << std::endl;
    std::cout << "CONST_H_PB:" << tv.CONST_H_PB << std::endl;

}

# #2 enumハック
コンパイル時にクラスの定数が必要になった場合に使うテクニック
enum型の値がintとしても使えることを利用
effectivecpp.{hpp,cpp}を参照のこと