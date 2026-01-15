#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "../../common/matrix_utils.h"
#include "../../common/timing.h"
#include "../../common/thread_utils.h"
#include "../../common/csv_utils.h"

#define BLOCK_SIZE 32

void compute_kernel(Matrix A, Matrix B, Matrix C,
                    int start_row, int end_row) {
    int N = A.N;
    int BS = BLOCK_SIZE;

    for (int ii = start_row; ii < end_row; ii += BS) {
        int i_max = (ii + BS < end_row) ? ii + BS : end_row;

        for (int jj = 0; jj < N; jj += BS) {
            int j_max = (jj + BS < N) ? jj + BS : N;

            for (int kk = 0; kk < N; kk += BS) {
                int k_max = (kk + BS < N) ? kk + BS : N;

                for (int i = ii; i < i_max; i++) {
                    for (int j = jj; j < j_max; j++) {
                        double sum = C.data[i][j];
                        for (int k = kk; k < k_max; k++) {
                            sum += A.data[i][k] * B.data[k][j];
                        }
                        C.data[i][j] = sum;
                    }
                }
            }
        }
    }
}



void* thread_entry(void *arg) {
    thread_arg_t *t = (thread_arg_t*)arg;
    compute_kernel(
        *(Matrix*)t->A,
        *(Matrix*)t->B,
        *(Matrix*)t->C,
        t->start_row,
        t->end_row
    );
    return NULL;
}

int main() {

    int matrix_sizes[] = {256, 512, 1024, 2048};
    int num_sizes = 4;
    int thread_counts[] = {1, 2, 4, 8, 16};
    int num_threads = 5;

    FILE *fp = fopen("../../reports/Q4_results/blocked.csv", "w");
    fprintf(fp, "matrix_size,threads,time_seconds\n");
    fclose(fp);

    for (int s = 0; s < num_sizes; s++) {
        int N = matrix_sizes[s];

        for (int t = 0; t < num_threads; t++) {
            int T = thread_counts[t];

            Matrix A = allocate_matrix(N);
            Matrix B = allocate_matrix(N);
            Matrix C = allocate_matrix(N);

            init_matrix(A);
            init_matrix(B);
            zero_matrix(C);

            pthread_t threads[T];
            thread_arg_t args[T];

            int rows_per_thread = N / T;

            start_timer();

            for (int i = 0; i < T; i++) {
                args[i].thread_id = i;
                args[i].start_row = i * rows_per_thread;
                args[i].end_row =
                    (i == T - 1) ? N : (i + 1) * rows_per_thread;
                args[i].A = &A;
                args[i].B = &B;
                args[i].C = &C;

                pthread_create(&threads[i], NULL, thread_entry, &args[i]);
            }

            for (int i = 0; i < T; i++) {
                pthread_join(threads[i], NULL);
            }

            double time_taken = stop_timer();

            write_csv(
                "../../reports/Q4_results/blocked.csv",
                N,
                T,
                time_taken
            );

            free_matrix(A);
            free_matrix(B);
            free_matrix(C);
        }
    }

    return 0;
}
