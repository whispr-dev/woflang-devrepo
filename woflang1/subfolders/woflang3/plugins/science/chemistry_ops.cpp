#include "../../src/core/woflang.hpp"
#include <iostream>
#include <cmath>

// Adds chemistry glyphs/units and basic stoichiometry ops
class ChemistryOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("mol", [](WoflangInterpreter& interp) {
            if (!interp.stack.empty()) {
                auto v = interp.stack.back(); interp.stack.pop_back();
                std::cout << "Moles: " << (v.type == WofType::Integer ? std::to_string(std::get<int64_t>(v.value)) : "?") << " mol" << std::endl;
            }
        });
        interp.register_op("g", [](WoflangInterpreter& interp) {
            if (!interp.stack.empty()) {
                auto v = interp.stack.back(); interp.stack.pop_back();
                std::cout << "Mass: " << (v.type == WofType::Integer ? std::to_string(std::get<int64_t>(v.value)) : "?") << " g" << std::endl;
            }
        });
        interp.register_op("Na", [](WoflangInterpreter& interp) {
            interp.stack.emplace_back(6.02214076e23); // Avogadro's number
        });
        interp.register_op("M", [](W)_
