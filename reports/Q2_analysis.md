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


### Cache-Oblivious Recursive (Multi-threaded)

This access takes advantage of the recursive and different sizes of caches, divides the problem in smaller problems. Looks like blocked access but differs slightly. In blocked access, the blocks are fixed size for an implementation, but this one divides the matrix, like 128x128 to 64x64 to 32x32, which has different sizes which can be fit in different caches.
Since the method is also done on multi-threads, this can potentially offer a better speedup than the naive method. The term cache-oblivious is used since the problem is divided
till the problem fits the cache line.
