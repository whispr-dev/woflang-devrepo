// woflang_vm_executor.cpp
// WOFLANG virtual machine executor with double-buffered file loading

#include "load_woflang_plugins.cpp"
#include "dynamic_glyph_loader.cpp"
#include "wof_watch_autostart_patch.cpp"
#include "wofreplrc_loader_extended.cpp"
#include "load_phase1_mathlib_plugins.cpp"
#include "wof_keybind_autoload_patch.cpp"

#include <iostream>
#include <unordered_map>
#include <functional>
#include <stack>
#include <vector>
#include <fstream>
#include <codecvt>
#include <locale>
#include <cstring>
#include "parse_woflang_simd.cpp"

class WoflangVM {
public:
    WoflangVM() {
        registerDefaultOps();
    }

    void loadScript(const char32_t* glyphStream, size_t length) {
        tokens = parseWoflangSIMD(glyphStream, length);
    }

    void execute() {
        size_t ip = 0;  // instruction pointer
        while (ip < tokens.size()) {
            const auto& token = tokens[ip];
            auto it = opcodeHandlers.find(token.opcode);
            if (it != opcodeHandlers.end()) {
                it->second(*this, token);
            } else {
                std::cerr << "Unknown opcode: " << token.opcode << " at position " << token.position << "\n";
            }
            ++ip;
        }
    }

    void push(int64_t value) {
        stack.push(value);
    }

    int64_t pop() {
        if (stack.empty()) throw std::runtime_error("Stack underflow");
        int64_t val = stack.top();
        stack.pop();
        return val;
    }

    void runDoubleBuffered(const std::string& filename, size_t chunkSize = 4096) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return;
        }

        std::u32string buffer1, buffer2;
        bool useBuffer1 = true;
        std::u32string* activeBuffer = &buffer1;

        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;

        std::string chunk;
        chunk.resize(chunkSize);

        while (file.read(&chunk[0], chunkSize) || file.gcount()) {
            size_t bytesRead = file.gcount();
            chunk.resize(bytesRead);

            *activeBuffer = conv.from_bytes(chunk);
            loadScript(activeBuffer->data(), activeBuffer->size());
            execute();

            chunk.resize(chunkSize); // reset chunk size
            activeBuffer = useBuffer1 ? &buffer2 : &buffer1;
            useBuffer1 = !useBuffer1;
        }
    }

private:
    std::vector<WofToken> tokens;
    std::stack<int64_t> stack;

    using Handler = std::function<void(WoflangVM&, const WofToken&)>;
    std::unordered_map<uint16_t, Handler> opcodeHandlers;

    void registerDefaultOps() {
        opcodeHandlers[1] = [](WoflangVM& vm, const WofToken& t) {
            std::cout << "[def] Start definition block at " << t.position << "\n";
        };
        opcodeHandlers[2] = [](WoflangVM& vm, const WofToken& t) {
            std::cout << "[if] Condition check (simulated)\n";
        };
        opcodeHandlers[3] = [](WoflangVM& vm, const WofToken& t) {
            std::cout << "[then] Executing THEN block\n";
        };
        opcodeHandlers[4] = [](WoflangVM& vm, const WofToken& t) {
            std::cout << "[else] Executing ELSE block\n";
        };
        opcodeHandlers[5] = [](WoflangVM& vm, const WofToken& t) {
            std::cout << "[ret] Returning from function\n";
        };
        opcodeHandlers[6] = [](WoflangVM& vm, const WofToken& t) {
            std::cout << "[block start] ⺆\n";
        };
        opcodeHandlers[7] = [](WoflangVM& vm, const WofToken& t) {
            std::cout << "[block end] ⺘\n";
        };

        // Stack math ops
        opcodeHandlers[10] = [](WoflangVM& vm, const WofToken&) { // ADD
            int64_t b = vm.pop();
            int64_t a = vm.pop();
            vm.push(a + b);
            std::cout << "[add] " << a << " + " << b << " = " << (a + b) << "\n";
        };
        opcodeHandlers[11] = [](WoflangVM& vm, const WofToken&) { // SUB
            int64_t b = vm.pop();
            int64_t a = vm.pop();
            vm.push(a - b);
            std::cout << "[sub] " << a << " - " << b << " = " << (a - b) << "\n";
        };
        opcodeHandlers[12] = [](WoflangVM& vm, const WofToken&) { // MUL
            int64_t b = vm.pop();
            int64_t a = vm.pop();
            vm.push(a * b);
            std::cout << "[mul] " << a << " * " << b << " = " << (a * b) << "\n";
        };
        opcodeHandlers[13] = [](WoflangVM& vm, const WofToken&) { // DIV
            int64_t b = vm.pop();
            int64_t a = vm.pop();
            if (b == 0) throw std::runtime_error("[div] Division by zero");
            vm.push(a / b);
            std::cout << "[div] " << a << " / " << b << " = " << (a / b) << "\n";
        
            #include "load_math_plugins.cpp"
            ...
            load_all_math_plugins(interpreter);
            
            #include "load_woflang_plugins.cpp"
            #include "dynamic_glyph_loader.cpp"
            
            ...
            
            load_plugin_glyphmaps(interpreter);
            load_all_woflang_plugins(interpreter);            

            // Load glyphs + plugins
            interpreter.loadOpcodeMapFromFile("glyphs.tsv");
            interpreter.loadPluginsFromFolder("./plugins");
            load_all_math_plugins(interpreter);

            // Run REPL or file
        };
    }
};