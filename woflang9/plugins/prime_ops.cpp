// plugins/prime_ops.cpp — robust parse + deterministic 64-bit Miller–Rabin
#ifndef WOFLANG_PLUGIN_EXPORT
#  ifdef _WIN32
#    define WOFLANG_PLUGIN_EXPORT extern "C" __declspec(dllexport)
#  else
#    define WOFLANG_PLUGIN_EXPORT extern "C"
#  endif
#endif

#include "core/woflang.hpp"
#include <cstdint>
#include <stack>
#include <stdexcept>
#include <string>
#include <string_view>
#include <limits>
#include <charconv>

namespace woflang {

// ---------- parse helpers ----------
static inline bool parse_u64(std::string_view s, uint64_t& out) {
    while (!s.empty() && (s.front()==' '||s.front()=='\t'||s.front()=='\n'||s.front()=='\r')) s.remove_prefix(1);
    while (!s.empty() && (s.back() ==' '||s.back() =='\t'||s.back() =='\n'||s.back() =='\r')) s.remove_suffix(1);
    if (s.empty()) return false;
    if (s.front() == '+') s.remove_prefix(1);
    if (s.empty()) return false;

#if defined(__cpp_lib_to_chars) && __cpp_lib_to_chars >= 201611L
    const char* first = s.data();
    const char* last  = s.data() + s.size();
    uint64_t v = 0;
    auto res = std::from_chars(first, last, v, 10);
    if (res.ec != std::errc() || res.ptr != last) return false;
    out = v; return true;
#else
    uint64_t v = 0;
    for (char c : s) {
        if (c < '0' || c > '9') return false;
        uint64_t d = static_cast<uint64_t>(c - '0');
        if (v > (std::numeric_limits<uint64_t>::max() - d) / 10ULL) return false;
        v = v*10ULL + d;
    }
    out = v; return true;
#endif
}

static inline uint64_t as_u64(const WofValue& v, const char* op) {
    if (v.is_numeric()) {
        double d = v.as_numeric();
        if (!(d >= 0.0)) throw std::runtime_error(std::string(op)+": non-negative integer required");
        uint64_t u = static_cast<uint64_t>(d);
        if (static_cast<double>(u) != d)
            throw std::runtime_error(std::string(op)+": non-integer (pass as string)");
        return u;
    }
    try {
        std::string s = v.to_string();
        uint64_t u = 0;
        if (!parse_u64(s, u)) throw std::runtime_error(std::string(op)+": numeric required");
        return u;
    } catch (...) {
        throw std::runtime_error(std::string(op)+": numeric required");
    }
}

// ---------- 64-bit Miller–Rabin ----------
static inline uint64_t mulmod_u64(uint64_t a, uint64_t b, uint64_t m){
#if defined(__GNUC__) || defined(__clang__)
    // MinGW GCC/Clang on x64 support 128-bit integers — use them unconditionally here.
    __uint128_t z = ( (__uint128_t)a * (__uint128_t)b ) % m;
    return (uint64_t)z;
#elif defined(_MSC_VER) && defined(_M_X64)
    // Portable fallback for MSVC without __int128
    uint64_t res = 0;
    a %= m;
    while (b) {
        if (b & 1ULL) res = (res + a) % m;
        a = (a + a) % m;
        b >>= 1ULL;
    }
    return res;
#else
    // Last-resort portable path
    uint64_t res = 0;
    a %= m;
    while (b) {
        if (b & 1ULL) res = (res + a) % m;
        a = (a + a) % m;
        b >>= 1ULL;
    }
    return res;
#endif
}
static inline uint64_t powmod_u64(uint64_t a, uint64_t e, uint64_t m){
    uint64_t r = 1 % m;
    a %= m;
    while (e){
        if (e & 1ULL) r = mulmod_u64(r, a, m);
        a = mulmod_u64(a, a, m);
        e >>= 1ULL;
    }
    return r;
}
static bool mr_check(uint64_t n, uint64_t a, uint64_t d, uint64_t s){
    uint64_t x = powmod_u64(a % n, d, n);
    if (x == 1 || x == n - 1) return true;
    for (uint64_t r = 1; r < s; ++r) {
        x = mulmod_u64(x, x, n);
        if (x == n - 1) return true;
    }
    return false;
}
static bool is_prime_u64(uint64_t n){
    if (n < 2) return false;

    // quick trial division by small primes
    static const uint32_t smalls[] = {2,3,5,7,11,13,17,19,23,29,31,37};
    for (uint32_t p : smalls){
        if (n == p) return true;
        if (n % p == 0) return n == p;
    }

    // n-1 = d * 2^s
    uint64_t d = n - 1, s = 0; 
    while ((d & 1ULL) == 0){ d >>= 1ULL; ++s; }

    // Sinclair 7 bases (deterministic for 64-bit)
    static const uint64_t S7[] = {2ULL,325ULL,9375ULL,28178ULL,450775ULL,9780504ULL,1795265022ULL};
    for (uint64_t a : S7) if (!mr_check(n, a, d, s)) return false;

    // Extra classic small bases (cheap redundancy)
    static const uint64_t Sclassic[] = {2ULL,3ULL,5ULL,7ULL,11ULL,13ULL,17ULL,19ULL,23ULL,29ULL,31ULL,37ULL,41ULL};
    for (uint64_t a : Sclassic) if (!mr_check(n, a, d, s)) return false;

    return true;
}

} // namespace woflang

WOFLANG_PLUGIN_EXPORT void init_plugin(woflang::WoflangInterpreter::OpTable* ops){
    using namespace woflang;
    if (!ops) return;

    // Numeric version probe (so '.' always prints something)
    (*ops)["prime_version"] = [](std::stack<WofValue>& S){S.push(WofValue(6407.0));
     // arbitrary code so we can verify the right DLL
};

    (*ops)["prime_check"] = [](std::stack<WofValue>& S){
        if (S.empty()) throw std::runtime_error("prime_check: stack underflow");
        uint64_t n = as_u64(S.top(), "prime_check"); S.pop();
        S.push(WofValue(is_prime_u64(n) ? 1.0 : 0.0));
    };

    (*ops)["next_prime"] = [](std::stack<WofValue>& S){
        if (S.empty()) throw std::runtime_error("next_prime: stack underflow");
        uint64_t n = as_u64(S.top(), "next_prime"); S.pop();
        if (n <= 2) { S.push(WofValue(2.0)); return; }
        if ((n & 1ULL) == 0) ++n;
        while (!is_prime_u64(n)) n += 2ULL;
        S.push(WofValue(static_cast<double>(n)));
    };
}
