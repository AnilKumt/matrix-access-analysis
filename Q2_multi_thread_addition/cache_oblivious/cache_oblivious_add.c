#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "../../common/matrix_utils.h"
#include "../../common/timing.h"
#include "../../common/thread_utils.h"
#include "../../common/csv_utils.h"


#define BASE_SIZE 32 

static void add_recursive(Matrix A, Matrix B, Matrix C,
                          int r0, int r1,
                          int c0, int c1) {
    int rows = r1 - r0;
    int cols = c1 - c0;

    /* Base case */
    if (rows <= BASE_SIZE && cols <= BASE_SIZE) {
        for (int i = r0; i < r1; i++) {
            for (int j = c0; j < c1; j++) {
                C.data[i][j] = A.data[i][j] + B.data[i][j];
            }
        }
        return;
    }

    /* Recursive divide */
    if (rows >= cols) {
        int rm = r0 + rows / 2;
        add_recursive(A, B, C, r0, rm, c0, c1);
        add_recursive(A, B, C, rm, r1, c0, c1);
    } else {
        int cm = c0 + cols / 2;
        add_recursive(A, B, C, r0, r1, c0, cm);
        add_recursive(A, B, C, r0, r1, cm, c1);
    }
}



/* ============================================================
   TODO: IMPLEMENT THIS FUNCTION ONLY
   ============================================================ */
void compute_kernel(Matrix A, Matrix B, Matrix C,
                    int start_row, int end_row) {
    /* Implement your access pattern here */
	int n = A.N;
	
	add_recursive(A, B, C, start_row, end_row, 0, n);	
}
/* ============================================================ */

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

    FILE *fp = fopen("../../reports/Q2_results/cache_oblivious.csv", "w");
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
                "../../reports/Q2_results/cache_oblivious.csv",
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
