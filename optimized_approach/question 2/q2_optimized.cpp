#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <pthread.h>
#include <sched.h>

#include "../../common/matrix_utils.h"
#include "../../common/timing.h"
#include "../../common/csv_utils.h"
#include "../../common/resource_utils.h"
#include "../../common/task_utils.h"

void worker_add(Matrix A, Matrix B, Matrix C, Task t) {
    for (int i = t.r0; i < t.r1; i++)
        for (int j = t.c0; j < t.c1; j++)
            C.data[i][j] = A.data[i][j] + B.data[i][j];
}

// void compute_kernel(Matrix A, Matrix B, Matrix C) {
//     int N = A.N;
//     int max_threads = get_num_cores();
//     int Bsize = compute_block_size(N);

//     auto tasks = create_block_tasks(N, Bsize);
//     std::vector<std::thread> pool;

//     for (auto &task : tasks) {
//         if ((int)pool.size() == max_threads) {
//             for (auto &t : pool) t.join();
//             pool.clear();
//         }
//         pool.emplace_back(worker_add, A, B, C, task);
//     }
//     for (auto &t : pool) t.join();
// }


void compute_kernel(Matrix A, Matrix B, Matrix C) {
    int N = A.N;
    int max_threads = get_num_cores();
    int Bsize = compute_block_size(N);

    auto tasks = create_block_tasks(N, Bsize);
    std::vector<std::thread> pool;

    for (auto &task : tasks) {
        if ((int)pool.size() == max_threads) {
            for (auto &t : pool) t.join();
            pool.clear();
        }

        std::thread th(worker_add, A, B, C, task);

        struct sched_param param;
        param.sched_priority = 1;

        pthread_setschedparam(
            th.native_handle(),
            SCHED_BATCH,
            &param
        );

        pool.push_back(std::move(th));
    }

    for (auto &t : pool)
        t.join();
}


int main() {
    int matrix_sizes[] = {256, 512, 1024, 2048};

    FILE *fp = fopen("../../reports/Q2_results/optimized.csv", "w");
    fprintf(fp, "matrix_size,threads,time_seconds\n");
    fclose(fp);

    int threads = get_num_cores();

    for (int s = 0; s < 4; s++) {
        int N = matrix_sizes[s];

        Matrix A = allocate_matrix(N);
        Matrix B = allocate_matrix(N);
        Matrix C = allocate_matrix(N);

        init_matrix(A);
        init_matrix(B);
        zero_matrix(C);

        start_timer();
        compute_kernel(A, B, C);
        double t = stop_timer();

        write_csv("../../reports/Q2_results/optimized.csv", N, threads, t);

        free_matrix(A);
        free_matrix(B);
        free_matrix(C);
    }
    return 0;
}

