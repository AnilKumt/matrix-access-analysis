### IKJ Access (Multi-threaded)

IKJ access improves cache reuse by keeping A[i][k] in a register while
iterating over j. Performance scales well with threads up to an optimal
point, after which synchronization overhead and memory bandwidth limit
speedup. Larger matrices benefit more from increased thread counts.


### Cyclic Row Partitioning (Multi-threaded)

Cyclic row partition balances work by assigning matrix rows to threads in a round-robin fashion, keeping all cores busy and reducing idle time. Performance scales with thread count for larger matrices, but small matrices see little benefit because overhead dominates. As thread count increases, speedup eventually saturates due to memory bandwidth limits and synchronization overhead. Like, if number of threads are 3, 1st thread takes 1, 4, 7, ...

### KIJ Access (Multi-threaded)

KIJ multithreading improves cache locality compared to cyclic row partitioning by accessing matrix B sequentially while accumulating results, reducing cache misses. Compared to IKJ, KIJ offers similar reuse of A elements but typically achieves slightly lower performance due to less efficient reuse of C across threads. Performance scales with thread count for large matrices, but speedup saturates earlier than IKJ because memory bandwidth becomes the limiting factor. Overall, KIJ performs better than cyclic row partitioning but slightly worse than IKJ for large matrix sizes.

