// wof_interpreter_loop_patch.hpp
// Patch to integrate LoopContext into WofInterpreter

#pragma once
#include "loop_block_runtime.hpp"

class WofInterpreter {
public:
    WofInterpreter();

    // core methods (assume implemented)
    void load(const char32_t* code, size_t length);
    void run();
    void push(int64_t val);
    int64_t pop();
    void registerOpcode(uint16_t opcode, std::function<void(WofInterpreter&, const WofToken&)> handler);
    void loadOpcodeMapFromFile(const std::string& filename);
    void loadPluginsFromFolder(const std::string& folderPath);
    void jumpToLabel(const std::string& label);
    void defineLabel(const std::string& label, size_t position);
    void defineFunction(const std::string& name, size_t startIndex);
    void callFunction(const std::string& name);

    // 🔁 Loop support
    LoopContext loopContext;

private:
    std::vector<WofToken> tokens;
    std::stack<int64_t> dataStack;
    std::unordered_map<uint16_t, std::function<void(WofInterpreter&, const WofToken&)>> handlers;
    std::unordered_map<std::string, size_t> labelMap;
    std::unordered_map<std::string, size_t> functionMap;
    std::optional<size_t> instructionPointerOverride;
};

extern std::unordered_map<char32_t, uint16_t> glyphToOpcode;
