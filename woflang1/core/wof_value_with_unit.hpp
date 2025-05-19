// wof_value_with_unit.hpp
// Extended WofValue to support units

#pragma once
#include <string>
#include <variant>
#include <vector>
#include <optional>
#include <iostream>

struct WofUnit {
    std::string symbol;
    double multiplier = 1.0;

    void print() const {
        std::cout << symbol;
    }
};

struct WofValue {
    enum class Type { INT, FLOAT, LIST };

    Type type = Type::INT;
    int64_t intVal = 0;
    double floatVal = 0.0;
    std::vector<WofValue> listVal;
    std::optional<WofUnit> unit;

    WofValue() = default;
    WofValue(int64_t val) : type(Type::INT), intVal(val) {}
    WofValue(double val) : type(Type::FLOAT), floatVal(val) {}
    WofValue(std::vector<WofValue> list) : type(Type::LIST), listVal(std::move(list)) {}

    void print() const {
        if (type == Type::INT)
            std::cout << intVal;
        else if (type == Type::FLOAT)
            std::cout << floatVal;
        else {
            std::cout << "[ ";
            for (const auto& v : listVal) {
                v.print();
                std::cout << " ";
            }
            std::cout << "]";
        }

        if (unit) {
            std::cout << " ";
            unit->print();
        }
    }
};
