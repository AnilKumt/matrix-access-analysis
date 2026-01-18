#include <stdio.h>
#include <stdlib.h>

#include "../../common/matrix_utils.h"
#include "../../common/timing.h"
#include "../../common/csv_utils.h"

/* ============================================================
   TODO: IMPLEMENT THIS FUNCTION ONLY
   ============================================================ */
void compute_kernel(Matrix A, Matrix B, Matrix C) {
    int N = A.cols;  // Assuming square matrices
    
    // Iterate through columns first (outer loop)
    for (int j = 0; j < N; j++) {
        // Then iterate through rows (inner loop)
        for (int i = 0; i < N; i++) {
            C.data[i * N + j] = A.data[i * N + j] + B.data[i * N + j];
        }
    }
   
}
/* ============================================================ */

int main() {

    int matrix_sizes[] = {256, 512, 1024, 2048};
    int num_sizes = 4;

    FILE *fp = fopen("../../reports/Q1_results/row_major.csv", "w");
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
            "../../reports/Q1_results/row_major.csv",
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

