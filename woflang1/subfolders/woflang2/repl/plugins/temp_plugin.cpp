#include "wof_interpreter.hpp"
#include <iostream>

void glyph_zap(WofInterpreter& vm) {
    std::cout << "[⚡] ZAP!\n";
    vm.push(42); // Push a value onto the stack
}

extern "C" void register_woflang_plugin(WofInterpreter& vm) {
    std::cout << "[plugin] ⚡ template_plugin loaded.\n";
    vm.registerFunction(U"zap", glyph_zap);
}
