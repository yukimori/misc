
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

/**
   ref:
   http://www.mm2d.net/main/prog/c/time-05.html
   http://kernhack.hatenablog.com/entry/2013/12/04/165249
 **/


static inline double
timespec2msec(const struct timespec *st)
{
    return (double) st->tv_sec + (double) st->tv_nsec * 1e-9;
}

static void
test_common(const char *name, clockid_t clk_id)
{
    struct timespec start, end;

    clock_gettime(clk_id, &start);

    sleep(1);

    clock_gettime(clk_id, &end);

    printf("%s: %f msec\n", name, timespec2msec(&end) - timespec2msec(&start));
}

static void *
test_func(void *data)
{
    test_common(__FUNCTION__, CLOCK_THREAD_CPUTIME_ID);
    return NULL;
}

#define NUM_TEST_THREADS 8
static void
test_clock_thread_cputime_id(void)
{
    struct timespec start, end;

    pthread_t ths[NUM_TEST_THREADS];
    int i, ret;

    printf("Test CLOCK_THREAD_CPUTIME_ID\n");
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

    for (i = 0; i < NUM_TEST_THREADS; i++) {
        ret = pthread_create(&ths[i], NULL, test_func, NULL);
        assert(ret == 0);
    }

    for (i = 0; i < NUM_TEST_THREADS; i++)
        pthread_join(ths[i], NULL);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

    printf("%s: %f msec\n", __FUNCTION__, timespec2msec(&end) - timespec2msec(&start));
}

static void
test_clock_process_cputime_id(void)
{
    printf("Test CLOCK_PROCESS_CPUTIME_ID\n");
    test_common(__FUNCTION__, CLOCK_PROCESS_CPUTIME_ID);
}

static void
test_clock_realtime(void)
{
    printf("Test CLOCK_REALTIME\n");
    test_common(__FUNCTION__, CLOCK_REALTIME);
}

static void
usage(char *name)
{
    fprintf(stderr, "%s option\n", name);
    fprintf(stderr, "0: test CLOCK_REALTIME\n");
    fprintf(stderr, "1: test CLOCK_PROCESS_CPUTIME_ID\n");
    fprintf(stderr, "2: test CLOCK_THREAD_CPUTIME_ID\n");
    exit(-1);
}


int main(int argc, char **argv) {
    struct timespec ts;
    printf("time():  %10ld\n", time(NULL));
    clock_getres(CLOCK_REALTIME, &ts);
    printf("res :    %10ld.%09ld CLOCK_REALTIME\n", ts.tv_sec, ts.tv_nsec);
    clock_gettime(CLOCK_REALTIME, &ts);
    printf("time:    %10ld.%09ld CLOCK_REALTIME\n", ts.tv_sec, ts.tv_nsec);
    #ifdef CLOCK_REALTIME_COARSE
    clock_getres(CLOCK_REALTIME_COARSE, &ts);
    printf("res :    %10ld.%09ld CLOCK_REALTIME_COARSE\n", ts.tv_sec, ts.tv_nsec);
    clock_gettime(CLOCK_REALTIME_COARSE, &ts);
    printf("time:    %10ld.%09ld CLOCK_REALTIME_COARSE\n", ts.tv_sec, ts.tv_nsec);
    #endif
    clock_getres(CLOCK_MONOTONIC, &ts);
    printf("res :    %10ld.%09ld CLOCK_MONOTONIC\n", ts.tv_sec, ts.tv_nsec);
    clock_gettime(CLOCK_MONOTONIC, &ts);
    printf("time:    %10ld.%09ld CLOCK_MONOTONIC\n", ts.tv_sec, ts.tv_nsec);
    #ifdef CLOCK_MONOTONIC_COARSE
    clock_getres(CLOCK_MONOTONIC_COARSE, &ts);
    printf("res :    %10ld.%09ld CLOCK_MONOTONIC_COARSE\n", ts.tv_sec, ts.tv_nsec);
    clock_gettime(CLOCK_MONOTONIC_COARSE, &ts);
    printf("time:    %10ld.%09ld CLOCK_MONOTONIC_COARSE\n", ts.tv_sec, ts.tv_nsec);
    #endif
    #ifdef CLOCK_MONOTONIC_RAW
    clock_getres(CLOCK_MONOTONIC_RAW, &ts);
    printf("res :    %10ld.%09ld CLOCK_MONOTONIC_RAW\n", ts.tv_sec, ts.tv_nsec);
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    printf("time:    %10ld.%09ld CLOCK_MONOTONIC_RAW\n", ts.tv_sec, ts.tv_nsec);
    #endif
    #ifdef CLOCK_BOOTTIME
    clock_getres(CLOCK_BOOTTIME, &ts);
    printf("res :    %10ld.%09ld CLOCK_BOOTTIME\n", ts.tv_sec, ts.tv_nsec);
    clock_gettime(CLOCK_BOOTTIME, &ts);
    printf("time:    %10ld.%09ld CLOCK_BOOTTIME\n", ts.tv_sec, ts.tv_nsec);
    #endif
    clock_getres(CLOCK_PROCESS_CPUTIME_ID, &ts);
    printf("res :    %10ld.%09ld CLOCK_PROCESS_CPUTIME_ID\n", ts.tv_sec, ts.tv_nsec);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
    printf("time:    %10ld.%09ld CLOCK_PROCESS_CPUTIME_ID\n", ts.tv_sec, ts.tv_nsec);
    clock_getres(CLOCK_THREAD_CPUTIME_ID, &ts);
    printf("res :    %10ld.%09ld CLOCK_THREAD_CPUTIME_ID\n", ts.tv_sec, ts.tv_nsec);
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts);
    printf("time:    %10ld.%09ld CLOCK_THREAD_CPUTIME_ID\n", ts.tv_sec, ts.tv_nsec);
    printf("clock(): %20.9f\n", (double)(clock()) / CLOCKS_PER_SEC);


    int testcase = 0;

    if (argc > 1) {
        testcase = atoi(argv[1]);
    }

    // http://kernhack.hatenablog.com/entry/2013/12/04/165249
    switch (testcase) {
        case 0:
            // CLOCK_REALTIMEで実時間測定
            test_clock_realtime();
            break;
        case 1:
            // プロセスのcpu時間測定
            test_clock_process_cputime_id();
            break;
        case 2:
            // スレッド毎のcpu時間とプロセスのcpu時間測定
            test_clock_thread_cputime_id();
            break;
        default:
            usage(argv[0]);
    }
    
    return 0;
}
