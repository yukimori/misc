#include <iostream>
#include <string>
#include <memory>
#include <cassert>

/**
   ref:
   http://qiita.com/MasayaMizuhara/items/0b78f7046aaa6d17bb66
   http://ramemiso.hateblo.jp/entry/2013/09/01/180414
   http://d.hatena.ne.jp/A7M/20110529/1306648863

   shared_pointer 指定されたリソースへの所有権を共有するスマートポインタ
   newで作成したインスタンスを明示的に削除しなくても参照が0になると自動的にメモリを解放しデストラクタを呼び出してくれる
 **/

class Hoge {
private:
    std::string s_;
public:
    explicit Hoge(const std::string &s)
            :s_(s) {
        std::cout << "Hoge::Hoge(" + s_ + ")" << std::endl;
    }
    ~Hoge() {
        std::cout << "Hoge::~Hoge(" + s_ + ")" << std::endl;
    }
};

int main() {
    std::shared_ptr<Hoge> hoge_ptr0;

    {
        std::cout << "--- AとBの構築 ---" << std::endl;
        std::shared_ptr<Hoge> hoge_ptr1(new Hoge("A"));
        std::shared_ptr<Hoge> hoge_ptr2(new Hoge("B"));
        std::shared_ptr<Hoge> hoge_ptr3(new Hoge("C"));

        std::cout << hoge_ptr1.use_count() << std::endl;
        std::cout << hoge_ptr2.use_count() << std::endl;
        std::cout << hoge_ptr3.use_count() << std::endl;

        std::cout << "--- Aの破棄 ---" << std::endl;
        // Aがだれからも参照されなくなる
        hoge_ptr0 = hoge_ptr1 = hoge_ptr2;
        // hoge_ptr0,AがBを指すようになったのでBのカウント数は3になる
        std::cout << hoge_ptr1.use_count() << std::endl;
        std::cout << hoge_ptr2.use_count() << std::endl;
        std::cout << hoge_ptr3.use_count() << std::endl;

        std::cout << "--- Cの破棄 ---" << std::endl;
    } // スコープを抜けるとCを参照するものがいなくなるのでCは廃棄される

    std::cout << "--- Bの破棄 ---" << std::endl;
    
    return 0;
}
