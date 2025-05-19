// wof_interpreter.cpp
#include "wof_interpreter.hpp"

void WofInterpreter::push(int64_t val) {
    valueStack.push_back(WofValue{WofValue::INT, val, {}});
}

void WofInterpreter::pushValue(const WofValue& val) {
    valueStack.push_back(val);
}

WofValue WofInterpreter::popValue() {
    if (valueStack.empty()) {
        std::cerr << "Pop from empty valueStack!\n";
        return WofValue{WofValue::INT, 0, {}};
    }
    WofValue v = valueStack.back();
    valueStack.pop_back();
    return v;
}

void WofInterpreter::execute(const std::u32string& code) {
    std::cout << "[exec] Received code (stubbed).
";
}

void WofInterpreter::loadPlugin(const std::string& path) {
    std::cout << "[plugin] Stub loading: " << path << std::endl;
}

void WofInterpreter::findBlockEnd() {
    std::cout << "[blocks] Stub find block end.
";
}
