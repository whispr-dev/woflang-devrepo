#include "src/core/woflang.hpp"
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    woflang::WoflangInterpreter interp;
    std::cout << "Welcome to Woflang!\n";
    std::string line;
    while (std::cout << "wof> ", std::getline(std::cin, line)) {
        interp.execute_line(line);
    }
}
