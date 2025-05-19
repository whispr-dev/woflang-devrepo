// wof_interpreter.cpp
#include "wof_interpreter.hpp"
#include <iostream> // Included for std::cerr and std::cout

void WofInterpreter::push(int64_t val) {
    valueStack.push_back(WofValue{WofValue::INT, val, {}});
}

void WofInterpreter::pushValue(const WofValue& val) {
    valueStack.push_back(val);
}

WofValue WofInterpreter::popValue() {
    if (valueStack.empty()) {
        // Corrected: Escaping newline in string literal
        std::cerr << "Pop from empty valueStack!\\n";
        return WofValue{WofValue::INT, 0, {}};
    }
    WofValue v = valueStack.back();
    valueStack.pop_back();
    return v;
}

void WofInterpreter::execute(const std::u32string& code) {
    // Corrected: Escaping newline in string literal
    std::cout << "[exec] Received code (stubbed).\\n";
}

void WofInterpreter::loadPlugin(const std::string& path) {
    std::cout << "[plugin] Stub loading: " << path << std::endl;
}

void WofInterpreter::findBlockEnd() {
    // Corrected: Escaping newline in string literal
    std::cout << "[blocks] Stub find block end.\\n";
}