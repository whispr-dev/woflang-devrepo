Building the WofLang Ecosystem: A Guide for Developers
Introduction
This guide provides practical information for developers interested in extending, modifying, or working with the WofLang programming language. Whether you're looking to create plugins, contribute to the core codebase, or simply understand the internal architecture in more depth, this document will help you navigate the WofLang ecosystem.
Setting Up the Development Environment
Prerequisites
To work with WofLang, you'll need:

C++23 compatible compiler:

GCC 11+ on Linux
Clang 14+ on macOS
MSVC 2019+ on Windows


Build tools:

CMake 3.16+
Ninja (optional but recommended)


SIMD support (optional):

AVX2 or AVX512 on x86_64
NEON on ARM


Development libraries:

Unicode libraries (ICU)
Dynamic loading (dl on Linux, Windows API)



Getting the Source Code
Clone the WofLang repository:
bashgit clone https://github.com/ryo-modular/woflang.git
cd woflang
Building from Source
Linux/macOS
bashmkdir build
cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ..
ninja
Windows
cmdmkdir build
cd build
cmake -G "Visual Studio 16 2019" -A x64 ..
cmake --build . --config Debug
Running Tests
bashcd build
ctest -V
Core Architecture Overview
Understanding the WofLang architecture is crucial for effective development:
Layered Design
WofLang is organized into several layers:

Core Layer: Fundamental stack and value types
Execution Layer: Interpreter and evaluation engine
Parser Layer: Tokenization and syntax processing
Plugin Layer: Extension mechanism
REPL/CLI Layer: User interaction

Key Components
The main components and their responsibilities:

WoflangInterpreter: Central class that manages execution
WofValue: Represents values on the stack
TokenParser: Handles tokenization and parsing
PluginLoader: Manages dynamic plugin loading
OperationRegistry: Stores and dispatches operations

Data Flow

Input (string) → Tokenizer (SIMD-accelerated)
Tokens → Parser → Operations
Operations → Interpreter → Stack Manipulation
Stack → Result Extraction

Developing WofLang Plugins
Plugins are the primary mechanism for extending WofLang's functionality.
Plugin Basics
A WofLang plugin is a dynamically loaded library that registers new operations with the interpreter.
Plugin Structure
A minimal plugin requires:

Including the WofLang plugin header
Defining a class that inherits from WoflangPlugin
Implementing the register_ops method
Exporting the register_plugin function

Example Plugin
Here's a simple plugin that adds a factorial operation:
cpp// factorial_plugin.cpp
#include "woflang.hpp"

namespace woflang {

class FactorialPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        // Register the factorial operation
        interp.register_op("fact", [](WoflangInterpreter& interp) {
            // Get the top value from the stack
            auto n = interp.pop().as<int64_t>();
            
            // Calculate factorial
            int64_t result = 1;
            for (int64_t i = 2; i <= n; ++i) {
                result *= i;
            }
            
            // Push the result back onto the stack
            interp.push(result);
        });
        
        // Register a Unicode symbol for the operation
        interp.register_op("！", "fact");
    }
    
    std::string get_name() const override {
        return "Factorial Plugin";
    }
};

} // namespace woflang

// Export the plugin registration function
WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::FactorialPlugin plugin;
    plugin.register_ops(interp);
}
Building the Plugin
Use CMake to build your plugin:
cmake# CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(factorial_plugin)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find WofLang package
find_package(WofLang REQUIRED)

# Create shared library
add_library(factorial_plugin SHARED factorial_plugin.cpp)
target_link_libraries(factorial_plugin PRIVATE WofLang::Core)

# Set output directory
set_target_properties(factorial_plugin PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins"
)
Testing Your Plugin

Build your plugin
Place the resulting shared library in the WofLang plugins directory
Run WofLang with the --list-plugins flag to verify loading
Test your operations in the REPL

Advanced Development Topics
Stack Management Best Practices
When developing operations for WofLang, follow these stack management guidelines:

Type Safety: Always check the types of values before operating on them
Underflow Protection: Verify the stack has enough elements before popping
Error Propagation: Push error values rather than crashing on invalid input
Stack Discipline: Maintain proper stack balance in all code paths

