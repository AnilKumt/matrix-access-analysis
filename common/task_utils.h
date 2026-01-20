#ifndef TASK_UTILS_H
#define TASK_UTILS_H

#include <vector>
#include <algorithm>
#include "task.h"

inline std::vector<Task> create_block_tasks(int N, int B) {
    std::vector<Task> tasks;

    for (int i = 0; i < N; i += B)
        for (int j = 0; j < N; j += B)
            tasks.push_back({
                i,
                std::min(i + B, N),
                j,
                std::min(j + B, N)
            });

    return tasks;
}

#endif
