#ifndef THREAD_UTILS_H
#define THREAD_UTILS_H

#include <pthread.h>

typedef struct {
    int thread_id;
    int start_row;
    int end_row;
    int N;
    void *A;
    void *B;
    void *C;
} thread_arg_t;

#endif
