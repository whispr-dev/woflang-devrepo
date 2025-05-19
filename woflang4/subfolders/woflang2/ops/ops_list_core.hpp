// ops_list_core.hpp
// Implements core list operations: length, get, append

#pragma once
#include "wof_interpreter.hpp"
#include "wof_value.hpp"
#include <iostream>

void register_list_opcodes(WofInterpreter& vm) {
    // length
    vm.registerOpcode(3100, [](WofInterpreter& vm, const WofToken&) {
        auto list = vm.popValue();
        if (list.type != WofValue::Type::LIST) {
            std::cerr << "[list] length expects a list\n";
            return;
        }
        vm.push(list.listVal.size());
    });

    // get
    vm.registerOpcode(3101, [](WofInterpreter& vm, const WofToken&) {
        int64_t index = vm.pop();
        auto list = vm.popValue();
        if (list.type != WofValue::Type::LIST || index < 0 || index >= list.listVal.size()) {
            std::cerr << "[list] get out of bounds or wrong type\n";
            return;
        }
        vm.pushValue(list.listVal[index]);
    });

    // append
    vm.registerOpcode(3102, [](WofInterpreter& vm, const WofToken&) {
        auto item = vm.popValue();
        auto list = vm.popValue();
        if (list.type != WofValue::Type::LIST) {
            std::cerr << "[list] append requires list target\n";
            return;
        }
        list.listVal.push_back(item);
        vm.pushValue(list);
    });
}
