#ifndef CSV_UTILS_H
#define CSV_UTILS_H

#include <stdio.h>

static inline void write_csv(
    const char *filename,
    int matrix_size,
    int threads,
    double time_sec
) {
    FILE *fp = fopen(filename, "a");
    if (!fp) return;

    fprintf(fp, "%d,%d,%.6f\n", matrix_size, threads, time_sec);
    fclose(fp);
}

#endif
