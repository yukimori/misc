
namespace my {

class testvector {
 public:
    testvector();
    static const int CONST_H_PB = 1;
    // staticでない変数は初期化できない
    // static int CONST_H_PB;
 private:
    static const int CONST_H_PV = 2;
    // enumハック NumTurnsを5の代わりに使えるようにする
    enum { NumTurns = 5 };

    // 問題なし
    int scores[NumTurns];
};


}  // namespace my
