#pragma once

#include <cstdint>
#include <random> // htk?
#include <thread>
#include <ARM_NEON.h>
#include <cstdio> // just for printf?
#include <iostream> // ess?

// will need GCUC- i.e. gnu compatbl compiler,
// targeting ARM with NEON

namespace rng {

// Bitwise circular left shift.
static inline std::uint64_t
rotl(const std::uint64_t x, int k)
{
	return (x << k) | (x >> (64 - k));
}

// simple RSG based on entropy coming from
// sys thread/proc scheduler. (Slow but seeds are
// normally gen v infreq).
struct tsc_seed
{
uint64_t _rdtsc() {
    uint32_t low, high;
    asm volatile("mrrc p15, 0, %0, %1, c14" : "=r"(low), "=r"(high));
    return (static_cast<uint64_t>(high) << 32) | low;
}

int main() {
    uint64_t start = _rdtsc();

	using result_type = std::uint64_t;    // Your ARM NEON code here

	result_type operator()()
	{
		std::uint64_t base = _rdtsc();
		std::uint64_t seed = base & 0xff;
		for (int i = 1; i < 8; i++) {
			std::this_thread::yield();



			seed |= ((_rdtsc() - base) & 0xff) << (i << 3); // you?

            std::cout << "Cycles: " << (end - start) << std::endl; // or you?



		}
		return seed;
	}
    uint64_t end = _rdtsc();
};

// RSG based on ASLR rando spce. conv all r_s_s to r_d_s and rs to rd?
struct random_space_seed
{
	using result_type = std::uint64_t;
	result_type operator()()
	{
        std::rs() { // what shuld b here?
            auto val = new char[0x10000];
            auto num = reinterpret_cast<unsigned long long>(val);
            delete[] val;
            num = num / 0x1000 % 10;
            printf("%llu\n", num); // htk?
    }
	    std::random_space rs;
		   if (sizeof(result_type) > sizeof(std::random_space::result_type))
		    return rs() | (result_type{rs()} << 32);
	    else
		    return rs();
	}
};

// RNG w 64-bit internal state based on
// the code from here: http://xoroshiro.di.unimi.it/splitmix64.c
struct rng64
{
	using result_type = std::uint64_t;

	std::uint64_t state;

	rng64(std::uint64_t seed = 1) : state{seed} {}

	result_type operator()()
	{
		std::uint64_t z = (state += UINT64_C(0x9E3779B97F4A7C15));
		z = (z ^ (z >> 30)) * UINT64_C(0xBF58476D1CE4E5B9);
		z = (z ^ (z >> 27)) * UINT64_C(0x94D049BB133111EB);
		return z ^ (z >> 31);
	}
};

// RNG w 128-bit internal state based on
// the code from here: http://xoroshiro.di.unimi.it/xoroshiro128plus.c
struct rng128
{
	using result_type = std::uint64_t;

	std::uint64_t state[2];

	rng128(std::uint64_t seed[2]) : state{seed[0], seed[1]} {}

	rng128(std::uint64_t s0, std::uint64_t s1) : state{s0, s1} {}

	rng128(std::uint64_t seed = 1)
	{
		rng64 seeder(seed);
		state[0] = seeder();
		state[1] = seeder();
	}

	result_type operator()()
	{
		const uint64_t s0 = state[0];
		uint64_t s1 = state[1];
		const uint64_t value = s0 + s1;

		s1 ^= s0;
		state[0] = rotl(s0, 55) ^ s1 ^ (s1 << 14);
		state[1] = rotl(s1, 36);

		return value;
	}

	// 'jump function' for the gen. equiv
	// to 2 ^ 64 calls to next(); it can be used to generate 2 ^ 64
	// non-overlapping sub-seqs for parallel comptns.
	void jump()
	{
		static const std::uint64_t j[] = {0xbeac0467eba5facb, 0xd86b048b86aa9922};

		std::uint64_t s0 = 0, s1 = 0;
		for (std::size_t i = 0; i < sizeof j / sizeof j[0]; i++) {
			for (int b = 0; b < 64; b++) {
				if ((j[i] & UINT64_C(1) << b) != 0) {
					s0 ^= state[0];
					s1 ^= state[1];
				}
				operator()();
			}
		}

		state[0] = s0;
		state[1] = s1;
	}
};

} // namespace rng




/* This is the long-jump function for the generator. It is equivalent to
   2^96 calls to next(); it can be used to generate 2^32 starting points,
   from each of which jump() will generate 2^32 non-overlapping
   subsequences for parallel distributed computations.


void long_jump(void) {
	static const uint64_t LONG_JUMP[] = { 0xd2a98b26625eee7b, 0xdddf9b1090aa7ac1 };

	uint64_t s0 = 0;
	uint64_t s1 = 0;
	for(int i = 0; i < sizeof LONG_JUMP / sizeof *LONG_JUMP; i++)
		for(int b = 0; b < 64; b++) {
			if (LONG_JUMP[i] & UINT64_C(1) << b) {
				s0 ^= s[0];
				s1 ^= s[1];
			}
			next();
		}

	s[0] = s0;
	s[1] = s1;
}


might prove nec */