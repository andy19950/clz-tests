#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "clz.h"

#define CLOCK_ID CLOCK_MONOTONIC_RAW
#define ONE_SEC 1000000000.0

int main(int argc, char const *argv[])
{
    struct timespec start = {0, 0};
    struct timespec end = {0, 0};

    if (argc < 2) return -1;

    uint32_t N = 0xFF;
    int i, loop = 25;

    // Recursize
    clock_gettime(CLOCK_ID, &start);
    for(i = 0; i < loop; i++) {
        clz_recur(N, SIZE);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%.4f ", (double) ((end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC) * 1000 );
    
    // Iteration
    clock_gettime(CLOCK_ID, &start);
    for(i = 0; i < loop; i++) {
        clz_itera(N);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%.4f ", (double) ((end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC) * 1000 );


    // OpenMP with 2 threads
    clock_gettime(CLOCK_ID, &start);
    for(i = 0; i < loop; i++) {
        clz_Harley(N);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%.4f\n", (double) ((end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC) * 1000 );


    return 0;
}
