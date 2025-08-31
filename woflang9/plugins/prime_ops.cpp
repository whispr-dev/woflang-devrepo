// plugins/prime_ops.cpp
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

namespace woflang {

// --------- 64-bit deterministic Miller–Rabin ----------
static inline uint64_t mulmod_u64(uint64_t a, uint64_t b, uint64_t m){
#if defined(__SIZEOF_INT128__)
    __uint128_t z = ( (__uint128_t)a * b );
    return (uint64_t)(z % m);
#else
    uint64_t res = 0;
    while (b) {
        if (b & 1) { res = (res >= m - a) ? (res - (m - a)) : (res + a); }
        a = (a >= m - a) ? (a - (m - a)) : (a + a);
        b >>= 1;
    }
    return res;
#endif
}
static inline uint64_t powmod_u64(uint64_t a, uint64_t e, uint64_t m){
    uint64_t r = 1 % m;
    while (e){
        if (e & 1) r = mulmod_u64(r, a, m);
        a = mulmod_u64(a, a, m);
        e >>= 1;
    }
    return r;
}
static bool is_prime_u64(uint64_t n){
    if (n < 2) return false;
    static const uint64_t bases[] = {2,3,5,7,11,13,17,19,23,29,31,37};
    for (uint64_t p: bases){ if (n==p) return true; if (n%p==0) return n==p; }
    uint64_t d = n-1, s = 0; while ((d & 1)==0){ d >>= 1; ++s; }
    for (uint64_t a: bases){
        if (a % n == 0) continue;
        uint64_t x = powmod_u64(a, d, n);
        if (x == 1 || x == n-1) continue;
        bool ok = false;
        for (uint64_t r=1; r<s; ++r){
            x = mulmod_u64(x, x, n);
            if (x == n-1){ ok = true; break; }
        }
        if (!ok) return false;
    }
    return true;
}

static inline uint64_t need_u64(const WofValue& v, const char* op){
    if (!v.is_numeric()) throw std::runtime_error(std::string(op)+": numeric required");
    double d = v.as_numeric();
    if (!(d >= 0.0)) throw std::runtime_error(std::string(op)+": non-negative integer required");
    uint64_t u = static_cast<uint64_t>(d);
    if (static_cast<double>(u) != d) throw std::runtime_error(std::string(op)+": non-integer");
    return u;
}

} // namespace woflang

WOFLANG_PLUGIN_EXPORT void init_plugin(woflang::WoflangInterpreter::OpTable* ops){
    using namespace woflang;
    if (!ops) return;

    (*ops)["prime_check"] = [](std::stack<WofValue>& S){
        if (S.size() < 1) throw std::runtime_error("prime_check: stack underflow");
        uint64_t n = need_u64(S.top(), "prime_check"); S.pop();
        S.push(WofValue(is_prime_u64(n) ? 1.0 : 0.0));
    };

    (*ops)["next_prime"] = [](std::stack<WofValue>& S){
        if (S.size() < 1) throw std::runtime_error("next_prime: stack underflow");
        uint64_t n = need_u64(S.top(), "next_prime"); S.pop();
        if (n <= 2) { S.push(WofValue(2.0)); return; }
        if ((n & 1ULL) == 0) ++n;
        while (!is_prime_u64(n)) n += 2;
        S.push(WofValue(static_cast<double>(n)));
    };
}
