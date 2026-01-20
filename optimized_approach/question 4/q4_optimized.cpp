#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <vector>

#include "../../common/matrix_utils.h"
#include "../../common/timing.h"
#include "../../common/csv_utils.h"
#include "../../common/resource_utils.h"
#include "../../common/task_utils.h"

/* ===================== WORKER ===================== */

void worker_mul(Matrix A, Matrix B, Matrix C, Task t) {
    int N = A.N;
    int Bsize = t.r1 - t.r0;

    for (int kk = 0; kk < N; kk += Bsize)
        for (int i = t.r0; i < t.r1; i++)
            for (int j = t.c0; j < t.c1; j++)
                for (int k = kk; k < kk + Bsize && k < N; k++)
                    C.data[i][j] += A.data[i][k] * B.data[k][j];
}

/* ===================== KERNEL ===================== */

void compute_kernel(Matrix A, Matrix B, Matrix C) {
    int N = A.N;

    int max_threads = get_num_cores();
    int Bsize = compute_block_size(N);

    auto tasks = create_block_tasks(N, Bsize);
    std::vector<std::thread> pool;

    for (auto &task : tasks) {
        if ((int)pool.size() == max_threads) {
            for (auto &t : pool)
                t.join();
            pool.clear();
        }
        pool.emplace_back(worker_mul, A, B, C, task);
    }

    for (auto &t : pool)
        t.join();
}

/* ===================== MAIN ===================== */

int main() {

    int matrix_sizes[] = {256, 512, 1024, 2048};
    int num_sizes = 4;

    int threads = get_num_cores();

    FILE *fp = fopen("../../reports/Q4_results/optimized.csv", "w");
    fprintf(fp, "matrix_size,threads,time_seconds\n");
    fclose(fp);

    for (int s = 0; s < num_sizes; s++) {
        int N = matrix_sizes[s];

        Matrix A = allocate_matrix(N);
        Matrix B = allocate_matrix(N);
        Matrix C = allocate_matrix(N);

        init_matrix(A);
        init_matrix(B);
        zero_matrix(C);

        start_timer();
        compute_kernel(A, B, C);
        double time_taken = stop_timer();

        write_csv(
            "../../reports/Q4_results/optimized.csv",
            N,
            threads,
            time_taken
        );

        free_matrix(A);
        free_matrix(B);
        free_matrix(C);
    }

    return 0;
}

