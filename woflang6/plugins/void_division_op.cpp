#include "../src/core/woflang.hpp"
#include <iostream>
#include <limits>

namespace woflang {

class VoidDivisionOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("void_division", [](WoflangInterpreter& interp) {
            std::cout << "⚠️  FORBIDDEN OPERATION DETECTED ⚠️\n";
            std::cout << "Attempting to divide by the void...\n";
            
            if (interp.stack.size() < 2) {
                std::cout << "The void requires a sacrifice.\n";
                return;
            }
            
            auto divisor = interp.pop();
            auto dividend = interp.pop();
            
            std::cout << "Dividing " << dividend.to_string() 
                     << " by the essence of nothingness...\n";
            
            // The void consumes all
            interp.clear_stack();
            
            // But leaves behind infinity
            interp.push(WofValue(std::numeric_limits<double>::infinity()));
            
            std::cout << "The operation succeeds. Infinity remains.\n";
            std::cout << "You have gazed into the abyss.\n";
        });
        
        interp.register_op("/0", [](WoflangInterpreter& interp) {
            // Shorthand for void division
            if (interp.stack.size() < 1) {
                std::cout << "Even the void requires something to consume.\n";
                return;
            }
            
            auto value = interp.pop();
            
            std::cout << "÷0: " << value.to_string() << " → ∞\n";
            interp.push(WofValue(std::numeric_limits<double>::infinity()));
        });
    }
};

} // namespace woflang

WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::VoidDivisionOpsPlugin plugin;
    plugin.register_ops(interp);
}