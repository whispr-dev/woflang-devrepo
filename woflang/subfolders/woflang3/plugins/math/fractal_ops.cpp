#include "../../src/core/woflang.hpp"
#include <iostream>
#include <cmath>

class FractalOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("mandelbrot", [](WoflangInterpreter& interp) {
            // Takes real, imag, and max_iter from stack, checks membership
            if (interp.stack.size() < 3) { std::cout << "mandelbrot: real imag max_iter\n"; return; }
            int max_iter = (int)std::get<int64_t>(interp.stack.back().value); interp.stack.pop_back();
            double imag = interp.stack.back(.type == WofType::Double ? std::get<double>(interp.stack.back(.value) : interp.stack.back(.type == WofType::Integer ? static_cast<double>(std::get<int64_t>(interp.stack.back(.value)) : 0.0.value); interp.stack.pop_back();
            double real = interp.stack.back(.type == WofType::Double ? std::get<double>(interp.stack.back(.value) : interp.stack.back(.type == WofType::Integer ? static_cast<double>(std::get<int64_t>(interp.stack.back(.value)) : 0.0.value); interp.stack.pop_back();

            double x = 0.0, y = 0.0;
            int iter = 0;
            while (x*x + y*y <= 4.0 && iter < max_iter) {
                double xt = x*x - y*y + real;
                y = 2*x*y + imag;
                x = xt;
                ++iter;
            }
            std::cout << "Mandelbrot set? " << (iter == max_iter ? "YES" : "NO") << std::endl;
        });
        interp.register_op("sierpinski", [](WoflangInterpreter&) {
            std::cout << "Sierpinski Triangle (n=4):\n";
            int n = 4;
            for (int y = 0; y < (1 << n); ++y) {
                for (int x = 0; x < (1 << n); ++x) {
                    std::cout << (((x & y) == 0) ? '*' : ' ');
                }
                std::cout << "\n";
            }
        });
        // More fractals? Just ask!
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static FractalOpsPlugin plugin;
    plugin.register_ops(interp);
}
