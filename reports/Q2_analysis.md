### Diagonal Access (Multi-threaded)

Diagonal access was parallelized by distributing row ranges across threads.
Performance improved as thread count increased up to an optimal point,
after which overhead and cache contention reduced gains.
Larger matrices benefited more from higher thread counts, with optimal
performance typically observed between 4 and 8 threads.
