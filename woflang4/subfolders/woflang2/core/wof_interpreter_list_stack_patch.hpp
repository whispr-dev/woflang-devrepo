// wof_interpreter_list_stack_patch.hpp
// Adds pushValue/popValue to WofInterpreter for list support

#pragma once
#include "wof_value.hpp"
#include <stack>
#include <stdexcept>

class WofInterpreter {
public:
    std::stack<WofValue> valueStack;

    void push(int64_t val) {
        valueStack.push(WofValue(val));
    }

    void pushValue(const WofValue& val) {
        valueStack.push(val);
    }

    WofValue popValue() {
        if (valueStack.empty()) throw std::runtime_error("popValue: stack underflow");
        WofValue v = valueStack.top();
        valueStack.pop();
        return v;
    }

    int64_t pop() {
        WofValue v = popValue();
        if (v.type != WofValue::Type::INT) throw std::runtime_error("pop: not an int");
        return v.intVal;
    }

    size_t stackSize() const {
        return valueStack.size();
    }

    void printStack() {
        std::cout << "[STACK] Top → ";
        std::stack<WofValue> temp = valueStack;
        std::vector<WofValue> reversed;
        while (!temp.empty()) {
            reversed.push_back(temp.top());
            temp.pop();
        }
        for (auto it = reversed.rbegin(); it != reversed.rend(); ++it) {
            it->print();
            std::cout << " ";
        }
        std::cout << "\n";
    }
};
