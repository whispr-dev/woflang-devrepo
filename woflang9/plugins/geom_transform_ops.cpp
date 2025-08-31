// plugins/geom_transform_ops.cpp
#ifndef WOFLANG_PLUGIN_EXPORT
#  ifdef _WIN32
#    define WOFLANG_PLUGIN_EXPORT extern "C" __declspec(dllexport)
#  else
#    define WOFLANG_PLUGIN_EXPORT extern "C"
#  endif
#endif

#include "core/woflang.hpp"
#include <cmath>
#include <stdexcept>
#include <stack>

namespace woflang {

static inline double deg2rad(double d){ return d * 3.141592653589793238462643383279502884 / 180.0; }
static inline double need_num(const WofValue& v, const char* op){
    if (!v.is_numeric()) throw std::runtime_error(std::string(op)+": numeric required");
    return v.as_numeric();
}

class GeomTransformOps : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& I) override {

        // x y angle_deg rotate2d -> x' y'
        I.register_op("rotate2d", [](std::stack<WofValue>& S){
            if (S.size() < 3) throw std::runtime_error("rotate2d: need x y angle_deg");
            auto angV = S.top(); S.pop();
            auto yV   = S.top(); S.pop();
            auto xV   = S.top(); S.pop();
            double x = need_num(xV, "rotate2d");
            double y = need_num(yV, "rotate2d");
            double a = deg2rad(need_num(angV, "rotate2d"));
            double c = std::cos(a), s = std::sin(a);
            S.push(WofValue(c*x - s*y));
            S.push(WofValue(s*x + c*y));
        });

        // x y dx dy translate2d -> x' y'
        I.register_op("translate2d", [](std::stack<WofValue>& S){
            if (S.size() < 4) throw std::runtime_error("translate2d: need x y dx dy");
            auto dyV = S.top(); S.pop();
            auto dxV = S.top(); S.pop();
            auto yV  = S.top(); S.pop();
            auto xV  = S.top(); S.pop();
            double x = need_num(xV, "translate2d");
            double y = need_num(yV, "translate2d");
            double dx = need_num(dxV, "translate2d");
            double dy = need_num(dyV, "translate2d");
            S.push(WofValue(x + dx));
            S.push(WofValue(y + dy));
        });

        // x y sx sy scale2d -> x' y'
        I.register_op("scale2d", [](std::stack<WofValue>& S){
            if (S.size() < 4) throw std::runtime_error("scale2d: need x y sx sy");
            auto syV = S.top(); S.pop();
            auto sxV = S.top(); S.pop();
            auto yV  = S.top(); S.pop();
            auto xV  = S.top(); S.pop();
            double x = need_num(xV, "scale2d");
            double y = need_num(yV, "scale2d");
            double sx = need_num(sxV, "scale2d");
            double sy = need_num(syV, "scale2d");
            S.push(WofValue(x * sx));
            S.push(WofValue(y * sy));
        });

        // x y reflect_x -> x' y'
        I.register_op("reflect_x", [](std::stack<WofValue>& S){
            if (S.size() < 2) throw std::runtime_error("reflect_x: need x y");
            auto yV = S.top(); S.pop();
            auto xV = S.top(); S.pop();
            double x = need_num(xV, "reflect_x");
            double y = need_num(yV, "reflect_x");
            S.push(WofValue(x));
            S.push(WofValue(-y));
        });

        // x y reflect_y -> x' y'
        I.register_op("reflect_y", [](std::stack<WofValue>& S){
            if (S.size() < 2) throw std::runtime_error("reflect_y: need x y");
            auto yV = S.top(); S.pop();
            auto xV = S.top(); S.pop();
            double x = need_num(xV, "reflect_y");
            double y = need_num(yV, "reflect_y");
            S.push(WofValue(-x));
            S.push(WofValue(y));
        });
    }
};

} // namespace woflang

WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::GeomTransformOps plugin;
    plugin.register_ops(interp);
}
