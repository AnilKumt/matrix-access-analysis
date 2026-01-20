#ifndef TASK_H
#define TASK_H

typedef struct {
    int r0;   // row start (inclusive)
    int r1;   // row end   (exclusive)
    int c0;   // col start (inclusive)
    int c1;   // col end   (exclusive)
} Task;

#endif
