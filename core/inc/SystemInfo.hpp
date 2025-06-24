#pragma once
#include <cstddef>
#include <iostream>

struct CacheSizes {
    size_t L1 = 32 * 1024;       // Default fallbacks
    size_t L2 = 256 * 1024;
    size_t L3 = 8 * 1024 * 1024;

    void print() const {
        std::cout << "L1 Cache: " << L1 << " bytes\n";
        std::cout << "L2 Cache: " << L2 << " bytes\n";
        std::cout << "L3 Cache: " << L3 << " bytes\n";
    }
};

class SystemInfo {
public:
    static CacheSizes getCacheSizes();
};