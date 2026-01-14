### Zigzag Access

Zigzag access traverses the matrix along diagonals, alternating direction.
As matrix size increases, execution time grows faster than row-major access
due to poor spatial locality and increased cache misses.
Performance degradation becomes more visible for large matrices.
