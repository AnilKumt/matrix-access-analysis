#ifndef TIMING_H
#define TIMING_H

#include <time.h>

static struct timespec __start_time, __end_time;

static inline void start_timer() {
    clock_gettime(CLOCK_MONOTONIC, &__start_time);
}

static inline double stop_timer() {
    clock_gettime(CLOCK_MONOTONIC, &__end_time);
    return (__end_time.tv_sec - __start_time.tv_sec) +
           (__end_time.tv_nsec - __start_time.tv_nsec) * 1e-9;
}

#endif
