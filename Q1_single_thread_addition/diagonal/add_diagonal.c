#include <stdio.h>
#include <stdlib.h>

#include "../../common/matrix_utils.h"
#include "../../common/timing.h"
#include "../../common/csv_utils.h"


void compute_kernel(Matrix A, Matrix B, Matrix C) {
    int n = A.N;

    for (int d = 0; d <= 2 * (n - 1); d++) {

        int i_start, i_end;

        if (d < n) {
            i_start = d;
            i_end = 0;
        } else {
            i_start = n - 1;
            i_end = d - (n - 1);
        }

        for (int i = i_start; i >= i_end; i--) {
            int j = d - i;
            C.data[i][j] = A.data[i][j] + B.data[i][j];
        }
    }
}


int main() {

    int matrix_sizes[] = {256, 512, 1024, 2048};
    int num_sizes = 4;

    FILE *fp = fopen("../../reports/Q1_results/diagonal.csv", "w");
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
            "../../reports/Q1_results/diagonal.csv",
            N,
            1,
            time_taken
        );

        free_matrix(A);
        free_matrix(B);
        free_matrix(C);
    }

    return 0;
}

