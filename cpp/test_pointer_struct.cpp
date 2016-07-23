
#include <cstdio>
#include <iostream>


struct mixed {
    char code;
    double value;
    int length;
};

int main() {
    
    struct mixed mix1;
    
    printf("構造体のアドレス\n");
    printf("mix1 %p \n", &mix1);
    printf("構造体のcodeメンバのアドレス\n");
    printf("char mix1->code %p \n", &mix1.code);

    printf("\n") ;
    printf("構造体のvalueメンバのアドレス\n");
    printf("double mix1->value %p \n", &mix1.value);
    printf("codeは1バイトのはずだが、valueとは8バイト離れている\n");
    printf("メンバ間には空きがある！（空きをパディングと呼ぶ）\n");

    printf("size of double : %d\n", sizeof(mix1.value));

    printf("\n");
    printf("構造体のlengthメンバのアドレス\n");
    printf("int mix1->length %p \n", &mix1.length);
    printf("mix1.valueとmix1.lengthは8バイト離れており、空きがない\n");
    printf("\n");
    printf("0を(struct mixed*)型に変換してvalueメンバのアドレスをsize_t型に変換してoffset値として使えるようにする\n");
    printf("(size_t)&((struct mixed*)0->value) %d \n",((size_t)&((struct mixed*)0)->value));
    printf("そのときのアドレス\n");
    printf("address %p \n",(&((struct mixed*)0)->value));
}
