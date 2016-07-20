#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>

/**
   ref:http://www.nminoru.jp/~nminoru/programming/numofbits_test.c
   gcc numofbit_test_minimal.c numofbits_routines.c -msse4.2
 **/

enum {
    REPEAT    = 10000,
    DATA_SIZE = 65536
};

extern int dummy(uint32_t x) __attribute__((noinline));
extern int numofbits1(uint32_t x) __attribute__((noinline));
int numofbits5(uint32_t x);
extern int popcount8if(unsigned int x) __attribute__((noinline));
extern int popcount_16bit_table(unsigned int x) __attribute__((noinline));
extern int _popcount_16bit_table_init();
extern int popcount_32bitsse42(uint32_t bits);
int popcount_64bitsse42(uint32_t bits1, uint32_t bits2);

static double getdiff(const struct timeval *before, const struct timeval *after) {
    return (after->tv_sec - before->tv_sec) + 1.0 * (after->tv_usec - before->tv_usec) / 1000000;
}

static unsigned int data[DATA_SIZE];

int test(){
    printf("value check. loop:%d\n",REPEAT);
    printf("regard numofbits1 as correct\n");
    int ans_nob1 = 0;
    int ans_nob5 = 0;
    int ans_8if = 0;
    int ans_16table = 0;
    int ans_popcntsse42 = 0;
    int ans_popcnt64sse42 = 0;

    
    int test_ok = 1;
    for(int i=0; i<REPEAT; i++) {
        ans_nob1 += numofbits1(data[i % DATA_SIZE]);
        ans_nob5 += numofbits5(data[i % DATA_SIZE]);
        ans_8if += popcount8if(data[i % DATA_SIZE]);
        ans_16table += popcount_16bit_table(data[i % DATA_SIZE]);
        ans_popcntsse42 += popcount_32bitsse42(data[i % DATA_SIZE]);

        if(ans_nob1 != ans_8if) {
            test_ok = 0;
            printf("[%d]popcount 8if expect:%d fact:%d value:%x\n",i,ans_nob1, ans_8if,data[i%DATA_SIZE]);
            break;
        }
        if(ans_nob1 != ans_nob5) {
            test_ok = 0;
            printf("[%d]nomofbit5 expect:%d fact:%d value:%x\n",i,ans_nob1, ans_nob5,data[i%DATA_SIZE]);
            break;
        }
        if(ans_nob1 != ans_16table) {
            test_ok = 0;
            printf("[%d]popcount 16bit table expect:%d value:%d data:%x\n",i,ans_nob1, ans_16table,data[i%DATA_SIZE]);
            break;
        }
        if(ans_nob1 != ans_popcntsse42) {
            test_ok = 0;
            printf("[%d]popcnt 32bit sse4.2 expect:%d value:%d data:%x\n",i,ans_nob1, ans_popcntsse42,data[i%DATA_SIZE]);
            break;
        }
    }

    for(int i=0; i<REPEAT; i+=2) {
        ans_popcnt64sse42 += popcount_64bitsse42(data[i%DATA_SIZE],
                                                 data[(i+1)%DATA_SIZE]);
    }
    if(ans_nob1 != ans_popcnt64sse42) {
        test_ok = 0;
        printf("popcount_64bitsse42 calcurate wrong values.\n");
    }

    printf("sum 1 bits\n");
    printf("numofbits1:%d\n", ans_nob1);
    printf("numofbits5:%d\n", ans_nob5);
    printf("popcount 8if:%d\n", ans_8if);
    printf("popcount 16bit table:%d\n", ans_16table);
    printf("popcount 64bit sse4.2:%d\n", ans_popcnt64sse42);
    if(test_ok){
        printf("%s\n", "algorithms are correct.");
    } else {
        printf("%s\n", "some algorithms may have error.");
    }
    return test_ok;
}

void print_time(char *method, struct timeval before, struct timeval after) {
    printf("%s: %10.6f sec\n", method, getdiff(&before, &after));
}

int main(int argc, char** argv) {
    int i;
    struct timeval before, after;

    // Prepare
    // input datas
    for (i=0 ; i<REPEAT ; i++) {
        data[i % DATA_SIZE] = rand();
    }
    // 16bit table(64KB)
    _popcount_16bit_table_init();

    // Warm up data cache
    /* for (i=0 ; i<REPEAT ; i++) { */
    /*     dummy(data[i % DATA_SIZE]); */
    /* } */

    /* struct timeval before, after; */

    test();
    
    // dummy
    gettimeofday(&before, NULL);
    /* for (i=0 ; i<REPEAT ; i++) { */
    /*     dummy(data[i % DATA_SIZE]); */
    /* } */
    gettimeofday(&after, NULL);

    int ans_8if = 0;
    //popcount8if
    gettimeofday(&before, NULL);
    for (i=0; i<REPEAT; i++) {
        ans_8if = popcount8if(data[i % DATA_SIZE]);
    }
    gettimeofday(&after, NULL);
    printf("popcount8if: %10.6f sec\n", getdiff(&before, &after));

    int ans_16table = 0;
    gettimeofday(&before, NULL);
    for (i=0; i<REPEAT; i++) {
        ans_16table = popcount_16bit_table(data[i % DATA_SIZE]);
    }
    gettimeofday(&after, NULL);
    print_time("popcount_16bit_table", before, after);

    int ans_popcntsse42 = 0;
    gettimeofday(&before, NULL);
    for (i=0; i<REPEAT; i++) {
        ans_popcntsse42 = popcount_32bitsse42(data[i % DATA_SIZE]);
    }
    gettimeofday(&after, NULL);
    print_time("popcount_32bitsse42", before, after);

    int ans_popcnt64sse42 = 0;
    gettimeofday(&before, NULL);
    for (i=0; i<REPEAT; i+=2) {
        ans_popcnt64sse42 = popcount_64bitsse42(data[i%DATA_SIZE],
                                                 data[(i+1)%DATA_SIZE]);

    }
    gettimeofday(&after, NULL);
    print_time("popcount_64bitsse42", before, after);

    
    // numofbits5
    int ans_nob5 = 0;
    gettimeofday(&before, NULL);
    for (i=0 ; i<REPEAT ; i++) {
        ans_nob5 = numofbits5(data[i % DATA_SIZE]);
    }
    gettimeofday(&after, NULL);
    /* printf("numofbits1: %10.6f sec\n", getdiff(&before, &after) - base_time); */
    printf("numofbits5: %10.6f sec\n", getdiff(&before, &after));

    
    // numofbits1
    int ans_nob1 = 0;
    gettimeofday(&before, NULL);
    for (i=0 ; i<REPEAT ; i++) {
        ans_nob1 = numofbits1(data[i % DATA_SIZE]);
    }
    gettimeofday(&after, NULL);
    /* printf("numofbits1: %10.6f sec\n", getdiff(&before, &after) - base_time); */
    printf("numofbits1: %10.6f sec\n", getdiff(&before, &after));

    printf("finished...\n");
}
