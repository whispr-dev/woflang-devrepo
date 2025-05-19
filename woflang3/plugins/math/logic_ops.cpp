#include "../../src/core/woflang.hpp"
#include <iostream>

class LogicOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("∧", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) { std::cout << "AND: need 2 bool/int\n"; return; }
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();
            if (a.type == WofType::Integer && b.type == WofType::Integer)
                interp.stack.emplace_back((std::get<int64_t>(a.value) && std::get<int64_t>(b.value)) ? 1 : 0);
            else std::cout << "AND: int/bool only\n";
        });
        interp.register_op("∨", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) { std::cout << "OR: need 2 bool/int\n"; return; }
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();
            if (a.type == WofType::Integer && b.type == WofType::Integer)
                interp.stack.emplace_back((std::get<int64_t>(a.value) || std::get<int64_t>(b.value)) ? 1 : 0);
            else std::cout << "OR: int/bool only\n";
        });
        interp.register_op("¬", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) return;
            auto a = interp.stack.back(); interp.stack.pop_back();
            if (a.type == WofType::Integer)
                interp.stack.emplace_back(!std::get<int64_t>(a.value) ? 1 : 0);
            else std::cout << "NOT: int/bool only\n";
        });
        interp.register_op("⊕", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) { std::cout << "XOR: need 2 bool/int\n"; return; }
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();
            if (a.type == WofType::Integer && b.type == WofType::Integer)
                interp.stack.emplace_back((std::get<int64_t>(a.value) ^ std::get<int64_t>(b.value)) ? 1 : 0);
            else std::cout << "XOR: int/bool only\n";
        });
        interp.register_op("⇒", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) { std::cout << "IMPLIES: need 2 bool/int\n"; return; }
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();
            if (a.type == WofType::Integer && b.type == WofType::Integer)
                interp.stack.emplace_back((!std::get<int64_t>(a.value) || std::get<int64_t>(b.value)) ? 1 : 0);
            else std::cout << "IMPLIES: int/bool only\n";
        });
        // ... add more as needed (∀, ∃, etc.)
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static LogicOpsPlugin plugin;
    plugin.register_ops(interp);
}
