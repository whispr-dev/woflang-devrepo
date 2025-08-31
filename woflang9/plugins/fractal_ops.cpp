// plugins/fractal_ops.cpp
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

static int mandelbrot_iters(double cr, double ci, int max_iter) {
    double zr=0.0, zi=0.0;
    int i=0;
    while(i<max_iter){
        double zr2 = zr*zr - zi*zi + cr;
        double zi2 = 2.0*zr*zi + ci;
        zr = zr2; zi = zi2;
        if (zr*zr + zi*zi > 4.0) break;
        ++i;
    }
    return i;
}

static int julia_iters(double zr, double zi, double cr, double ci, int max_iter) {
    int i=0;
    while(i<max_iter){
        double zr2 = zr*zr - zi*zi + cr;
        double zi2 = 2.0*zr*zi + ci;
        zr = zr2; zi = zi2;
        if (zr*zr + zi*zi > 4.0) break;
        ++i;
    }
    return i;
}

static inline double need_num(const WofValue& v, const char* op){
    if (!v.is_numeric()) throw std::runtime_error(std::string(op)+": numeric required");
    return v.as_numeric();
}

class FractalOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& I) override {

        // cr ci max_iter mandelbrot -> iters
        I.register_op("mandelbrot", [](std::stack<WofValue>& S){
            if (S.size() < 3) throw std::runtime_error("mandelbrot: need cr ci max_iter");
            auto maxV = S.top(); S.pop();
            auto ciV  = S.top(); S.pop();
            auto crV  = S.top(); S.pop();
            int it = mandelbrot_iters(need_num(crV,"mandelbrot"),
                                      need_num(ciV,"mandelbrot"),
                                      static_cast<int>(need_num(maxV,"mandelbrot")));
            S.push(WofValue(static_cast<double>(it)));
        });

        // zr zi cr ci max_iter julia -> iters
        I.register_op("julia", [](std::stack<WofValue>& S){
            if (S.size() < 5) throw std::runtime_error("julia: need zr zi cr ci max_iter");
            auto maxV = S.top(); S.pop();
            auto ciV  = S.top(); S.pop();
            auto crV  = S.top(); S.pop();
            auto ziV  = S.top(); S.pop();
            auto zrV  = S.top(); S.pop();
            int it = julia_iters(need_num(zrV,"julia"),
                                 need_num(ziV,"julia"),
                                 need_num(crV,"julia"),
                                 need_num(ciV,"julia"),
                                 static_cast<int>(need_num(maxV,"julia")));
            S.push(WofValue(static_cast<double>(it)));
        });
    }
};

} // namespace woflang

WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::FractalOpsPlugin plugin;
    plugin.register_ops(interp);
}
