// ops_list_math_extended.hpp
// Implements sum, avg, min, max, norm for lists

#pragma once
#include "wof_interpreter.hpp"
#include "wof_value.hpp"
#include <iostream>
#include <cmath>
#include <limits>

void register_list_math_ext(WofInterpreter& vm) {
    // sum
    vm.registerOpcode(3113, [](WofInterpreter& vm, const WofToken&) {
        auto list = vm.popValue();
        if (list.type != WofValue::Type::LIST) return;
        int64_t sum = 0;
        for (const auto& v : list.listVal)
            if (v.type == WofValue::Type::INT) sum += v.intVal;
        vm.push(sum);
    });

    // avg
    vm.registerOpcode(3114, [](WofInterpreter& vm, const WofToken&) {
        auto list = vm.popValue();
        if (list.type != WofValue::Type::LIST || list.listVal.empty()) return;
        int64_t sum = 0;
        for (const auto& v : list.listVal)
            if (v.type == WofValue::Type::INT) sum += v.intVal;
        vm.push(sum / list.listVal.size());
    });

    // min
    vm.registerOpcode(3115, [](WofInterpreter& vm, const WofToken&) {
        auto list = vm.popValue();
        if (list.type != WofValue::Type::LIST) return;
        int64_t result = std::numeric_limits<int64_t>::max();
        for (const auto& v : list.listVal)
            if (v.type == WofValue::Type::INT) result = std::min(result, v.intVal);
        vm.push(result);
    });

    // max
    vm.registerOpcode(3116, [](WofInterpreter& vm, const WofToken&) {
        auto list = vm.popValue();
        if (list.type != WofValue::Type::LIST) return;
        int64_t result = std::numeric_limits<int64_t>::min();
        for (const auto& v : list.listVal)
            if (v.type == WofValue::Type::INT) result = std::max(result, v.intVal);
        vm.push(result);
    });

    // norm (L2)
    vm.registerOpcode(3117, [](WofInterpreter& vm, const WofToken&) {
        auto list = vm.popValue();
        if (list.type != WofValue::Type::LIST) return;
        double acc = 0.0;
        for (const auto& v : list.listVal)
            if (v.type == WofValue::Type::INT) acc += static_cast<double>(v.intVal) * v.intVal;
        vm.pushValue(WofValue(std::sqrt(acc)));
    });
}
