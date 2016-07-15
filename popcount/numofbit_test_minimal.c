#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>

enum {
    REPEAT    = 1,
    DATA_SIZE = 65536
};

extern int dummy(uint32_t x) __attribute__((noinline));
extern int numofbits1(uint32_t x) __attribute__((noinline));
extern int popcount8if(unsigned int x) __attribute__((noinline));

static double getdiff(const struct timeval *before, const struct timeval *after) {
    return (after->tv_sec - before->tv_sec) + 1.0 * (after->tv_usec - before->tv_usec) / 1000000;
}

static unsigned int data[DATA_SIZE];

int main(int argc, char** argv) {
    int i;
    struct timeval before, after;

    // Prepare input datas
    for (i=0 ; i<REPEAT ; i++) {
        data[i % DATA_SIZE] = rand();
    }

    // Warm up data cache
    /* for (i=0 ; i<REPEAT ; i++) { */
    /*     dummy(data[i % DATA_SIZE]); */
    /* } */

    /* struct timeval before, after; */

    // dummy
    gettimeofday(&before, NULL);
    /* for (i=0 ; i<REPEAT ; i++) { */
    /*     dummy(data[i % DATA_SIZE]); */
    /* } */
    /* gettimeofday(&after, NULL); */
    double base_time = getdiff(&before, &after);

    int ans = 0;
    //popcount8if
    for (i=0; i<REPEAT; i++) {
        ans = popcount8if(&data[i % DATA_SIZE]);
    }
    printf("ans:%d\n",ans);
    
    // numofbits1
    gettimeofday(&before, NULL);
    for (i=0 ; i<REPEAT ; i++) {
        numofbits1(data[i % DATA_SIZE]);
    }
    gettimeofday(&after, NULL);
    /* printf("numofbits1: %10.6f sec\n", getdiff(&before, &after) - base_time); */
    printf("ans:%d\n",ans);
    printf("numofbits1: %10.6f sec\n", getdiff(&before, &after));

    printf("finished...");
}
