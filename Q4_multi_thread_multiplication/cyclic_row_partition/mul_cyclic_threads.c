#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "../../common/matrix_utils.h"
#include "../../common/timing.h"
// #include "../../common/thread_utils.h"
#include "../../common/csv_utils.h"

// Thread argument structure
typedef struct {
    int thread_id;   // The ID of this thread
    int num_threads; // Total number of threads
    Matrix *A;
    Matrix *B;
    Matrix *C;
} thread_arg_t;

/* ============================================================
   Compute kernel using cyclic row partitioning
   Each thread computes every num_threads-th row starting from its thread_id
   ============================================================ */
void compute_kernel(Matrix A, Matrix B, Matrix C,
                    int thread_id, int num_threads) {
    int N = A.N;

    for (int i = thread_id; i < N; i += num_threads) { // cyclic row assignment
        for (int j = 0; j < N; j++) {
            double sum = 0.0;
            for (int k = 0; k < N; k++) {
                sum += A.data[i][k] * B.data[k][j];
            }
            C.data[i][j] = sum;
        }
    }
}
/* ============================================================ */

void* thread_entry(void *arg) {
    thread_arg_t *t = (thread_arg_t*)arg;
    compute_kernel(
        *(t->A),
        *(t->B),
        *(t->C),
        t->thread_id,
        t->num_threads
    );
    return NULL;
}

int main() {

    int matrix_sizes[] = {256, 512, 1024, 2048};
    int num_sizes = 4;
    int thread_counts[] = {1, 2, 4, 8, 16};
    int num_threads = 5;

    FILE *fp = fopen("../../reports/Q4_results/cyclic_row_partition.csv", "w");
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

            start_timer();

            for (int i = 0; i < T; i++) {
                args[i].thread_id = i;
                args[i].num_threads = T;
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
                "../../reports/Q4_results/cyclic_row_partition.csv",
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

