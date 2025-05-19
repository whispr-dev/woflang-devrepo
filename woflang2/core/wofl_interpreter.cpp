// wof_interpreter.cpp
#include "wof_interpreter.hpp"
#include <codecvt>
#include <locale>
#include <filesystem>

namespace fs = std::filesystem;

std::unordered_map<char32_t, uint16_t> glyphToOpcode;  // Global shared map

WofInterpreter::WofInterpreter() {}

void WofInterpreter::load(const char32_t* code, size_t length) {
    tokens = parseWoflangSIMD(code, length);
}

void WofInterpreter::run() {
    for (const auto& token : tokens) {
        auto it = handlers.find(token.opcode);
        if (it != handlers.end()) {
            it->second(*this, token);
        } else {
            std::cerr << "Unhandled opcode: " << token.opcode << "\n";
        }
    }
}

void WofInterpreter::push(int64_t val) {
    dataStack.push(val);
}

int64_t WofInterpreter::pop() {
    if (dataStack.empty()) throw std::runtime_error("Stack underflow");
    int64_t val = dataStack.top();
    dataStack.pop();
    return val;
}

void WofInterpreter::registerOpcode(uint16_t opcode, std::function<void(WofInterpreter&, const WofToken&)> handler) {
    handlers[opcode] = handler;
}

void WofInterpreter::loadOpcodeMapFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to load opcode map from: " << filename << std::endl;
        return;
    }

    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
    std::string line;

    while (std::getline(file, line)) {
        size_t tab = line.find('\t');
        if (tab == std::string::npos) continue;

        std::string glyphUtf8 = line.substr(0, tab);
        uint16_t opcode = static_cast<uint16_t>(std::stoi(line.substr(tab + 1)));

        char32_t glyph = conv.from_bytes(glyphUtf8)[0];
        glyphToOpcode[glyph] = opcode;
    }

    std::cout << "Loaded " << glyphToOpcode.size() << " opcodes from " << filename << "\n";
}

void WofInterpreter::loadPluginsFromFolder(const std::string& folderPath) {
    size_t totalLoaded = 0;
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.path().extension() == ".glyphmap") {
            loadOpcodeMapFromFile(entry.path().string());
            ++totalLoaded;
        }
    }
    std::cout << "[plugin loader] Loaded " << totalLoaded << " .glyphmap files from " << folderPath << "\n";
}