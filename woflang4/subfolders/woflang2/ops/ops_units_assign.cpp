// ops_units_assign.cpp
// Implements `assign_unit`: assigns unit from stack to previous value

#include "wof_interpreter.hpp"
#include "wof_units.hpp"
#include <iostream>

void register_unit_assignment(WofInterpreter& vm, UnitRegistry& reg) {
    vm.registerOpcode(3140, [&reg](WofInterpreter& vm, const WofToken&) {
        auto unitToken = vm.popValue();
        auto value = vm.popValue();

        if (unitToken.type != WofValue::Type::LIST && unitToken.type != WofValue::Type::INT) {
            std::cerr << "[unit] invalid unit type" << std::endl;
            vm.pushValue(value);
            return;
        }

        std::string symbol;

        if (unitToken.type == WofValue::Type::LIST && !unitToken.listVal.empty()) {
            auto sym = unitToken.listVal[0];
            if (sym.type == WofValue::Type::INT) {
                symbol = std::to_string(sym.intVal);
            } else if (std::holds_alternative<std::string>(sym.value)) {
                symbol = std::get<std::string>(sym.value);
            }
        } else if (unitToken.type == WofValue::Type::INT) {
            symbol = std::to_string(unitToken.intVal);
        }

        const WofUnit* u = reg.get(symbol);
        if (!u) {
            std::cerr << "[unit] unknown unit symbol: " << symbol << std::endl;
            vm.pushValue(value);
            return;
        }

        value.unit = *u;
        vm.pushValue(value);
        std::cout << "[unit] assigned " << symbol << std::endl;
    });
}
