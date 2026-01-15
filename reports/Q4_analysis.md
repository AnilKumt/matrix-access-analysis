### IKJ Access (Multi-threaded)

IKJ access improves cache reuse by keeping A[i][k] in a register while
iterating over j. Performance scales well with threads up to an optimal
point, after which synchronization overhead and memory bandwidth limit
speedup. Larger matrices benefit more from increased thread counts.


### Cyclic Row Partitioning (Multi-threaded)

Cyclic row partition balances work by assigning matrix rows to threads in a round-robin fashion, keeping all cores busy and reducing idle time. Performance scales with thread count for larger matrices, but small matrices see little benefit because overhead dominates. As thread count increases, speedup eventually saturates due to memory bandwidth limits and synchronization overhead.
