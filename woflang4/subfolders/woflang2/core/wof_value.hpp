// wof_value.hpp
// WOFLANG dynamic value type supporting int and list

#pragma once
#include <vector>
#include <variant>
#include <iostream>

struct WofValue {
    enum class Type { INT, LIST };

    Type type = Type::INT;
    int64_t intVal = 0;
    std::vector<WofValue> listVal;

    WofValue() = default;
    WofValue(int64_t val) : type(Type::INT), intVal(val) {}
    WofValue(std::vector<WofValue> list) : type(Type::LIST), listVal(std::move(list)) {}

    void print() const {
        if (type == Type::INT) {
            std::cout << intVal;
        } else {
            std::cout << "[ ";
            for (const auto& val : listVal) {
                val.print();
                std::cout << " ";
            }
            std::cout << "]";
        }
    }
};