Example of proper stack handling:
cppinterp.register_op("safe_divide", [](WoflangInterpreter& interp) {
    // Check stack size
    if (interp.stack_size() < 2) {
        interp.push_error("Stack underflow: safe_divide requires two arguments");
        return;
    }
    
    // Get values with type checking
    auto b = interp.pop();
    auto a = interp.pop();
    
    if (b.type != WofValue::Type::Number || a.type != WofValue::Type::Number) {
        interp.push_error("Type error: safe_divide requires numeric arguments");
        return;
    }
    
    // Check for division by zero
    if (b.as<double>() == 0.0) {
        interp.push_error("Runtime error: division by zero");
        return;
    }
    
    // Perform the operation and push result
    interp.push(a.as<double>() / b.as<double>());
});
Extending the Core
To modify the WofLang core (not recommended unless necessary):

Understand the core architecture deeply
Follow the existing code style and patterns
Add comprehensive tests for all changes
Document the changes in the code and external docs
Ensure backward compatibility

Performance Optimization
When optimizing WofLang code:

Profile First: Use tools like perf, VTune, or tracy to identify bottlenecks
SIMD Opportunities: Look for vector operations on large data sets
Memory Management: Minimize allocations in hot paths
Cache Locality: Organize data for optimal cache usage

Specialty Domain Implementation
Guidelines for implementing specialized domain functionality:
Symbolic Math
For symbolic mathematics operations:

Use the Expression tree structure
Implement pattern matching for simplification
Use recursive algorithms for tree manipulation
Consider using the visitor pattern for operations

Quantum Operations
For quantum computing simulations:

Use complex number arithmetic
Implement sparse matrix operations for efficiency
Follow quantum computing conventions
Use the state vector representation

Fractal Generation
For fractal implementations:

Use complex arithmetic for Mandelbrot/Julia sets
Implement iterative and recursive algorithms
Consider GPU acceleration for rendering
Optimize escape-time algorithms

Contributing to WofLang
Guidelines for contributing to the main WofLang project:

Code Style: Follow the established C++23 style
Testing: Add tests for all new features
Documentation: Update documentation for user-visible changes
Backward Compatibility: Ensure your changes don't break existing code
Performance: Consider the performance impact of your changes

Debugging and Troubleshooting
Common Issues and Solutions

Plugin Loading Failures:

Check library path and permissions
Verify ABI compatibility
Use dlopen with RTLD_NOW to catch symbol errors early


Stack Manipulation Errors:

Use the stack_dump operation for debugging
Add extra validation in development builds
Check for type mismatches


Unicode Handling Issues:

Ensure proper Unicode normalization
Check for combining characters
Verify encoding consistency (UTF-8 externally, UTF-32 internally)



Debugging Tools

REPL Debugging Mode:

Enable with :debug on
Shows stack operations in real-time
Traces function calls


Logging:

Set WOFLANG_LOG_LEVEL=debug environment variable
Logs to stderr by default
Can be redirected to a file


Core Dumps:

Enable with ulimit -c unlimited (Unix)
Analyze with gdb ./woflang core



Best Practices for WofLang Programming
Code Organization

Stack Hygiene: Clean up the stack after operations
Comment Unicode: Add comments for less common Unicode characters
Modularize: Use separate files for different functionality
Stack Diagrams: Document stack effects with diagrams:
# fact ( n -- n! )
#   Calculate factorial


Security Considerations

Input Validation: Always validate user input
Sandbox Plugins: Use separate processes for untrusted plugins
Resource Limits: Implement and respect resource limits
Avoid Self-Modifying Code: Use with extreme caution

Community Resources

GitHub Repository: Main source code and issue tracking
Documentation: Comprehensive reference and guides
Discord Channel: Real-time help and discussion
WofLang Showcase: Gallery of example projects

Conclusion
WofLang presents a unique development opportunity at the intersection of traditional programming, Unicode expressiveness, and stack-based languages. By following the guidelines in this document, you'll be well-equipped to contribute to the WofLang ecosystem, whether through plugins, core improvements, or innovative applications.

This developer guide was prepared for RYO Modular/whispr.dev based on the WofLang implementation files v1.0.0 through v3.0.0.