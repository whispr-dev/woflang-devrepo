// ops_list_hof.hpp
// Higher-order list operations for WOFLANG

#pragma once
#include "wof_interpreter.hpp"
#include "wof_value.hpp"
#include <iostream>
#include <functional>

// Utility to apply a unary op to each list element
std::vector<WofValue> applyUnary(const std::vector<WofValue>& list, std::function<WofValue(const WofValue&)> f) {
    std::vector<WofValue> result;
    for (const auto& v : list) {
        result.push_back(f(v));
    }
    return result;
}

// Utility to reduce a list to a single value
WofValue reduceList(const std::vector<WofValue>& list, std::function<WofValue(WofValue, WofValue)> f) {
    if (list.empty()) return WofValue(0);
    WofValue acc = list[0];
    for (size_t i = 1; i < list.size(); ++i) {
        acc = f(acc, list[i]);
    }
    return acc;
}

void register_hof_list_opcodes(WofInterpreter& vm) {
    // map: applies a simple operation (e.g. double each value)
    vm.registerOpcode(3110, [](WofInterpreter& vm, const WofToken&) {
        auto list = vm.popValue();
        if (list.type != WofValue::Type::LIST) {
            std::cerr << "[list] map expects a list\n";
            return;
        }

        auto mapped = applyUnary(list.listVal, [](const WofValue& v) -> WofValue {
            if (v.type == WofValue::Type::INT) return WofValue(v.intVal * 2);
            return v;
        });

        vm.pushValue(WofValue(mapped));
    });

    // reduce: adds all elements
    vm.registerOpcode(3111, [](WofInterpreter& vm, const WofToken&) {
        auto list = vm.popValue();
        if (list.type != WofValue::Type::LIST) {
            std::cerr << "[list] reduce expects a list\n";
            return;
        }

        auto sum = reduceList(list.listVal, [](WofValue a, WofValue b) {
            if (a.type == WofValue::Type::INT && b.type == WofValue::Type::INT)
                return WofValue(a.intVal + b.intVal);
            return a;
        });

        vm.pushValue(sum);
    });

    // dot: dot product of two int lists
    vm.registerOpcode(3112, [](WofInterpreter& vm, const WofToken&) {
        auto b = vm.popValue();
        auto a = vm.popValue();

        if (a.type != WofValue::Type::LIST || b.type != WofValue::Type::LIST) {
            std::cerr << "[list] dot requires two lists\n";
            return;
        }

        const auto& av = a.listVal;
        const auto& bv = b.listVal;

        if (av.size() != bv.size()) {
            std::cerr << "[list] dot size mismatch\n";
            return;
        }

        int64_t total = 0;
        for (size_t i = 0; i < av.size(); ++i) {
            if (av[i].type == WofValue::Type::INT && bv[i].type == WofValue::Type::INT) {
                total += av[i].intVal * bv[i].intVal;
            }
        }

        vm.pushValue(WofValue(total));
    });
}
