// wof_interpreter.hpp
#pragma once

#include <vector>
#include <unordered_map>
#include <stack>
#include <functional>
#include <cstdint>
#include <fstream>
#include <string>
#include <sstream>
#include <optional>
#include "parse_woflang_simd.cpp"

class WofInterpreter {
public:
    WofInterpreter();

    // Load a script (glyph stream) and prepare token stream
    void load(const char32_t* code, size_t length);

    // Run the entire token stream
    void run();

    // Stack operations
    void push(int64_t val);
    int64_t pop();

    // Register new opcode handler
    void registerOpcode(uint16_t opcode, std::function<void(WofInterpreter&, const WofToken&)> handler);

    // Load glyph-to-opcode mappings from a plugin file (UTF-8 TSV: "⺆\t6")
    void loadOpcodeMapFromFile(const std::string& filename);
    void loadPluginsFromFolder(const std::string& folderPath);

    // Control flow
    void jumpToLabel(const std::string& label);
    void defineLabel(const std::string& label, size_t position);

    // Function definition support
    void defineFunction(const std::string& name, size_t startIndex);
    void callFunction(const std::string& name);

private:
    std::vector<WofToken> tokens;
    std::stack<int64_t> dataStack;
    std::unordered_map<uint16_t, std::function<void(WofInterpreter&, const WofToken&)>> handlers;

    std::unordered_map<std::string, size_t> labelMap;
    std::unordered_map<std::string, size_t> functionMap;
    std::optional<size_t> instructionPointerOverride;
};

extern std::unordered_map<char32_t, uint16_t> glyphToOpcode;

// External map that parseWoflangSIMD will use (unified global)
