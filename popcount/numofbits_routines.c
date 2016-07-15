#include <stdio.h>

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
        x++;
    }
    return c;
}

int numofbits1(int bits)
{
    int num  = 0;
    int mask = 1;

    for ( ; mask != 0 ; mask = mask << 1 ){
        if (bits & mask )
            num++;
    }

    return num;
}

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

int numofbits2(int bits)
{
    int num  = 0;

    for (int i=0 ; i<sizeof(bits) ; i++ ) {
        num += BITS_COUNT_TABLE[((unsigned char*)&bits)[i]];
    }

    return num;
}

int numofbits3(int bits)
{
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
