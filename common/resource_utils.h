#ifndef RESOURCE_UTILS_H
#define RESOURCE_UTILS_H

#include <thread>
#include <cmath>

inline int get_num_cores() {
    unsigned int cores = std::thread::hardware_concurrency();
    return (cores == 0) ? 4 : cores;
}

/*
  Goal:
  - Create ~4× more tasks than cores (good load balance)
  - Ensure blocks are cache-friendly
*/
inline int compute_block_size(int N) {
    int cores = get_num_cores();

    int target_tasks = cores * 1;     // coarse granularity
    // int blocks_per_dim = std::sqrt(target_tasks);
    int blocks_per_dim = target_tasks;

    if(N >= 1024){
        blocks_per_dim = std::cbrt(blocks_per_dim);
    }

    int B = N / blocks_per_dim;

    // Clamp block size
    if (B < 128) B = 128;
    if (B > 480) B = 480;

    return B;
}

#endif
