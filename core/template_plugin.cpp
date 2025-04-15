// template_plugin.cpp
// Compile with: g++ -fPIC -shared template_plugin.cpp -o template_plugin.so

#include "wof_interpreter.hpp"
#include <iostream>

extern "C" void register_woflang_plugin(WofInterpreter& vm) {
    const uint16_t opcode_hello = 42001;
    const uint16_t opcode_square = 42002;

    vm.registerOpcode(opcode_hello, [](WofInterpreter& vm, const WofToken&) {
        std::cout << "[plugin] Hello from template plugin!\n";
    });

    vm.registerOpcode(opcode_square, [](WofInterpreter& vm, const WofToken&) {
        int64_t val = vm.pop();
        vm.push(val * val);
        std::cout << "[plugin] Squared: " << val << " -> " << val * val << "\n";
    });
}
