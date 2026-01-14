### Blocked Access (Single-threaded)

Blocked matrix multiplication improves cache locality by operating on
sub-matrices that fit into cache. As matrix size increases, blocked
access shows significantly better performance compared to naive
multiplication due to reduced cache misses and better data reuse.
Execution time increases rapidly with matrix size but remains lower
than non-blocked approaches.
