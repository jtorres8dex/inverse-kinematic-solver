#include "SystemInfo.hpp"

#if defined(__APPLE__)
#include <sys/sysctl.h>
CacheSizes SystemInfo::getCacheSizes() {
    CacheSizes sizes;
    size_t size = 0;
    size_t len = sizeof(size);

    sysctlbyname("hw.l1dcachesize", &size, &len, nullptr, 0);
    sizes.L1 = size;

    sysctlbyname("hw.l2cachesize", &size, &len, nullptr, 0);
    sizes.L2 = size;

    if (sysctlbyname("hw.l3cachesize", &size, &len, nullptr, 0) == 0)
        sizes.L3 = size;
    else
        sizes.L3 = 0; // Apple M-series doesn't expose L3

    return sizes;
}
#elif defined(_WIN32)
#include <windows.h>
CacheSizes SystemInfo::getCacheSizes() {
    CacheSizes sizes;
    DWORD len = 0;
    GetLogicalProcessorInformation(nullptr, &len);
    std::vector<uint8_t> buffer(len);
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION* info =
        reinterpret_cast<SYSTEM_LOGICAL_PROCESSOR_INFORMATION*>(buffer.data());
    GetLogicalProcessorInformation(info, &len);

    for (DWORD i = 0; i < len / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION); ++i) {
        if (info[i].Relationship == RelationCache) {
            const auto& cache = info[i].Cache;
            if (cache.Level == 1) sizes.L1 = cache.Size;
            else if (cache.Level == 2) sizes.L2 = cache.Size;
            else if (cache.Level == 3) sizes.L3 = cache.Size;
        }
    }
    return sizes;
}
#else // Linux
#include <fstream>
CacheSizes SystemInfo::getCacheSizes() {
    CacheSizes sizes;
    std::ifstream f;

    auto read = [](const std::string& path) -> size_t {
        std::ifstream file(path);
        size_t val = 0;
        file >> val;
        return val * 1024; // kB to bytes
    };

    try {
        sizes.L1 = read("/sys/devices/system/cpu/cpu0/cache/index0/size");
        sizes.L2 = read("/sys/devices/system/cpu/cpu0/cache/index1/size");
        sizes.L3 = read("/sys/devices/system/cpu/cpu0/cache/index2/size");
    } catch (...) {}

    return sizes;
}
#endif