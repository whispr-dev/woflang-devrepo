// plugins/prime_ops.cpp
//
// Deterministic 64-bit Miller–Rabin + next_prime for woflang.
// Exposes ops:
//   - prime_check   ( n -- 1|0 )  : pushes 1 if n is prime, else 0
//   - next_prime    ( n -- p )    : pushes the smallest prime >= n+1 (i.e., next after n)
//   - prime_version ( -- v )      : pushes an integer version marker
//
// Compatible with the plugin loader signature: init_plugin(OpTable*).

#include <cstdint>
#include <stack>
#include <stdexcept>
#include <string>
#include <limits>
#include <type_traits>
#include <cctype>
#include <vector>
#include <cmath>

#include "src/core/woflang.hpp"   // included via -I.../src and -I.../src/core

namespace woflang {

// ---------- helpers to read/write WofValue ----------
static uint64_t to_u64_throw(const WofValue& v, const char* op_name) {
    switch (v.type) {
        case WofType::Integer: {
            int64_t x = std::get<int64_t>(v.value);
            if (x < 0) throw std::runtime_error(std::string(op_name) + ": nonnegative integer required");
            return static_cast<uint64_t>(x);
        }
        case WofType::Double: {
            double d = std::get<double>(v.value);
            if (!(d >= 0.0) || d > static_cast<double>(std::numeric_limits<uint64_t>::max()))
                throw std::runtime_error(std::string(op_name) + ": numeric out of range");
            // Accept only integral doubles to avoid surprises
            double ip;
            if (std::modf(d, &ip) != 0.0)
                throw std::runtime_error(std::string(op_name) + ": integer required");
            return static_cast<uint64_t>(d);
        }
        case WofType::String:
        case WofType::Symbol: {
            const std::string& s = std::get<std::string>(v.value);
            if (s.empty()) throw std::runtime_error(std::string(op_name) + ": empty string");
            size_t i = 0;
            while (i < s.size() && std::isspace(static_cast<unsigned char>(s[i]))) ++i;
            if (i >= s.size() || s[i] == '-') throw std::runtime_error(std::string(op_name) + ": nonnegative integer required");
            uint64_t val = 0;
            for (; i < s.size(); ++i) {
                char c = s[i];
                if (std::isspace(static_cast<unsigned char>(c))) break;
                if (c < '0' || c > '9') throw std::runtime_error(std::string(op_name) + ": integer required");
                uint64_t d = static_cast<uint64_t>(c - '0');
                if (val > (std::numeric_limits<uint64_t>::max() - d) / 10ULL)
                    throw std::runtime_error(std::string(op_name) + ": integer overflow");
                val = val * 10ULL + d;
            }
            return val;
        }
        default:
            throw std::runtime_error(std::string(op_name) + ": numeric required");
    }
}

static void push_bool(std::stack<WofValue>& st, bool b) {
    // push as Integer 1/0 for stable printing/expectations
    st.emplace(static_cast<int64_t>(b ? 1 : 0), WofType::Integer);
}

static void push_u64(std::stack<WofValue>& st, uint64_t x) {
    if (x <= static_cast<uint64_t>(std::numeric_limits<int64_t>::max())) {
        st.emplace(static_cast<int64_t>(x), WofType::Integer);
    } else {
        // very large—represent as double exactly up to 2^53, but for our use in next_prime it’s fine
        st.emplace(static_cast<double>(x), WofType::Double);
    }
}

// ---------- 64-bit safe arithmetic ----------
static inline uint64_t mulmod_u64(uint64_t a, uint64_t b, uint64_t m) {
#if defined(__SIZEOF_INT128__)
    return static_cast<uint64_t>((__uint128_t)a * b % m);
#else
    // Fallback: double-based trick (safe enough here because m < 2^64 and we just need correctness).
    // But to be robust, do classic add-doubling to avoid overflow.
    uint64_t res = 0;
    while (b) {
        if (b & 1ULL) {
            uint64_t t = a >= m - res ? a - (m - res) : a + res;
            res = (res + a) % m; // keep within range
            res = t % m;
        }
        a = (a >= m - a) ? a - (m - a) : a + a;
        a %= m;
        b >>= 1ULL;
    }
    return res % m;
#endif
}

static inline uint64_t powmod_u64(uint64_t a, uint64_t e, uint64_t m) {
    uint64_t r = 1 % m;
    uint64_t x = a % m;
    while (e) {
        if (e & 1ULL) r = mulmod_u64(r, x, m);
        x = mulmod_u64(x, x, m);
        e >>= 1ULL;
    }
    return r;
}

// ---------- Miller–Rabin (deterministic for 64-bit) ----------
static bool mr_round(uint64_t n, uint64_t d, unsigned s, uint64_t a) {
    if (a % n == 0) return true; // base divisible by n: treat as passing this round
    uint64_t x = powmod_u64(a, d, n);
    if (x == 1ULL || x == (n - 1)) return true;
    for (unsigned r = 1; r < s; ++r) {
        x = mulmod_u64(x, x, n);
        if (x == (n - 1)) return true;
    }
    return false; // 'a' is a witness => composite
}

static bool is_prime_u64(uint64_t n) {
    if (n < 2) return false;
    // small primes quick path
    static const uint32_t smalls[] = {2,3,5,7,11,13,17,19,23,29,31};
    for (uint32_t p : smalls) {
        if (n == p) return true;
        if (n % p == 0) return (n == p);
    }
    // write n-1 = d * 2^s with d odd
    uint64_t d = n - 1;
    unsigned s = 0;
    while ((d & 1ULL) == 0) { d >>= 1ULL; ++s; }

    // Deterministic 64-bit bases:
    // See Jim Sinclair / CP-algorithms: {2, 3, 5, 7, 11, 13, 17} works up to < 341,550,071,728,321.
    // For full 64-bit correctness use the "S7" set below.
    static const uint64_t bases[] = {
        2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL
    };

    for (uint64_t a : bases) {
        if (!mr_round(n, d, s, a)) return false;
    }
    return true;
}

// ---------- wof ops ----------
static void op_prime_check(std::stack<WofValue>& st) {
    if (st.empty()) throw std::runtime_error("prime_check: need one argument");
    WofValue v = st.top(); st.pop();
    uint64_t n = to_u64_throw(v, "prime_check");
    push_bool(st, is_prime_u64(n));
}

static uint64_t next_prime_u64(uint64_t n) {
    if (n <= 2) return 2ULL;
    uint64_t c = n + 1;
    if ((c & 1ULL) == 0) ++c;
    while (true) {
        if (is_prime_u64(c)) return c;
        c += 2;
    }
}

static void op_next_prime(std::stack<WofValue>& st) {
    if (st.empty()) throw std::runtime_error("next_prime: need one argument");
    WofValue v = st.top(); st.pop();
    uint64_t n = to_u64_throw(v, "next_prime");
    uint64_t p = next_prime_u64(n);
    push_u64(st, p);
}

static void op_prime_version(std::stack<WofValue>& st) {
    // bump this if you tweak the algorithm so you can sanity-check that the right DLL is loaded
    st.emplace(static_cast<int64_t>(7003), WofType::Integer);
}

} // namespace woflang

// ---- plugin entrypoint ----
extern "C"
#ifdef _WIN32
__declspec(dllexport)
#endif
void init_plugin(woflang::WoflangInterpreter::OpTable* op_table) {
    using namespace woflang;
    if (!op_table) return;
    (*op_table)["prime_check"]    = [](std::stack<WofValue>& st){ op_prime_check(st); };
    (*op_table)["next_prime"]     = [](std::stack<WofValue>& st){ op_next_prime(st); };
    (*op_table)["prime_version"]  = [](std::stack<WofValue>& st){ op_prime_version(st); };
}
