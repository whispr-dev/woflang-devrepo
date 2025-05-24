#include "../../src/core/woflang.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <cmath>
#include <functional>
#include <algorithm>
#include <iomanip>
#include <sstream>

namespace woflang {

/**
 * @brief Helper functions for crypto operations
 */
namespace crypto_helpers {
    // Convert string to binary representation
    std::string text_to_binary(const std::string& text) {
        std::string binary;
        for (char c : text) {
            for (int i = 7; i >= 0; --i) {
                binary += ((c & (1 << i)) ? '1' : '0');
            }
            binary += ' ';
        }
        return binary;
    }
    
    // Convert binary representation to string
    std::string binary_to_text(const std::string& binary) {
        std::string text;
        std::string current_byte;
        
        for (char c : binary) {
            if (c == '0' || c == '1') {
                current_byte += c;
                if (current_byte.size() == 8) {
                    char byte = 0;
                    for (int i = 0; i < 8; ++i) {
                        if (current_byte[i] == '1') {
                            byte |= (1 << (7 - i));
                        }
                    }
                    text += byte;
                    current_byte.clear();
                }
            }
        }
        
        return text;
    }
    
    // Convert string to hexadecimal representation
    std::string to_hex(const std::string& text) {
        std::stringstream ss;
        for (unsigned char c : text) {
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
        }
        return ss.str();
    }
    
    // Convert hexadecimal representation to string
    std::string from_hex(const std::string& hex) {
        std::string text;
        for (size_t i = 0; i < hex.length(); i += 2) {
            std::string byte = hex.substr(i, 2);
            char c = static_cast<char>(std::stoi(byte, nullptr, 16));
            text += c;
        }
        return text;
    }
    
    // Base64 encoding/decoding
    static const std::string base64_chars = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    std::string base64_encode(const std::string& input) {
        std::string encoded;
        int i = 0;
        int j = 0;
        unsigned char char_array_3[3];
        unsigned char char_array_4[4];
        
        for (char c : input) {
            char_array_3[i++] = c;
            if (i == 3) {
                char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
                char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
                char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
                char_array_4[3] = char_array_3[2] & 0x3f;
                
                for (i = 0; i < 4; i++) {
                    encoded += base64_chars[char_array_4[i]];
                }
                i = 0;
            }
        }
        
        if (i) {
            for (j = i; j < 3; j++) {
                char_array_3[j] = '\0';
            }
            
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            
            for (j = 0; j < i + 1; j++) {
                encoded += base64_chars[char_array_4[j]];
            }
            
            while (i++ < 3) {
                encoded += '=';
            }
        }
        
        return encoded;
    }
    
    std::string base64_decode(const std::string& encoded) {
        std::string decoded;
        int i = 0;
        int j = 0;
        int in_len = encoded.size();
        unsigned char char_array_4[4], char_array_3[3];
        
        auto is_base64 = [](unsigned char c) -> bool {
            return (isalnum(c) || (c == '+') || (c == '/'));
        };
        
        while (in_len-- && (encoded[j] != '=') && is_base64(encoded[j])) {
            char_array_4[i++] = encoded[j++];
            if (i == 4) {
                for (i = 0; i < 4; i++) {
                    char_array_4[i] = base64_chars.find(char_array_4[i]);
                }
                
                char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
                char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
                char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
                
                for (i = 0; i < 3; i++) {
                    decoded += char_array_3[i];
                }
                i = 0;
            }
        }
        
        if (i) {
            for (j = 0; j < i; j++) {
                char_array_4[j] = base64_chars.find(char_array_4[j]);
            }
            
            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            
            for (j = 0; j < i - 1; j++) {
                decoded += char_array_3[j];
            }
        }
        
        return decoded;
    }
    
    // Generate a random integer in a range
    int64_t random_int(int64_t min, int64_t max) {
        static std::mt19937_64 rng(static_cast<unsigned long>(std::time(nullptr)));
        std::uniform_int_distribution<int64_t> dist(min, max);
        return dist(rng);
    }
    
    // Generate random bytes
    std::string random_bytes(size_t count) {
        static std::mt19937 rng(static_cast<unsigned long>(std::time(nullptr)));
        std::uniform_int_distribution<int> dist(0, 255);
        
        std::string bytes;
        for (size_t i = 0; i < count; ++i) {
            bytes += static_cast<char>(dist(rng));
        }
        
        return bytes;
    }
    
