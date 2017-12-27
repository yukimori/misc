#include <iostream>


class GamePlayer {
 private:
    // enumハック NumTurnsを5の代わりに使えるようにする
    enum { NumTurns = 5 };

    // 問題なし
    int scores[NumTurns];
};

int main(void) {

}
