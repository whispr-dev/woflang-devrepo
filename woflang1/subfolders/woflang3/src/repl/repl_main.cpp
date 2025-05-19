#include "woflang.hpp"
#include "repl_helpers.hpp"
#include "repl_extras.cpp"
#include <iostream>
#include <string>

int main() {
    WoflangInterpreter interp;
    register_core_ops(interp); // from core_ops.hpp
    register_repl_extras(interp); // meta/repl extras
    interp.load_plugins("plugins"); // Autoload all plugins

    std::cout << "WOFLANG 2 - Sacred Stack REPL\n";
    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;
        try {
            interp.run_line(line);
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    return 0;
}
