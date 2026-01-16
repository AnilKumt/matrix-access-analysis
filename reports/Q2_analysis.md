### Diagonal Access (Multi-threaded)

Diagonal access was parallelized by distributing row ranges across threads.
Performance improved as thread count increased up to an optimal point,
after which overhead and cache contention reduced gains.
Larger matrices benefited more from higher thread counts, with optimal
performance typically observed between 4 and 8 threads.


### Transposed Access (Multi-threaded)

Transposed access was parallelized by distributing column ranges across threads.
Performance improved as thread count increased up to an optimal point, after which overhead and cache contention reduced gains.
Smaller matrices benefited little from more than 2–4 threads, while larger matrices saw greater speedups, with optimal performance typically observed between 4 and 8 threads.
These access method assumes the matrix is stored in column wise, which then transposes the matrix to perform the operations.

