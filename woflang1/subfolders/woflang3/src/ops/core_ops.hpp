#pragma once
#include "../core/woflang.hpp"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <cstdlib>

// --- Register all built-in, sacred, meta, and ritual ops ---
inline void register_core_ops(WoflangInterpreter& interp) {
    // Arithmetic
    interp.register_op("+", [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) throw std::runtime_error("Stack underflow on +");
        auto b = interp.stack.back(); interp.stack.pop_back();
        auto a = interp.stack.back(); interp.stack.pop_back();
        if (a.type == WofType::Integer && b.type == WofType::Integer)
            interp.stack.emplace_back(std::get<int64_t>(a.value) + std::get<int64_t>(b.value));
        else if (a.type == WofType::Double && b.type == WofType::Double)
            interp.stack.emplace_back(std::get<double>(a.value) + std::get<double>(b.value));
        else
            throw std::runtime_error("Type error in +");
    });
    // ... (repeat for -, *, /, dup, drop, swap, etc.)

    // --- Sacred/Meta/Hidden Ops (always present, sometimes hidden/discoverable) ---
    interp.register_op("pi", [](WoflangInterpreter& interp) {
        interp.stack.emplace_back(3.14159265358979323846);
    });
    interp.register_op("print", [](WoflangInterpreter& interp) {
        if (!interp.stack.empty()) {
            const auto& v = interp.stack.back();
            if (v.type == WofType::Integer) std::cout << std::get<int64_t>(v.value);
            else if (v.type == WofType::Double) std::cout << std::get<double>(v.value);
            else if (v.type == WofType::String || v.type == WofType::Symbol) std::cout << std::get<std::string>(v.value);
            if (v.unit) std::cout << " " << *v.unit;
            std::cout << std::endl;
        }
    });

    // --- Meta/REPL/Easter Egg Commands ---
    interp.register_op("prophecy", [](WoflangInterpreter&) {
        static std::vector<std::string> prophecies = {
            "In the glyph’s shadow, your stack’s fate is sealed.",
            "Beware: The next push may tip the void.",
            "The stack will echo your intent, not your command.",
            "A silent glyph is the most powerful of all."
        };
        int idx = std::rand() % prophecies.size();
        std::cout << "[Prophecy] " << prophecies[idx] << std::endl;
    });
    interp.register_op("egg", [](WoflangInterpreter&) {
        std::cout << "🥚  You have discovered the Joy Egg! May your stack never underflow!" << std::endl;
    });
    interp.register_op("sigil_map", [](WoflangInterpreter&) {
        std::cout << "Sacred Sigils:\n"
                  << "prophecy (🔮): Cryptic stack fate message\n"
                  << "stack_slayer (☠️): Destroys the stack (forbidden)\n"
                  << "egg (🥚): Joy Easter Egg\n"
                  << "glyph_prophecy (🜄): Secret, full-moon only\n"
                  << "omega (Ω): Session ending\n"
                  << "sigil_map (🗺️): This map\n";
    });
    interp.register_op("entropy", [](WoflangInterpreter& interp) {
        if (interp.stack.empty()) {
            std::cout << "∴  Entropy: 0.0 (empty stack)\n";
            return;
        }
        std::unordered_map<std::string, int> freq;
        for (const auto& v : interp.stack) {
            std::string s;
            if (v.type == WofType::String || v.type == WofType::Symbol)
                s = std::get<std::string>(v.value);
            else if (v.type == WofType::Integer)
                s = std::to_string(std::get<int64_t>(v.value));
            else if (v.type == WofType::Double)
                s = std::to_string(std::get<double>(v.value));
            else
                s = "?";
            freq[s]++;
        }
        double H = 0.0;
        double N = interp.stack.size();
        for (auto& [val, count] : freq) {
            double p = count / N;
            H -= p * std::log2(p);
        }
        std::cout << "∴  Entropy: " << H << "\n";
    });
    interp.register_op("stack_slayer", [](WoflangInterpreter& interp) {
        std::cout << "☠️  The void has claimed your stack! (All items erased)" << std::endl;
        interp.clear_stack();
    });
    interp.register_op("omega", [](WoflangInterpreter&) {
        std::cout << "Ω  All cycles end. The interpreter closes. Until next session, fren!" << std::endl;
        std::exit(0);
    });
    // Add more sacred/hidden/REPL ops as needed, from your manifest
}
