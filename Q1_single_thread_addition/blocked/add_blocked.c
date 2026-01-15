#include <stdio.h>
#include <stdlib.h>

#include "../../common/matrix_utils.h"
#include "../../common/timing.h"
#include "../../common/csv_utils.h"

#define BLOCK_SIZE 32

/* ============================================================
   TODO: IMPLEMENT THIS FUNCTION ONLY
   ============================================================ */
void compute_kernel(Matrix A, Matrix B, Matrix C) {
    /* Implement your access pattern here */
	int n = A.N;

	int bsize = BLOCK_SIZE;
	
	for(int x = 0; x < n; x += bsize) {
		for(int y = 0; y < n; y += bsize) {
			int x_max = (x + bsize < n) ? x + bsize : n;
			int y_max = (y + bsize < n) ? y + bsize : n;

			for(int i = x; i < x_max; i++) {
				for(int j = y; j < y_max; j++) {
					C.data[i][j] = A.data[i][j] + B.data[i][j];
				}
			}
		}
	}
}
/* ============================================================ */

int main() {

    int matrix_sizes[] = {256, 512, 1024, 2048};
    int num_sizes = 4;

    FILE *fp = fopen("../../reports/Q1_results/blocked.csv", "w");
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
            "../../reports/Q1_results/blocked.csv",
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
