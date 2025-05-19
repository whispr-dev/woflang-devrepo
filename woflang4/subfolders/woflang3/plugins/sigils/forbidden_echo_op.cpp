#include "../../src/core/woflang.hpp"
#include <iostream>

static std::string last_forbidden_message = "";

class ForbiddenEchoOpPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("void_division", [](WoflangInterpreter& interp) {
            last_forbidden_message = "You have peered into the void.";
            if (interp.stack.empty() ||
                ((interp.stack.back().type == WofType::Integer && std::get<int64_t>(interp.stack.back().value) == 0))) {
                std::cout << "∅  " << last_forbidden_message << " (stack erased)" << std::endl;
                interp.clear_stack();
            } else {
                std::cout << "∅  Only the zero can echo the void.\n";
            }
        });
        interp.register_op("forbidden_echo", [](WoflangInterpreter&) {
            if (!last_forbidden_message.empty()) {
                std::cout << "∅∅  Forbidden echo (inverted): " << last_forbidden_message << " (now returned to you)\n";
            } else {
                std::cout << "∅∅  No forbidden op to echo.\n";
            }
        });
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static ForbiddenEchoOpPlugin plugin;
    plugin.register_ops(interp);
}
