# Add each plugin
add_woflang_plugin(math_constants math_constants.cpp)
add_woflang_plugin(math_greek math_greek.cpp)
add_woflang_plugin(physics_constants load_physics_constants.cpp)
add_woflang_plugin(modelica_constants load_modelica_constants.cpp)
add_woflang_plugin(crypto_ops crypto_ops.cpp)
add_woflang_plugin(quantum_ops quantum_ops.cpp)
add_woflang_plugin(fractal_ops fractal_ops.cpp)
add_woflang_plugin(mathlib_calculus mathlib_calculus.cpp)
add_woflang_plugin(symbolic_simplify ops_symbolic_simplify_rules.cpp)
add_woflang_plugin(symbolic_solve_linear ops_symbolic_solve_linear.cpp)
add_woflang_plugin(kanji_ops kanji_ops.cpp)
add_woflang_plugin(music_ops music_ops.cpp)
add_woflang_plugin(entropy_op entropy_op.cpp)
add_woflang_plugin(prophecy_op prophecy_op.cpp)
add_woflang_plugin(stack_slayer_op stack_slayer_op.cpp)
add_woflang_plugin(void_division_op void_division_op.cpp)
CMakeLists.txt (Tests Directory)
cmake# Tests CMakeLists.txt

# Test runner executable
add_executable(woflang_test_runner woflang_test_runner.cpp)
target_link_libraries(woflang_test_runner PRIVATE woflang_core)

# Copy test scripts to binary directory
file(GLOB TEST_SCRIPTS "*.wof")
foreach(script ${TEST_SCRIPTS})
    get_filename_component(script_name ${script} NAME)
    configure_file(${script} ${CMAKE_BINARY_DIR}/tests/${script_name} COPYONLY)
endforeach()

# Add test to CTest
add_test(NAME WoflangTests COMMAND woflang_test_runner)
Plugin API Standardization
To ensure all plugins follow a consistent pattern, we should create a plugin template that all new plugins can use:
plugin_template.cpp
cpp#include "../../src/core/woflang.hpp"
#include <iostream>

// Plugin class name should describe its purpose
class ExamplePlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        // Register ops with descriptive lambda names
        interp.register_op("example_op", [](WoflangInterpreter& interp) {
            // 1. Check stack size
            if (interp.stack.size() < 1) {
                std::cout << "example_op: Needs at least one value\n";
                return;
            }
            
            // 2. Pop values safely
            auto v = interp.stack.back();
            interp.stack.pop_back();
            
            // 3. Type check
            if (v.type != WofType::Integer) {
                std::cout << "example_op: Expected integer\n";
                interp.stack.push_back(v); // Put it back
                return;
            }
            
            // 4. Perform operation
            int64_t val = std::get<int64_t>(v.value);
            
            // 5. Push result
            interp.stack.emplace_back(val * 2);
            
            // 6. Optional: Print info/feedback
            std::cout << "example_op: Doubled the value\n";
        });
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static ExamplePlugin plugin;
    plugin.register_ops(interp);
            }
    std::cout << "mandelbrot: imag must be a number\n";
                return;
            }
            
            double real = 0.0;
            if (real_val.type == WofType::Double) {
                real = std::get<double>(real_val.value);
            } else if (real_val.type == WofType::Integer) {
                real = static_cast<double>(std::get<int64_t>(real_val.value));
            } else {
                std::cout << "mandelbrot: real must be a number\n";
                return;
            }

            // Calculate Mandelbrot set membership
            double x = 0.0, y = 0.0;
            int iter = 0;
            while (x*x + y*y <= 4.0 && iter < max_iter) {
                double xt = x*x - y*y + real;
                y = 2*x*y + imag;
                x = xt;
                ++iter;
            }
            std::cout << "Mandelbrot set? " << (iter == max_iter ? "YES" : "NO") << std::endl;
        
        
        interp.register_op("sierpinski", [](WoflangInterpreter& interp) {
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
