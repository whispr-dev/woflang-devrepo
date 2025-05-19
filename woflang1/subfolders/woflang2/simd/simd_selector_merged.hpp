// simd_selector.hpp
#pragma once

#include <vector>
#include <string>
#include "simd_avx2_module.hpp"
// #include "simd_avx512_module.hpp" // Future support
// #include "simd_neon_module.hpp"    // Future support
// #include "simd_fallback.hpp"       // Optional fallback

#if defined(_MSC_VER)
#include <intrin.h>
#else
#include <cpuid.h>
#endif

struct SIMDSelector {
    static std::vector<size_t> parse(const std::string& str) {
        if (isAVX2Supported()) {
            return parseJsonSIMD_AVX2(str);
        } /* else if (isAVX512Supported()) {
            return parseJsonSIMD_AVX512(str);
        } else if (isNEONSupported()) {
            return parseJsonSIMD_NEON(str);
        } else {
            return parseJsonFallback(str);
        } */
        return {};  // No SIMD path supported
    }

    static bool isAVX2Supported() {
#if defined(__GNUC__) || defined(__clang__)
        unsigned int eax, ebx, ecx, edx;
        __cpuid(0, eax, ebx, ecx, edx);
        if (eax >= 7) {
            __cpuid_count(7, 0, eax, ebx, ecx, edx);
            return (ebx & (1 << 5)) != 0;  // AVX2 bit
        }
        return false;
#elif defined(_MSC_VER)
        int info[4];
        __cpuid(info, 0);
        if (info[0] >= 7) {
            __cpuidex(info, 7, 0);
            return (info[1] & (1 << 5)) != 0;  // AVX2
        }
        return false;
#else
        return false;
#endif
    }

    static bool isNEONSupported() {
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
        return true;
#else
        return false;
#endif
    }
};