    // Modular exponentiation for large integers
    int64_t mod_pow(int64_t base, int64_t exp, int64_t modulus) {
        if (modulus == 1) return 0;
        
        int64_t result = 1;
        base = base % modulus;
        
        while (exp > 0) {
            if (exp % 2 == 1) {
                result = (result * base) % modulus;
            }
            exp = exp >> 1;
            base = (base * base) % modulus;
        }
        
        return result;
    }
    
    // Extended Euclidean Algorithm for modular inverse
    int64_t mod_inverse(int64_t a, int64_t m) {
        int64_t m0 = m;
        int64_t y = 0, x = 1;
        
        if (m == 1) return 0;
        
        while (a > 1) {
            // q is quotient
            int64_t q = a / m;
            int64_t t = m;
            
            // m is remainder now, process same as Euclid's GCD algorithm
            m = a % m;
            a = t;
            t = y;
            
            // Update y and x
            y = x - q * y;
            x = t;
        }
        
        // Make x positive
        if (x < 0) {
            x += m0;
        }
        
        return x;
    }
    
    // Simple Caesar cipher
    std::string caesar_cipher(const std::string& text, int shift) {
        std::string result;
        
        for (char c : text) {
            if (std::isalpha(c)) {
                char base = std::islower(c) ? 'a' : 'A';
                result += static_cast<char>(((c - base + shift) % 26 + 26) % 26 + base);
            } else {
                result += c;
            }
        }
        
        return result;
    }
    
    // FNV-1a hash (simplified)
    uint64_t fnv1a_hash(const std::string& data) {
        const uint64_t FNV_PRIME = 1099511628211ULL;
        const uint64_t FNV_OFFSET_BASIS = 14695981039346656037ULL;
        
        uint64_t hash = FNV_OFFSET_BASIS;
        
        for (unsigned char c : data) {
            hash ^= c;
            hash *= FNV_PRIME;
        }
        
        return hash;
    }
    
    // Simple XOR cipher
    std::string xor_cipher(const std::string& text, const std::string& key) {
        std::string result;
        
        for (size_t i = 0; i < text.size(); ++i) {
            result += text[i] ^ key[i % key.size()];
        }
        
        return result;
    }
}

/**
 * @brief Cryptography operations plugin for Woflang
 * 
 * This plugin provides various cryptographic operations and tools.
 */
class CryptoOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        // ----- Binary/Hex/Base64 Conversion -----
        
        // to_binary: Convert a string to its binary representation
        interp.register_op("to_binary", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on to_binary");
            }
            
            auto value = interp.stack.back(); interp.stack.pop_back();
            
