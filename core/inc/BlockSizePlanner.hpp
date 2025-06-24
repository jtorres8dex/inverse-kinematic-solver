#pragma once
#include <cstddef>
#include <algorithm>
#include "SystemInfo.hpp"

class BlockSizePlanner {
public:
    static size_t getOptimalBlockSize(const CacheSizes& cache) {
        // Assume:
        // - 3 matrices involved (A, B, C)
        // - Each uses blocks of size BxB doubles
        // - Each double is 8 bytes
        // - Fit all 3 blocks in L1 cache to avoid eviction

        constexpr size_t bytes_per_double = sizeof(double);
        size_t l1_bytes = cache.L1;

        // 3 * B^2 * sizeof(double) <= L1
        size_t max_block_bytes = l1_bytes / 3;
        size_t B = static_cast<size_t>(std::sqrt(max_block_bytes / bytes_per_double));

        // Round down to nearest multiple of 4 or 8 for better alignment
        return B - (B % 8);
    }
};