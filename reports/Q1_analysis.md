### Zigzag Access

Zigzag access traverses the matrix along diagonals, alternating direction.
As matrix size increases, execution time grows faster than row-major access
due to poor spatial locality and increased cache misses.
Performance degradation becomes more visible for large matrices.


### Blocked Access

Blocked access splits the matrix into smaller submatrices (blocks) to improve cache utilization.
For single-threaded execution, computation still proceeds sequentially within each block.
As matrix size increases, execution time grows roughly proportionally to the number of elements, but blocking slightly improves cache reuse compared to naive row-major access.
Performance scales reasonably well for small matrices, but larger matrices eventually exceed cache capacity, causing more memory traffic and slowing execution.
Block Size is taken as 32, which can be found using ```getconf LEVEL1_DCACHE_LINESIZE```, which is system specific.


### Diagonal Access

Diagonal access traverses the matrix along anti-diagonals, resulting in non-contiguous memory accesses in row-major storage. Compared to row-major access, this pattern exhibits poorer spatial locality and higher cache miss rates. As matrix size increases, execution time grows faster than row-major due to inefficient cache utilization, with performance degradation becoming more evident for larger matrices.