            if (value.type == WofType::String || value.type == WofType::Symbol) {
                std::string str = std::get<std::string>(value.value);
                std::string binary = crypto_helpers::text_to_binary(str);
                interp.stack.emplace_back(binary);
            } else {
                throw std::runtime_error("Type error: to_binary requires a string or symbol");
            }
        });
        
        // from_binary: Convert a binary representation to a string
        interp.register_op("from_binary", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on from_binary");
            }
            
            auto value = interp.stack.back(); interp.stack.pop_back();
            
            if (value.type == WofType::String || value.type == WofType::Symbol) {
                std::string binary = std::get<std::string>(value.value);
                std::string text = crypto_helpers::binary_to_text(binary);
                interp.stack.emplace_back(text);
            } else {
                throw std::runtime_error("Type error: from_binary requires a string or symbol");
            }
        });
        
        // to_hex: Convert a string or number to its hexadecimal representation
        interp.register_op("to_hex", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on to_hex");
            }
            
            auto value = interp.stack.back(); interp.stack.pop_back();
            
            if (value.type == WofType::String || value.type == WofType::Symbol) {
                std::string str = std::get<std::string>(value.value);
                std::string hex = crypto_helpers::to_hex(str);
                interp.stack.emplace_back(hex);
            } else if (value.type == WofType::Integer) {
                std::stringstream hex;
                hex << std::hex << std::get<int64_t>(value.value);
                interp.stack.emplace_back(hex.str());
            } else {
                throw std::runtime_error("Type error: to_hex requires a string, symbol, or integer");
            }
        });
        
        // from_hex: Convert a hexadecimal representation to a string
        interp.register_op("from_hex", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on from_hex");
            }
            
            auto value = interp.stack.back(); interp.stack.pop_back();
            
            if (value.type == WofType::String || value.type == WofType::Symbol) {
                std::string hex = std::get<std::string>(value.value);
                std::string bytes = crypto_helpers::from_hex(hex);
                interp.stack.emplace_back(bytes);
            } else {
                throw std::runtime_error("Type error: from_hex requires a string or symbol");
            }
        });
        
        // base64_encode: Encode a string with Base64
        interp.register_op("base64_encode", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on base64_encode");
            }
            
            auto value = interp.stack.back(); interp.stack.pop_back();
            
            if (value.type == WofType::String || value.type == WofType::Symbol) {
                std::string str = std::get<std::string>(value.value);
                std::string encoded = crypto_helpers::base64_encode(str);
                interp.stack.emplace_back(encoded);
            } else {
                throw std::runtime_error("Type error: base64_encode requires a string or symbol");
            }
        });
        
        // base64_decode: Decode a Base64-encoded string
        interp.register_op("base64_decode", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on base64_decode");
            }
            
            auto value = interp.stack.back(); interp.stack.pop_back();
            
            if (value.type == WofType::String || value.type == WofType::Symbol) {
                std::string str = std::get<std::string>(value.value);
                std::string decoded = crypto_helpers::base64_decode(str);
                interp.stack.emplace_back(decoded);
            } else {
                throw std::runtime_error("Type error: base64_decode requires a string or symbol");
            }
        });
        
        // ----- Random Number Generation -----
        
        // random: Generate a random integer within a range
        interp.register_op("random", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("Stack underflow on random");
            }
            
            auto max = interp.stack.back(); interp.stack.pop_back();
            auto min = interp.stack.back(); interp.stack.pop_back();
            
            if (min.type == WofType::Integer && max.type == WofType::Integer) {
                int64_t min_val = std::get<int64_t>(min.value);
                int64_t max_val = std::get<int64_t>(max.value);
                
                if (min_val > max_val) {
                    std::swap(min_val, max_val);
                }
                
                int64_t result = crypto_helpers::random_int(min_val, max_val);
                interp.stack.emplace_back(result);
            } else {
                throw std::runtime_error("Type error: random requires integer values");
            }
        });
        
        // random_bytes: Generate random bytes
        interp.register_op("random_bytes", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on random_bytes");
            }
            
            auto count = interp.stack.back(); interp.stack.pop_back();
            
            if (count.type == WofType::Integer) {
                int64_t count_val = std::get<int64_t>(count.value);
                
                if (count_val <= 0 || count_val > 1024) {
                    throw std::runtime_error("Value error: count must be between 1 and 1024");
                }
                
                std::string bytes = crypto_helpers::random_bytes(static_cast<size_t>(count_val));
                interp.stack.emplace_back(bytes);
                
                // Also display hexadecimal representation
                std::cout << "Random bytes (hex): " << crypto_helpers::to_hex(bytes) << std::endl;
            } else {
                throw std::runtime_error("Type error: random_bytes requires an integer count");
            }
        });
        
        // ----- Educational Crypto Concepts -----
        
        // prime_check: Check if a number is prime
        interp.register_op("prime_check", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on prime_check");
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
                throw std::runtime_error("Type error: prime_check requires an integer");
            }
        });
        
        // factor: Find the prime factors of a number
        interp.register_op("factor", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on factor");
            }
            
            auto value = interp.stack.back(); interp.stack.pop_back();
            
            if (value.type == WofType::Integer) {
                int64_t n = std::get<int64_t>(value.value);
                
                if (n <= 0) {
                    throw std::runtime_error("Value error: factor requires a positive integer");
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
                throw std::runtime_error("Type error: factor requires an integer");
            }
        });
        
        // entropy: Calculate the entropy of a string
        interp.register_op("entropy", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on entropy");
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
                throw std::runtime_error("Type error: entropy requires a string or symbol");
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
                    throw std::runtime_error("Type error: diffie_hellman parameters must be integers");
                }
            }
            
            // Generate private keys for Alice and Bob
            int64_t a = crypto_helpers::random_int(2, p - 2);  // Alice's private key
            int64_t b = crypto_helpers::random_int(2, p - 2);  // Bob's private key
            
            // Compute public keys
            int64_t A = crypto_helpers::mod_pow(g, a, p);  // Alice's public key
            int64_t B = crypto_helpers::mod_pow(g, b, p);  // Bob's public key
            
            // Compute shared secret
            int64_t secret_a = crypto_helpers::mod_pow(B, a, p);  // Alice's computation
            int64_t secret_b = crypto_helpers::mod_pow(A, b, p);  // Bob's computation
            
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
            int64_t d = crypto_helpers::mod_inverse(e, phi);
            
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
                    throw std::runtime_error("Type error: rsa_demo message must be an integer");
                }
            }
            
            // Encrypt
            int64_t ciphertext = crypto_helpers::mod_pow(message, e, n);
            
            // Decrypt
            int64_t decrypted = crypto_helpers::mod_pow(ciphertext, d, n);
            
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
        
        // caesar_cipher: Apply a Caesar cipher to a string
        interp.register_op("caesar_cipher", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("Stack underflow on caesar_cipher");
            }
            
            auto shift = interp.stack.back(); interp.stack.pop_back();
            auto text = interp.stack.back(); interp.stack.pop_back();
            
            if (shift.type != WofType::Integer) {
                throw std::runtime_error("Type error: caesar_cipher shift must be an integer");
            }
            
            if (text.type != WofType::String && text.type != WofType::Symbol) {
                throw std::runtime_error("Type error: caesar_cipher text must be a string or symbol");
            }
            
            int64_t shift_val = std::get<int64_t>(shift.value);
            std::string text_val = std::get<std::string>(text.value);
            
            std::string result = crypto_helpers::caesar_cipher(text_val, static_cast<int>(shift_val));
            interp.stack.emplace_back(result);
        });
        
        // caesar_break: Attempt to break a Caesar cipher by brute force
        interp.register_op("caesar_break", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on caesar_break");
            }
            
            auto ciphertext = interp.stack.back(); interp.stack.pop_back();
            
            if (ciphertext.type == WofType::String || ciphertext.type == WofType::Symbol) {
                std::string cipher = std::get<std::string>(ciphertext.value);
                
                std::cout << "Caesar Cipher Brute Force:\n";
                std::cout << "-------------------------\n";
                
                for (int shift = 0; shift < 26; ++shift) {
                    std::string plaintext = crypto_helpers::caesar_cipher(cipher, -shift);
                    std::cout << "Shift " << shift << ": " << plaintext << "\n";
                }
                
                // Push the original ciphertext back onto the stack
                interp.stack.push_back(ciphertext);
            } else {
                throw std::runtime_error("Type error: caesar_break requires a string or symbol");
            }
        });
        
        // hash: Calculate a hash of a value
        interp.register_op("hash", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on hash");
            }
            
            auto value = interp.stack.back(); interp.stack.pop_back();
            
            // Convert the value to a string representation
            std::string str;
            if (value.type == WofType::String || value.type == WofType::Symbol) {
                str = std::get<std::string>(value.value);
            } else if (value.type == WofType::Integer) {
                str = std::to_string(std::get<int64_t>(value.value));
            } else if (value.type == WofType::Double) {
                str = std::to_string(std::get<double>(value.value));
            }
            
            // Calculate the hash
            uint64_t hash = crypto_helpers::fnv1a_hash(str);
            
            // Push the hash onto the stack
            interp.stack.emplace_back(static_cast<int64_t>(hash));
            
            // Display the hash in hexadecimal
            std::stringstream ss;
            ss << std::hex << std::setw(16) << std::setfill('0') << hash;
            std::cout << "Hash: 0x" << ss.str() << std::endl;
        });
        
        // xor_cipher: Apply XOR cipher to a string with a key
        interp.register_op("xor_cipher", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("Stack underflow on xor_cipher");
            }
            
            auto key = interp.stack.back(); interp.stack.pop_back();
            auto text = interp.stack.back(); interp.stack.pop_back();
            
            if ((text.type != WofType::String && text.type != WofType::Symbol) ||
                (key.type != WofType::String && key.type != WofType::Symbol)) {
                throw std::runtime_error("Type error: xor_cipher requires string or symbol values");
            }
            
            std::string text_val = std::get<std::string>(text.value);
            std::string key_val = std::get<std::string>(key.value);
            
            std::string result = crypto_helpers::xor_cipher(text_val, key_val);
            
            // Display the result in hexadecimal for better visibility
            std::cout << "XOR cipher result (hex): " << crypto_helpers::to_hex(result) << std::endl;
            
            // Push the result onto the stack
            interp.stack.emplace_back(result);
        });
    }
};

} // namespace woflang

// Plugin registration function
WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::CryptoOpsPlugin plugin;
    plugin.register_ops(interp);
}