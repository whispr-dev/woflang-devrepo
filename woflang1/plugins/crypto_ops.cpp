}
        });
        
        // from_binary: Convert a binary representation to a string
        interp.register_op("from_binary", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                std::cout << "from_binary: Stack empty\n";
                return;
            }
            
            auto value = interp.stack.back(); interp.stack.pop_back();
            
            if (value.type == WofType::String || value.type == WofType::Symbol) {
                std::string binary = std::get<std::string>(value.value);
                std::string text = binary_to_text(binary);
                interp.stack.emplace_back(text);
            } else {
                std::cout << "from_binary: Value must be a string or symbol\n";
                interp.stack.push_back(value);
            }
        });
        
        // to_hex: Convert a string or number to its hexadecimal representation
        interp.register_op("to_hex", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                std::cout << "to_hex: Stack empty\n";
                return;
            }
            
            auto value = interp.stack.back(); interp.stack.pop_back();
            
            if (value.type == WofType::String || value.type == WofType::Symbol) {
                std::string str = std::get<std::string>(value.value);
                std::string hex = to_hex(str);
                interp.stack.emplace_back(hex);
            } else if (value.type == WofType::Integer) {
                std::ostringstream hex;
                hex << std::hex << std::get<int64_t>(value.value);
                interp.stack.emplace_back(hex.str());
            } else {
                std::cout << "to_hex: Value must be a string, symbol, or integer\n";
                interp.stack.push_back(value);
            }
        });
        
        // from_hex: Convert a hexadecimal representation to a string
        interp.register_op("from_hex", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                std::cout << "from_hex: Stack empty\n";
                return;
            }
            
            auto value = interp.stack.back(); interp.stack.pop_back();
            
            if (value.type == WofType::String || value.type == WofType::Symbol) {
                std::string hex = std::get<std::string>(value.value);
                std::string bytes = from_hex(hex);
                interp.stack.emplace_back(bytes);
            } else {
                std::cout << "from_hex: Value must be a string or symbol\n";
                interp.stack.push_back(value);
            }
        });
        
        // base64_encode: Encode a string with Base64
        interp.register_op("base64_encode", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                std::cout << "base64_encode: Stack empty\n";
                return;
            }
            
            auto value = interp.stack.back(); interp.stack.pop_back();
            
            if (value.type == WofType::String || value.type == WofType::Symbol) {
                std::string str = std::get<std::string>(value.value);
                std::string encoded = base64_encode(str);
                interp.stack.emplace_back(encoded);
            } else {
                std::cout << "base64_encode: Value must be a string or symbol\n";
                interp.stack.push_back(value);
            }
        });
        
        // base64_decode: Decode a Base64-encoded string
        interp.register_op("base64_decode", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                std::cout << "base64_decode: Stack empty\n";
                return;
            }
            
            auto value = interp.stack.back(); interp.stack.pop_back();
            
            if (value.type == WofType::String || value.type == WofType::Symbol) {
                std::string str = std::get<std::string>(value.value);
                std::string decoded = base64_decode(str);
                interp.stack.emplace_back(decoded);
            } else {
                std::cout << "base64_decode: Value must be a string or symbol\n";
                interp.stack.push_back(value);
            }
        });
        
        // ----- Random Number Generation -----
        
        // random: Generate a random integer within a range
        interp.register_op("random", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                std::cout << "random: Need min and max values\n";
                return;
            }
            
            auto max = interp.stack.back(); interp.stack.pop_back();
            auto min = interp.stack.back(); interp.stack.pop_back();
            
            if (min.type == WofType::Integer && max.type == WofType::Integer) {
                int64_t min_val = std::get<int64_t>(min.value);
                int64_t max_val = std::get<int64_t>(max.value);
                
                if (min_val > max_val) {
                    std::swap(min_val, max_val);
                }
                
                int64_t result = random_int(min_val, max_val);
                interp.stack.emplace_back(result);
            } else {
                std::cout << "random: Both values must be integers\n";
                interp.stack.push_back(min);
                interp.stack.push_back(max);
            }
        });
        
        // random_bytes: Generate random bytes
        interp.register_op("random_bytes", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                std::cout << "random_bytes: Need count\n";
                return;
            }
            
            auto count = interp.stack.back(); interp.stack.pop_back();
            
            if (count.type == WofType::Integer) {
                int64_t count_val = std::get<int64_t>(count.value);
                
                if (count_val <= 0 || count_val > 1024) {
                    std::cout << "random_bytes: Count must be between 1 and 1024\n";
                    interp.stack.push_back(count);
                    return;
                }
                
                std::string bytes = random_bytes(static_cast<size_t>(count_val));
                interp.stack.emplace_back(bytes);
                
                // Also display hexadecimal representation
                std::cout << "Random bytes (hex): " << to_hex(bytes) << std::endl;
            } else {
                std::cout << "random_bytes: Count must be an integer\n";
                interp.stack.push_back(count);
            }
        });
        
        // ----- Educational Crypto Concepts -----
        
        // prime_check: Check if a number is prime
        interp.register_op("prime_check", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                std::cout << "prime_check: Stack empty\n";
                return;
            }
            
            auto value = interp.stack.back(); interp.stack.pop_back();
            
            if (value.type == WofType::Integer) {
                int64_t n = std::get<int64_t>(value.value);
                
                if (n <= 1) {
                    interp.stack.emplace_back(0LL);  // Not prime
                    return;
                }
                
                if (n == 2 || n == 3) {
                    interp.stack.emplace_back(1LL);  // Prime
                    return;
                }
                
                if (n % 2 == 0 || n % 3 == 0) {
                    interp.stack.emplace_back(0LL);  // Not prime
                    return;
                }
                
                for (int64_t i = 5; i * i <= n; i += 6) {
                    if (n % i == 0 || n % (i + 2) == 0) {
                        interp.stack.emplace_back(0LL);  // Not prime
                        return;
                    }
                }
                
                interp.stack.emplace_back(1LL);  // Prime
            } else {
                std::cout << "prime_check: Value must be an integer\n";
                interp.stack.push_back(value);
            }
        });
        
        // factor: Find the prime factors of a number
        interp.register_op("factor", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                std::cout << "factor: Stack empty\n";
                return;
            }
            
            auto value = interp.stack.back(); interp.stack.pop_back();
            
            if (value.type == WofType::Integer) {
                int64_t n = std::get<int64_t>(value.value);
                
                if (n <= 0) {
                    std::cout << "factor: Value must be a positive integer\n";
                    interp.stack.push_back(value);
                    return;
                }
                
                std::vector<int64_t> factors;
                
                // Find all factors of 2
                while (n % 2 == 0) {
                    factors.push_back(2);
                    n /= 2;
                }
                
                // Find all odd factors
                for (int64_t i = 3; i * i <= n; i += 2) {
                    while (n % i == 0) {
                        factors.push_back(i);
                        n /= i;
                    }
                }
                
                // If n > 1, it's a prime factor
                if (n > 1) {
                    factors.push_back(n);
                }
                
                // Display the factors
                std::cout << "Prime factors: ";
                for (size_t i = 0; i < factors.size(); ++i) {
                    std::cout << factors[i];
                    if (i < factors.size() - 1) {
                        std::cout << " * ";
                    }
                }
                std::cout << std::endl;
                
                // Push the factors onto the stack
                for (int64_t factor : factors) {
                    interp.stack.emplace_back(factor);
                }
            } else {
                std::cout << "factor: Value must be an integer\n";
                interp.stack.push_back(value);
            }
        });
        
        // entropy: Calculate the entropy of a string
        interp.register_op("entropy", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                std::cout << "entropy: Stack empty\n";
                return;
            }
            
            auto value = interp.stack.back(); interp.stack.pop_back();
            
            if (value.type == WofType::String || value.type == WofType::Symbol) {
                std::string str = std::get<std::string>(value.value);
                
                // Count the frequency of each byte
                std::array<int, 256> freq{};
                for (unsigned char c : str) {
                    freq[c]++;
                }
                
                // Calculate the entropy (Shannon formula)
                double entropy = 0.0;
                for (int count : freq) {
                    if (count > 0) {
                        double p = static_cast<double>(count) / str.size();
                        entropy -= p * std::log2(p);
                    }
                }
                
                interp.stack.emplace_back(entropy);
                std::cout << "Entropy: " << entropy << " bits per byte\n";
                std::cout << "Perfect entropy for a byte is 8 bits.\n";
            } else {
                std::cout << "entropy: Value must be a string or symbol\n";
                interp.stack.push_back(value);
            }
        });
        
        // diffie_hellman: Simulate a Diffie-Hellman key exchange (educational)
        interp.register_op("diffie_hellman", [](WoflangInterpreter& interp) {
            // Default values for Diffie-Hellman
            int64_t p = 23;  // A small prime for demonstration
            int64_t g = 5;   // A primitive root modulo p
            
            // Use values from the stack if provided
            if (interp.stack.size() >= 2) {
                auto g_val = interp.stack.back(); interp.stack.pop_back();
                auto p_val = interp.stack.back(); interp.stack.pop_back();
                
                if (p_val.type == WofType::Integer && g_val.type == WofType::Integer) {
                    p = std::get<int64_t>(p_val.value);
                    g = std::get<int64_t>(g_val.value);
                } else {
                    std::cout << "diffie_hellman: Parameters must be integers\n";
                    interp.stack.push_back(p_val);
                    interp.stack.push_back(g_val);
                    return;
                }
            }
            
            // Generate private keys for Alice and Bob
            int64_t a = random_int(2, p - 2);  // Alice's private key
            int64_t b = random_int(2, p - 2);  // Bob's private key
            
            // Compute public keys
            int64_t A = mod_pow(g, a, p);  // Alice's public key
            int64_t B = mod_pow(g, b, p);  // Bob's public key
            
            // Compute shared secret
            int64_t secret_a = mod_pow(B, a, p);  // Alice's computation
            int64_t secret_b = mod_pow(A, b, p);  // Bob's computation
            
            // Display the process
            std::cout << "Diffie-Hellman Key Exchange (Educational)\n";
            std::cout << "----------------------------------------\n";
            std::cout << "Parameters:\n";
            std::cout << "  p = " << p << " (prime modulus)\n";
            std::cout << "  g = " << g << " (generator)\n\n";
            
            std::cout << "Private keys:\n";
            std::cout << "  a = " << a << " (Alice's private key)\n";
            std::cout << "  b = " << b << " (Bob's private key)\n\n";
            
            std::cout << "Public keys:\n";
            std::cout << "  A = g^a mod p = " << A << " (Alice's public key)\n";
            std::cout << "  B = g^b mod p = " << B << " (Bob's public key)\n\n";
            
            std::cout << "Shared secret computation:\n";
            std::cout << "  Alice: B^a mod p = " << secret_a << "\n";
            std::cout << "  Bob:   A^b mod p = " << secret_b << "\n\n";
            
            if (secret_a == secret_b) {
                std::cout << "Shared secret: " << secret_a << "\n";
            } else {
                std::cout << "Error: Shared secrets don't match!\n";
            }
            
            // Push the shared secret onto the stack
            interp.stack.emplace_back(secret_a);
        });
        
        // rsa_demo: Demonstrate a simple RSA encryption/decryption (educational)
        interp.register_op("rsa_demo", [](WoflangInterpreter& interp) {
            std::cout << "RSA Encryption/Decryption Demo (Educational)\n";
            std::cout << "-------------------------------------------\n";
            
            // Generate small primes for demonstration
            int64_t p = 61;
            int64_t q = 53;
            
            // Compute modulus
            int64_t n = p * q;
            
            // Compute Euler's totient function
            int64_t phi = (p - 1) * (q - 1);
            
            // Choose e (usually 65537, but we use a smaller number for demonstration)
            int64_t e = 17;
            
            // Compute d (private key)
            int64_t d = mod_inverse(e, phi);
            
            // Choose a message
            int64_t message = 42;
            
            // If a message is provided on the stack, use it
            if (!interp.stack.empty()) {
                auto msg = interp.stack.back(); interp.stack.pop_back();
                
                if (msg.type == WofType::Integer) {
                    message = std::get<int64_t>(msg.value);
                    if (message >= n) {
                        std::cout << "Message must be less than " << n << "\n";
                        message = message % n;
                        std::cout << "Using message modulo n: " << message << "\n";
                    }
                } else {
                    std::cout << "rsa_demo: Message must be an integer\n";
                    interp.stack.push_back(msg);
                    return;
                }
            }
            
            // Encrypt
            int64_t ciphertext = mod_pow(message, e, n);
            
            // Decrypt
            int64_t decrypted = mod_pow(ciphertext, d, n);
            
            // Display the process
            std::cout << "Key generation:\n";
            std::cout << "  p = " << p << ", q = " << q << " (prime factors)\n";
            std::cout << "  n = p * q = " << n << " (modulus)\n";
            std::cout << "  phi(n) = (p-1) * (q-1) = " << phi << "\n";
            std::cout << "  e = " << e << " (public exponent)\n";
            std::cout << "  d = " << d << " (private exponent)\n\n";
            
            std::cout << "Encryption/decryption:\n";
            std::cout << "  Message: " << message << "\n";
            std::cout << "  Ciphertext = message^e mod n = " << ciphertext << "\n";
            std::cout << "  Decrypted = ciphertext^d mod n = " << decrypted << "\n\n";
            
            if (message == decrypted) {
                std::cout << "Decryption successful!\n";
            } else {
                std::cout << "Error: Decryption failed!\n";
            }
            
            // Push the ciphertext and decrypted message onto the stack
            interp.stack.emplace_back(ciphertext);
            interp.stack.emplace_back(decrypted);
        });
        
        // caesar_break: Attempt to break a Caesar cipher by brute force
        interp.register_op("caesar_break", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                std::cout << "caesar_break: Stack empty\n";
                return;
            }
            
            auto ciphertext = interp.stack.back(); interp.stack.pop_back();
            
            if (ciphertext.type == WofType::String || ciphertext.type == WofType::Symbol) {
                std::string cipher = std::get<std::string>(ciphertext.value);
                
                std::cout << "Caesar Cipher Brute Force:\n";
                std::cout << "-------------------------\n";
                
                for (int shift = 0; shift < 26; ++shift) {
                    std::string plaintext = caesar_cipher(cipher, -shift);
                    std::cout << "Shift " << shift << ": " << plaintext << "\n";
                }
                
                // Push the original ciphertext back onto the stack
                interp.stack.push_back(ciphertext);
            } else {
                std::cout << "caesar_break: Value must be a string or symbol\n";
                interp.stack.push_back(ciphertext);
            }
        });
    }
};

} // namespace woflang

// Plugin registration function
WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::CryptoOpsPlugin plugin;
    plugin.register_ops(interp);
}