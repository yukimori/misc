#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>

enum {
    REPEAT    = 10000000,
    DATA_SIZE = 65536
};

extern int dummy(uint32_t x) __attribute__((noinline));
extern int numofbits1(uint32_t x) __attribute__((noinline));
extern int popcount8if(unsigned int x) __attribute__((noinline));
extern int popcount_16bit_table(unsigned int x) __attribute__((noinline));
extern int _popcount_16bit_table_init();

static double getdiff(const struct timeval *before, const struct timeval *after) {
    return (after->tv_sec - before->tv_sec) + 1.0 * (after->tv_usec - before->tv_usec) / 1000000;
}

static unsigned int data[DATA_SIZE];

int test(){
    printf("value check. loop:%d\n",REPEAT);
    printf("regard numofbits1 as correct\n");
    int ans_nob1 = 0;
    int ans_8if = 0;
    int ans_16table = 0;

    int test_ok = 1;
    for(int i=0; i<REPEAT; i++) {
        ans_nob1 = numofbits1(data[i % DATA_SIZE]);
        ans_8if = popcount8if(data[i % DATA_SIZE]);
        ans_16table = popcount_16bit_table(data[i % DATA_SIZE]);
        if(ans_nob1 != ans_8if) {
            test_ok = 0;
            printf("[%d]popcount 8if expect:%d fact:%d value:%x\n",i,ans_nob1, ans_8if,data[i%DATA_SIZE]);
            break;
        }
        if(ans_nob1 != ans_16table) {
            test_ok = 0;
            printf("[%d]popcount 16bit table expect:%d value:%d data:%x\n",i,ans_nob1, ans_16table,data[i%DATA_SIZE]);
            break;
        }
    }
    printf("lastvalue\n");
    printf("numofbits1:%d\n", ans_nob1);
    printf("popcount 8if:%d\n", ans_8if);
    printf("popcount 16bit table:%d\n", ans_16table);
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
    
    // numofbits1
    int ans_nob1 = 0;
    gettimeofday(&before, NULL);
    for (i=0 ; i<REPEAT ; i++) {
        ans_nob1 = numofbits1(data[i % DATA_SIZE]);
    }
    gettimeofday(&after, NULL);
    /* printf("numofbits1: %10.6f sec\n", getdiff(&before, &after) - base_time); */
    printf("numofbits1: %10.6f sec\n", getdiff(&before, &after));

    printf("finished...");
}
