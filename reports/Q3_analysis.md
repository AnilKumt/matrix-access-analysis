### Blocked Access (Single-threaded)

Blocked matrix multiplication improves cache locality by operating on
sub-matrices that fit into cache. As matrix size increases, blocked
access shows significantly better performance compared to naive
multiplication due to reduced cache misses and better data reuse.
Execution time increases rapidly with matrix size but remains lower
than non-blocked approaches.


### Row-Major-ijk order (Single-threaded)

Naive single-threaded matrix multiplication in row-major ijk order shows execution time increasing rapidly with matrix size. For small matrices, the overhead is negligible, but as size grows, cache misses dominate, leading to steep performance degradation. While straightforward, this approach suffers from poor cache locality, causing memory access to become the primary bottleneck for large matrices.


### Transpose-Based Access (Single-threaded)

Transpose-based matrix multiplication improves cache performance by accessing the second matrix in a row-major–friendly manner. By effectively converting column-wise access into sequential memory access, this approach significantly reduces cache misses compared to naive row-major ijk order. As matrix size increases, execution time still grows rapidly due to 𝑂(𝑁3) complexity, but remains consistently lower than standard row-major multiplication. While not as cache-efficient as blocked access, transpose-based access offers a clear performance improvement with minimal implementation overhead.

