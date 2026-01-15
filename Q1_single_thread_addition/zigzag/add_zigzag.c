#include <stdio.h>
#include <stdlib.h>

#include "../../common/matrix_utils.h"
#include "../../common/timing.h"
#include "../../common/csv_utils.h"

void compute_kernel(Matrix A, Matrix B, Matrix C) {
    int N = A.N;

    for (int d = 0; d < 2 * N - 1; d++) {
        if (d % 2 == 0) {
            int r = (d < N) ? d : N - 1;
            int c = d - r;
            while (r >= 0 && c < N) {
                C.data[r][c] = A.data[r][c] + B.data[r][c];
                r--;
                c++;
            }
        } else {
            int c = (d < N) ? d : N - 1;
            int r = d - c;
            while (c >= 0 && r < N) {
                C.data[r][c] = A.data[r][c] + B.data[r][c];
                r++;
                c--;
            }
        }
    }
}

int main() {
    int matrix_sizes[] = {256, 512, 1024, 2048};
    int num_sizes = 4;

    FILE *fp = fopen("../../reports/Q1_results/zigzag.csv", "w");
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

        write_csv("../../reports/Q1_results/zigzag.csv", N, 1, time_taken);

        free_matrix(A);
        free_matrix(B);
        free_matrix(C);
    }

    return 0;
}
