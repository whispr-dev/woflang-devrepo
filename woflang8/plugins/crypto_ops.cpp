// ==================================================
// crypto_ops.cpp - BLAZING FAST Cryptographic Operations
// ==================================================
#include "../../src/core/woflang.hpp"
#include <cmath>
#include <random>
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

extern "C" {

// Fast modular exponentiation: (base^exp) % mod
uint64_t mod_pow(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) {
            result = (__uint128_t)result * base % mod;
        }
        base = (__uint128_t)base * base % mod;
        exp >>= 1;
    }
    return result;
}

// Miller-Rabin primality test - BLAZING FAST! 🚀
bool miller_rabin(uint64_t n, int k = 10) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    
    // Write n-1 as d * 2^r
    uint64_t d = n - 1;
    int r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }
    
    // Use deterministic witnesses for numbers up to certain bounds
    std::vector<uint64_t> witnesses;
    if (n < 2047) {
        witnesses = {2};
    } else if (n < 1373653) {
        witnesses = {2, 3};
    } else if (n < 9080191) {
        witnesses = {31, 73};
    } else if (n < 25326001) {
        witnesses = {2, 3, 5};
    } else if (n < 3215031751ULL) {
        witnesses = {2, 3, 5, 7};
    } else if (n < 4759123141ULL) {
        witnesses = {2, 7, 61};
    } else if (n < 1122004669633ULL) {
        witnesses = {2, 13, 23, 1662803};
    } else if (n < 2152302898747ULL) {
        witnesses = {2, 3, 5, 7, 11};
    } else if (n < 3474749660383ULL) {
        witnesses = {2, 3, 5, 7, 11, 13};
    } else if (n < 341550071728321ULL) {
        witnesses = {2, 3, 5, 7, 11, 13, 17};
    } else {
        // For very large numbers, use random witnesses
        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_int_distribution<uint64_t> dis(2, n - 2);
        witnesses.resize(k);
        for (int i = 0; i < k; i++) {
            witnesses[i] = dis(gen);
        }
    }
    
    // Miller-Rabin test
    for (uint64_t a : witnesses) {
        if (a >= n) continue;
        
        uint64_t x = mod_pow(a, d, n);
        if (x == 1 || x == n - 1) continue;
        
        bool composite = true;
        for (int i = 0; i < r - 1; i++) {
            x = (__uint128_t)x * x % n;
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        
        if (composite) return false;
    }
    
    return true;
}

// Optimized trial division for small numbers
bool trial_division_fast(uint64_t n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    // Check divisors of form 6k ± 1 up to √n
    for (uint64_t i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

// Hybrid approach: trial division for small numbers, Miller-Rabin for large
bool is_prime_blazing_fast(uint64_t n) {
    if (n < 1000000) {
        // Use trial division for small numbers (faster due to less overhead)
        return trial_division_fast(n);
    } else {
        // Use Miller-Rabin for large numbers (much faster asymptotically)
        return miller_rabin(n);
    }
}

// Fermat primality test (faster but less accurate)
bool fermat_test(uint64_t n, int k = 5) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dis(2, n - 2);
    
    for (int i = 0; i < k; i++) {
        uint64_t a = dis(gen);
        if (mod_pow(a, n - 1, n) != 1) {
            return false;
        }
    }
    return true;
}

// Solovay-Strassen primality test
int jacobi_symbol(uint64_t a, uint64_t n) {
    if (a == 0) return 0;
    if (a == 1) return 1;
    
    int result = 1;
    if (a < 0) {
        a = -a;
        if (n % 4 == 3) result = -result;
    }
    
    while (a != 0) {
        while (a % 2 == 0) {
            a /= 2;
            if (n % 8 == 3 || n % 8 == 5) result = -result;
        }
        std::swap(a, n);
        if (a % 4 == 3 && n % 4 == 3) result = -result;
        a %= n;
    }
    
    return (n == 1) ? result : 0;
}

bool solovay_strassen(uint64_t n, int k = 5) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dis(2, n - 1);
    
    for (int i = 0; i < k; i++) {
        uint64_t a = dis(gen);
        int jacobi = jacobi_symbol(a, n);
        if (jacobi == 0) return false;
        
        uint64_t mod_result = mod_pow(a, (n - 1) / 2, n);
        if (jacobi < 0) jacobi = n + jacobi;
        
        if (mod_result != jacobi) return false;
    }
    return true;
}

