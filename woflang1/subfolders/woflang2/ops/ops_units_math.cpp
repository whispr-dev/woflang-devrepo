// ops_units_math.cpp
// Implements + - * / with unit support in WOFLANG

#include "wof_interpreter.hpp"
#include <iostream>

void register_unit_math_opcodes(WofInterpreter& vm) {
    // Addition: preserves unit if both match
    vm.registerOpcode(10, [](WofInterpreter& vm, const WofToken&) {
        auto b = vm.popValue();
        auto a = vm.popValue();

        if (a.unit && b.unit && a.unit->symbol == b.unit->symbol) {
            if (a.type == WofValue::Type::INT && b.type == WofValue::Type::INT)
                vm.pushValue(WofValue(a.intVal + b.intVal)).unit = a.unit;
            else
                vm.pushValue(WofValue(static_cast<double>(a.intVal) + static_cast<double>(b.intVal))).unit = a.unit;
        } else {
            std::cout << "[unit:add] Unit mismatch or missing, result is unitless.\n";
            vm.pushValue(WofValue(static_cast<double>(a.intVal) + static_cast<double>(b.intVal)));
        }
    });

    // Subtraction: same logic as addition
    vm.registerOpcode(11, [](WofInterpreter& vm, const WofToken&) {
        auto b = vm.popValue();
        auto a = vm.popValue();

        if (a.unit && b.unit && a.unit->symbol == b.unit->symbol)
            vm.pushValue(WofValue(a.intVal - b.intVal)).unit = a.unit;
        else {
            std::cout << "[unit:sub] Unit mismatch or missing, result is unitless.\n";
            vm.pushValue(WofValue(static_cast<double>(a.intVal) - static_cast<double>(b.intVal)));
        }
    });

    // Multiplication: always keeps unit from one operand if only one has it
    vm.registerOpcode(12, [](WofInterpreter& vm, const WofToken&) {
        auto b = vm.popValue();
        auto a = vm.popValue();
        WofValue out;

        if (a.unit && !b.unit) {
            out = WofValue(a.intVal * b.intVal);
            out.unit = a.unit;
        } else if (!a.unit && b.unit) {
            out = WofValue(a.intVal * b.intVal);
            out.unit = b.unit;
        } else {
            out = WofValue(a.intVal * b.intVal); // no unit or ambiguous unit result
        }

        vm.pushValue(out);
    });

    // Division: keeps numerator unit
    vm.registerOpcode(13, [](WofInterpreter& vm, const WofToken&) {
        auto b = vm.popValue();
        auto a = vm.popValue();
        WofValue out;

        out = WofValue(static_cast<double>(a.intVal) / static_cast<double>(b.intVal));
        out.unit = a.unit;

        vm.pushValue(out);
    });
}
