#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    double **data;  
    int N;
} Matrix;

/* Allocate NxN matrix (2D using malloc) */
static inline Matrix allocate_matrix(int N) {
    Matrix m;
    m.N = N;

    /* Allocate row pointers */
    m.data = (double**)malloc(N * sizeof(double*));
    if (!m.data) {
        fprintf(stderr, "Row pointer allocation failed\n");
        exit(1);
    }

    /* Allocate each row */
    for (int i = 0; i < N; i++) {
        m.data[i] = (double*)malloc(N * sizeof(double));
        if (!m.data[i]) {
            fprintf(stderr, "Row allocation failed at row %d\n", i);
            exit(1);
        }
    }

    return m;
}

/* Initialize matrix with deterministic values */
static inline void init_matrix(Matrix m) {
    for (int i = 0; i < m.N; i++) {
        for (int j = 0; j < m.N; j++) {
            m.data[i][j] = (double)((i * m.N + j) % 100);
        }
    }
}

/* Zero matrix */
static inline void zero_matrix(Matrix m) {
    for (int i = 0; i < m.N; i++) {
        for (int j = 0; j < m.N; j++) {
            m.data[i][j] = 0.0;
        }
    }
}

/* Free matrix memory */
static inline void free_matrix(Matrix m) {
    for (int i = 0; i < m.N; i++) {
        free(m.data[i]);
    }
    free(m.data);
}

/* Access macro */
#define MAT(m, i, j) m.data[(i)][(j)]

#endif
