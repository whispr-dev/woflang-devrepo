// ops_symbolic_simplify_rules.cpp
// Implements basic symbolic simplification patterns

#include "wof_symbolic.hpp"
#include <optional>
#include <string>

bool isVar(const WofSymbol& sym, const std::string& name) {
    return std::holds_alternative<std::string>(sym.value) &&
           std::get<std::string>(sym.value) == name;
}

bool isLit(const WofSymbol& sym, int64_t val) {
    return std::holds_alternative<int64_t>(sym.value) &&
           std::get<int64_t>(sym.value) == val;
}

std::optional<WofSymbol> simplifyAdd(const WofSymbol& expr) {
    if (!std::holds_alternative<std::vector<WofSymbol>>(expr.value)) return std::nullopt;
    const auto& tree = std::get<std::vector<WofSymbol>>(expr.value);
    if (tree.size() != 3) return std::nullopt;
    
    const auto& lhs = tree[0];
    const auto& op = tree[1];
    const auto& rhs = tree[2];

    if (!std::holds_alternative<std::string>(op.value)) return std::nullopt;
    if (std::get<std::string>(op.value) != "+") return std::nullopt;

    // X + X → 2X
    if (lhs.value == rhs.value && std::holds_alternative<std::string>(lhs.value)) {
        return WofSymbol{
            std::vector<WofSymbol>{
                WofSymbol{2},
                WofSymbol{"*"},
                lhs
            }
        };
    }

    // X + 0 → X
    if (isLit(rhs, 0)) return lhs;
    if (isLit(lhs, 0)) return rhs;

    return std::nullopt;
}
