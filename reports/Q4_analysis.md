### IKJ Access (Multi-threaded)

IKJ access improves cache reuse by keeping A[i][k] in a register while
iterating over j. Performance scales well with threads up to an optimal
point, after which synchronization overhead and memory bandwidth limit
speedup. Larger matrices benefit more from increased thread counts.