void init_plugin(woflang::WoflangInterpreter::OpTable* op_table) {
    // BLAZING FAST prime check - uses Miller-Rabin for large numbers
    (*op_table)["prime_check"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.empty()) {
            throw std::runtime_error("Stack underflow on prime_check");
        }
        auto a = stack.top(); stack.pop();
        
        uint64_t n = static_cast<uint64_t>(a.d);
        bool result = is_prime_blazing_fast(n);
        
        woflang::WofValue res;
        res.d = result ? 1.0 : 0.0;
        stack.push(res);
    };
    
    // Ultra-fast prime check using Fermat test (less accurate but LIGHTNING fast)
    (*op_table)["prime_check_ultra"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.empty()) {
            throw std::runtime_error("Stack underflow on prime_check_ultra");
        }
        auto a = stack.top(); stack.pop();
        
        uint64_t n = static_cast<uint64_t>(a.d);
        bool result = fermat_test(n);
        
        woflang::WofValue res;
        res.d = result ? 1.0 : 0.0;
        stack.push(res);
    };
    
    // Miller-Rabin with custom number of rounds
    (*op_table)["miller_rabin"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.size() < 2) {
            throw std::runtime_error("Stack underflow on miller_rabin (need number and rounds)");
        }
        auto rounds = stack.top(); stack.pop();
        auto a = stack.top(); stack.pop();
        
        uint64_t n = static_cast<uint64_t>(a.d);
        int k = static_cast<int>(rounds.d);
        bool result = miller_rabin(n, k);
        
        woflang::WofValue res;
        res.d = result ? 1.0 : 0.0;
        stack.push(res);
    };
    
    // Solovay-Strassen test
    (*op_table)["solovay_strassen"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.size() < 2) {
            throw std::runtime_error("Stack underflow on solovay_strassen (need number and rounds)");
        }
        auto rounds = stack.top(); stack.pop();
        auto a = stack.top(); stack.pop();
        
        uint64_t n = static_cast<uint64_t>(a.d);
        int k = static_cast<int>(rounds.d);
        bool result = solovay_strassen(n, k);
        
        woflang::WofValue res;
        res.d = result ? 1.0 : 0.0;
        stack.push(res);
    };
    
    // Trial division (for comparison)
    (*op_table)["prime_check_trial"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.empty()) {
            throw std::runtime_error("Stack underflow on prime_check_trial");
        }
        auto a = stack.top(); stack.pop();
        
        uint64_t n = static_cast<uint64_t>(a.d);
        bool result = trial_division_fast(n);
        
        woflang::WofValue res;
        res.d = result ? 1.0 : 0.0;
        stack.push(res);
    };
    
    // Modular exponentiation
    (*op_table)["mod_pow"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.size() < 3) {
            throw std::runtime_error("Stack underflow on mod_pow (need base, exponent, modulus)");
        }
        auto mod = stack.top(); stack.pop();
        auto exp = stack.top(); stack.pop();
        auto base = stack.top(); stack.pop();
        
        uint64_t result = mod_pow(
            static_cast<uint64_t>(base.d),
            static_cast<uint64_t>(exp.d),
            static_cast<uint64_t>(mod.d)
        );
        
        woflang::WofValue res;
        res.d = static_cast<double>(result);
        stack.push(res);
    };
    
    // Greatest Common Divisor (Euclidean algorithm)
    (*op_table)["gcd"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.size() < 2) {
            throw std::runtime_error("Stack underflow on gcd");
        }
        auto b = stack.top(); stack.pop();
        auto a = stack.top(); stack.pop();
        
        uint64_t x = static_cast<uint64_t>(a.d);
        uint64_t y = static_cast<uint64_t>(b.d);
        
        while (y != 0) {
            uint64_t temp = y;
            y = x % y;
            x = temp;
        }
        
        woflang::WofValue result;
        result.d = static_cast<double>(x);
        stack.push(result);
    };
    
    // Speed comparison operation
    (*op_table)["speed_compare"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.empty()) {
            throw std::runtime_error("Stack underflow on speed_compare");
        }
        auto a = stack.top(); stack.pop();
        
        uint64_t n = static_cast<uint64_t>(a.d);
        
        std::cout << "Speed comparison for " << n << ":\n";
        
        // Trial division timing
        auto start = std::chrono::high_resolution_clock::now();
        bool trial_result = trial_division_fast(n);
        auto end = std::chrono::high_resolution_clock::now();
        double trial_time = std::chrono::duration<double, std::milli>(end - start).count();
        
        // Miller-Rabin timing
        start = std::chrono::high_resolution_clock::now();
        bool miller_result = miller_rabin(n);
        end = std::chrono::high_resolution_clock::now();
        double miller_time = std::chrono::duration<double, std::milli>(end - start).count();
        
        // Fermat timing
        start = std::chrono::high_resolution_clock::now();
        bool fermat_result = fermat_test(n);
        end = std::chrono::high_resolution_clock::now();
        double fermat_time = std::chrono::duration<double, std::milli>(end - start).count();
        
        std::cout << "  Trial Division: " << trial_time << " ms (result: " << trial_result << ")\n";
        std::cout << "  Miller-Rabin:   " << miller_time << " ms (result: " << miller_result << ")\n";
        std::cout << "  Fermat Test:    " << fermat_time << " ms (result: " << fermat_result << ")\n";
        
        if (trial_time > 0) {
            std::cout << "  Speedup: " << (trial_time / miller_time) << "x faster with Miller-Rabin!\n";
        }
        
        // Push Miller-Rabin result
        woflang::WofValue result;
        result.d = miller_result ? 1.0 : 0.0;
        stack.push(result);
    };
    
    // Random prime generation
    (*op_table)["random_prime"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.empty()) {
            throw std::runtime_error("Stack underflow on random_prime");
        }
        auto bits = stack.top(); stack.pop();
        
        int bit_count = static_cast<int>(bits.d);
        if (bit_count < 2 || bit_count > 62) {
            throw std::runtime_error("Bit count must be between 2 and 62");
        }
        
        std::random_device rd;
        std::mt19937_64 gen(rd());
        uint64_t min_val = 1ULL << (bit_count - 1);
        uint64_t max_val = (1ULL << bit_count) - 1;
        std::uniform_int_distribution<uint64_t> dis(min_val, max_val);
        
        uint64_t candidate;
        do {
            candidate = dis(gen);
            if (candidate % 2 == 0) candidate++;  // Make it odd
        } while (!miller_rabin(candidate));
        
        woflang::WofValue result;
        result.d = static_cast<double>(candidate);
        stack.push(result);
    };
    
    // Benchmarking operation
    (*op_table)["crypto_benchmark"] = [](std::stack<woflang::WofValue>& stack) {
        std::cout << "🚀 CRYPTO SPEED BENCHMARK 🚀\n";
        std::cout << "==============================\n";
        
        std::vector<uint64_t> test_numbers = {
            1000000007ULL,
            1000000009ULL,
            10000000019ULL,
            100000000003ULL,
            1000000000039ULL,
            1000000000061ULL
        };
        
        for (uint64_t n : test_numbers) {
            std::cout << "\nTesting " << n << ":\n";
            
            auto start = std::chrono::high_resolution_clock::now();
            bool result = miller_rabin(n);
            auto end = std::chrono::high_resolution_clock::now();
            double time = std::chrono::duration<double, std::milli>(end - start).count();
            
            std::cout << "  Miller-Rabin: " << time << " ms (" << (result ? "PRIME" : "COMPOSITE") << ")\n";
        }
        
        std::cout << "\n🐺 BLAZING FAST! 🐺\n";
    };
}

} // extern "C"