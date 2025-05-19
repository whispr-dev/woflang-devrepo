#include "logic_ops.hpp"

WOFLANG_PLUGIN_EXPORT void register_logic_ops(WoflangInterpreter& interpreter) {
    REGISTER_OP("and", [](WoflangInterpreter& wof) {
        auto b = wof.pop_bool();
        auto a = wof.pop_bool();
        wof.push_bool(a && b);
    });

    REGISTER_OP("or", [](WoflangInterpreter& wof) {
        auto b = wof.pop_bool();
        auto a = wof.pop_bool();
        wof.push_bool(a || b);
    });

    REGISTER_OP("xor", [](WoflangInterpreter& wof) {
        auto b = wof.pop_bool();
        auto a = wof.pop_bool();
        wof.push_bool(a != b);
    });

    REGISTER_OP("not", [](WoflangInterpreter& wof) {
        auto a = wof.pop_bool();
        wof.push_bool(!a);
    });

    REGISTER_OP("eq", [](WoflangInterpreter& wof) {
        auto b = wof.pop();
        auto a = wof.pop();
        wof.push_bool(a == b);
    });

    REGISTER_OP("ne", [](WoflangInterpreter& wof) {
        auto b = wof.pop();
        auto a = wof.pop();
        wof.push_bool(a != b);
    });

    REGISTER_OP("gt", [](WoflangInterpreter& wof) {
        auto b = wof.pop();
        auto a = wof.pop();
        wof.push_bool(a > b);
    });

    REGISTER_OP("lt", [](WoflangInterpreter& wof) {
        auto b = wof.pop();
        auto a = wof.pop();
        wof.push_bool(a < b);
    });

    REGISTER_OP("gte", [](WoflangInterpreter& wof) {
        auto b = wof.pop();
        auto a = wof.pop();
        wof.push_bool(a >= b);
    });

    REGISTER_OP("lte", [](WoflangInterpreter& wof) {
        auto b = wof.pop();
        auto a = wof.pop();
        wof.push_bool(a <= b);
    });
}
