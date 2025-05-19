#include "../../src/core/woflang.hpp"
#include <cmath>
#include <iostream>

// Adds Greek-letter ops (π, σ, Δ, etc.) as alternate math ops/consts
class MathGreekPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("π", [](WoflangInterpreter& interp) {
            interp.stack.emplace_back(3.14159265358979323846);
        });
        interp.register_op("σ", [](WoflangInterpreter& interp) {
            // Example: stack standard deviation for demo
            if (interp.stack.empty()) { std::cout << "σ: Stack empty\n"; return; }
            double mean = 0.0;
            int n = 0;
            for (auto& v : interp.stack) {
                if (v.type == WofType::Double)
                    mean += std::get<double>(v.value), n++;
                else if (v.type == WofType::Integer)
                    mean += static_cast<double>(std::get<int64_t>(v.value)), n++;
            }
            if (n == 0) { std::cout << "σ: No numbers on stack\n"; return; }
            mean /= n;
            double sumsq = 0.0;
            for (auto& v : interp.stack) {
                double x = v.type == WofType::Double ? std::get<double>(v.value) :
                            v.type == WofType::Integer ? static_cast<double>(std::get<int64_t>(v.value)) : 0.0;
                sumsq += (x - mean) * (x - mean);
            }
            std::cout << "σ (stddev): " << std::sqrt(sumsq / n) << std::endl;
        });
        interp.register_op("Δ", [](WoflangInterpreter& interp) {
            // Δ: Difference of top two numbers
            if (interp.stack.size() < 2) { std::cout << "Δ: Need 2 numbers\n"; return; }
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();
            double da = a.type == WofType::Double ? std::get<double>(a.value) :
                        a.type == WofType::Integer ? static_cast<double>(std::get<int64_t>(a.value)) : 0.0;
            double db = b.type == WofType::Double ? std::get<double>(b.value) :
                        b.type == WofType::Integer ? static_cast<double>(b.value) : 0.0;
            interp.stack.emplace_back(da - db);
        });
        // Add any more Greek/math glyphs you want!
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static MathGreekPlugin plugin;
    plugin.register_ops(interp);
}
