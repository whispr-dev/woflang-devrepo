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
#include <stack>
#include <stdexcept>

namespace woflang {
static int mandelbrot_iters(double cr,double ci,int max_iter){
    double zr=0,zi=0; int i=0;
    while(i<max_iter){
        double zr2=zr*zr-zi*zi+cr;
        double zi2=2*zr*zi+ci;
        zr=zr2; zi=zi2;
        if(zr*zr+zi*zi>4.0) break;
        ++i;
    }
    return i;
}
static int julia_iters(double zr,double zi,double cr,double ci,int max_iter){
    int i=0;
    while(i<max_iter){
        double zr2=zr*zr-zi*zi+cr;
        double zi2=2*zr*zi+ci;
        zr=zr2; zi=zi2;
        if(zr*zr+zi*zi>4.0) break;
        ++i;
    }
    return i;
}
static inline double need_num(const WofValue& v,const char* op){
    if(!v.is_numeric()) throw std::runtime_error(std::string(op)+": numeric required");
    return v.as_numeric();
}
}

WOFLANG_PLUGIN_EXPORT void init_plugin(woflang::WoflangInterpreter::OpTable* ops){
    using namespace woflang;
    if (!ops) return;

    (*ops)["mandelbrot"] = [](std::stack<WofValue>& S){
        auto m=S.top(); S.pop(); auto ci=S.top(); S.pop(); auto cr=S.top(); S.pop();
        int it = mandelbrot_iters(need_num(cr,"mandelbrot"), need_num(ci,"mandelbrot"), (int)need_num(m,"mandelbrot"));
        S.push(WofValue((double)it));
    };
    (*ops)["julia"] = [](std::stack<WofValue>& S){
        auto m=S.top(); S.pop(); auto ci=S.top(); S.pop(); auto cr=S.top(); S.pop(); auto zi=S.top(); S.pop(); auto zr=S.top(); S.pop();
        int it = julia_iters(need_num(zr,"julia"), need_num(zi,"julia"), need_num(cr,"julia"), need_num(ci,"julia"), (int)need_num(m,"julia"));
        S.push(WofValue((double)it));
    };
}
