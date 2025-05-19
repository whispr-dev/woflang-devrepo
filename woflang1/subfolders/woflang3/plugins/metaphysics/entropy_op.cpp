#include "../../src/core/woflang.hpp"
#include <iostream>
#include <unordered_map>
#include <cmath>

class EntropyOpPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("entropy", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                std::cout << "∴  Entropy: 0.0 (empty stack)\n";
                return;
            }
            std::unordered_map<std::string, int> freq;
            for (const auto& v : interp.stack) {
                std::string s;
                if (v.type == WofType::String || v.type == WofType::Symbol)
                    s = v.value.type == WofType::String ? std::get<std::string>(v.value.value) : "";
                else if (v.type == WofType::Integer)
                    s = std::to_string(std::get<int64_t>(v.value));
                else if (v.type == WofType::Double)
                    s = std::to_string(v.value.type == WofType::Double ? std::get<double>(v.value.value) : v.value.type == WofType::Integer ? static_cast<double>(std::get<int64_t>(v.value.value)) : 0.0);
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
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static EntropyOpPlugin plugin;
    plugin.register_ops(interp);
}
