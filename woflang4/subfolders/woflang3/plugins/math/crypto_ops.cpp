#include "../../src/core/woflang.hpp"
#include <iostream>
#include <bitset>

// Example: XOR two integers, modexp, simple hash
class CryptoOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("xor", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) { std::cout << "xor: Need 2 integers\n"; return; }
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();
            if (a.type == WofType::Integer && b.type == WofType::Integer)
                interp.stack.emplace_back(std::get<int64_t>(a.value) ^ std::get<int64_t>(b.value));
            else std::cout << "xor: Integers only\n";
        });
        interp.register_op("modexp", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 3) { std::cout << "modexp: Need 3 ints (a, exp, mod)\n"; return; }
            auto m = interp.stack.back(); interp.stack.pop_back();
            auto e = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();
            if (a.type == WofType::Integer && e.type == WofType::Integer && m.type == WofType::Integer) {
                int64_t base = std::get<int64_t>(a.value);
                int64_t exp = std::get<int64_t>(e.value);
                int64_t mod = std::get<int64_t>(m.value);
                int64_t res = 1;
                for (; exp > 0; exp--) res = (res * base) % mod;
                interp.stack.emplace_back(res);
            } else std::cout << "modexp: Integers only\n";
        });
        interp.register_op("bitdump", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) return;
            auto v = interp.stack.back(); interp.stack.pop_back();
            if (v.type == WofType::Integer)
                std::cout << "Bits: " << std::bitset<64>(std::get<int64_t>(v.value)) << std::endl;
            else std::cout << "bitdump: Integer only\n";
        });
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static CryptoOpsPlugin plugin;
    plugin.register_ops(interp);
}
