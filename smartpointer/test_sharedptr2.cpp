/**
   ref:
   http://cpprefjp.github.io/reference/memory/shared_ptr.html
 **/

#include <iostream>
#include <memory>

struct X {
    ~X()
    {
        std::cout << "X dtor" << std::endl;
    }
};

struct Y {
    ~Y()
    {
        std::cout << "Y dtor" << std::endl;
    }
};


int test2() {
    std::cout << "shared_ptr<void>にあらゆる型のポインタを格納" << std::endl;
    std::cout << "代入されたポインタの型がもつデストラクタが正しく実行されることを保証" << std::endl;
    
    std::shared_ptr<void> p(new X());
    
    std::cout << 0 << std::endl;
    
    p.reset(new Y()); // Xが破棄される
    
    std::cout << 1 << std::endl;
} // Yが破棄される

int test1() {
    std::cout << "shared_prtの基本的な使い方" << std::endl;
    // newしたポインタをshared_ptrオブジェクトに管理させる
    // 所有者は1人。
    std::shared_ptr<int> p1(new int(3));

    {
        // shared_ptrオブジェクトをコピーすることで、
        // 複数のオブジェクトが一つのリソースを共有できる。
        // 所有者が2人になる。
        std::shared_ptr<int> p2 = p1;

        // 共有しているリソースにアクセスする
        std::cout << *p2 << std::endl;
    } // p2のデストラクタが実行される。
    // リソースの所有者が1人になる。
    // ここではまだ、リソースは解放されない。

    std::cout << *p1 << std::endl;
} // p1のデストラクタが実行される。
// リソースの所有者が0人になる。
// 誰もリソースを参照しなくなったので、リソースが解放される。

int main() {
    test1();
    test2();
}
