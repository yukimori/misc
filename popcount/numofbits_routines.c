
#include <stdio.h>
#include <stdint.h>
#include "immintrin.h"

/**
   ref:
   http://www.nminoru.jp/~nminoru/programming/bitcount.html
   http://www.slideshare.net/takesako/x86x64-sse42-popcnt
 **/

int dummy(uint32_t x) {
    return 0;
}

/**
   1byteあたり8回条件分岐してbitを数える
 **/
int popcount8if(unsigned int x) {
    int i = 0;
    int c = 0;
    for ( ; i < sizeof(x); i++) {
        if(((unsigned char*)&x)[i] & 0x01) c++;
        if(((unsigned char*)&x)[i] & 0x02) c++;
        if(((unsigned char*)&x)[i] & 0x04) c++;
        if(((unsigned char*)&x)[i] & 0x08) c++;
        if(((unsigned char*)&x)[i] & 0x10) c++;
        if(((unsigned char*)&x)[i] & 0x20) c++;
        if(((unsigned char*)&x)[i] & 0x40) c++;
        if(((unsigned char*)&x)[i] & 0x80) c++;
    }
    return c;
}

int numofbits1(int bits) {
    int num  = 0;
    int mask = 1;

    for ( ; mask != 0 ; mask = mask << 1 ){
        if (bits & mask )
            num++;
    }
    return num;
}

/**
   256byteのテーブルを作成して表引き
 **/
const int BITS_COUNT_TABLE[256] = {
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
};

int numofbits2(int bits) {
    int num  = 0;

    for (int i=0 ; i<sizeof(bits) ; i++ ) {
        num += BITS_COUNT_TABLE[((unsigned char*)&bits)[i]];
    }

    return num;
}

static char pop_table16bit[256 * 256];
void _popcount_16bit_table_init(void) {
    for(int i=0; i<256; i++) {
        for(int j=0; j<256; j++){
            pop_table16bit[i*256 + j] = BITS_COUNT_TABLE[i] + BITS_COUNT_TABLE[j];
        }
    }
}
int popcount_16bit_table(int bits) {
    int num = 0;
    /* _popcount_16bit_table_init(); */
    /* for(int i=0; i<256; i++) { */
    /*     printf("%d ",pop_table16bit[i]); */
    /* } */
    /* printf("\n"); */
    for(int i=0; i<(sizeof(bits)/2); i++){
        num += pop_table16bit[((unsigned short*)&bits)[i]];
    }
    return num;
}

int numofbits3(int bits) {
    int num  = 0;

    for ( ; bits != 0 ; bits &= bits - 1 ) {
        num++;
    }

    return num;
}

int numofbits4(int bits)
{
    int num;

    num = (bits >> 1) & 03333333333;
    num = bits - num - ((num >> 1) & 03333333333);
    num = ((num + (num >> 3)) & 0707070707) % 077;

    return num;
}

int numofbits5(long bits)
{
    bits = (bits & 0x55555555) + (bits >> 1 & 0x55555555);
    bits = (bits & 0x33333333) + (bits >> 2 & 0x33333333);
    bits = (bits & 0x0f0f0f0f) + (bits >> 4 & 0x0f0f0f0f);
    bits = (bits & 0x00ff00ff) + (bits >> 8 & 0x00ff00ff);
    return (bits & 0x0000ffff) + (bits >>16 & 0x0000ffff);
}
/**
   inline assemblar
   http://d.hatena.ne.jp/wocota/20090628/1246188338
 **/
int popcnt(uint32_t bits) {
    int ret;
    __asm__ ("popcntl %[input], %[output]" : [output] "=r"(ret) : [input] "r"(bits));
    return ret;
}

unsigned int popcount_64bitsse42(uint32_t bits1, uint32_t bits2) {
    uint64_t bits = (uint64_t)bits1 << 32;
    bits += bits2;
    //    printf("%x + %x = %llx\n",bits1,bits2,bits);
    int c = _mm_popcnt_u64(bits);
    return c;
}

unsigned int popcount_32bitsse42(uint32_t bits) {
    int c = _mm_popcnt_u32(bits);
    return c;
}
