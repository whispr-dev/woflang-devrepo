
// should be faster linux

rng::tsc_seed seed;
rng::rng128 gen(seed());
std::cout << "a random number: " << gen() << "\n";


// should be faster mac/arm/x86

rng::random_space_seed seed;
rng::rng128 gen(seed());
std::cout << "a random number: " << gen() << "\n"; 
