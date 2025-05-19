// wof_repl_or_loader.cpp
// WOFLANG entry point: REPL and/or .wof loader with easter eggs and preload

#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <codecvt>
#include <vector>
#include "wof_interpreter.hpp"

void runFromFile(const std::string& filename, WofInterpreter& interp) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return;
    }

    std::string raw;
    file.seekg(0, std::ios::end);
    raw.resize(file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(&raw[0], raw.size());

    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
    std::u32string glyphStream = conv.from_bytes(raw);

    interp.load(glyphStream.data(), glyphStream.size());
    interp.run();
}

void preloadWofInit(WofInterpreter& interp) {
    const std::string initPath = ".wofinit";
    std::ifstream initFile(initPath);
    if (initFile) {
        std::cout << "[init] Running preload script: " << initPath << "\n";
        runFromFile(initPath, interp);
    }
}

void runREPL(WofInterpreter& interp) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
    std::string line;

    std::cout << R"(
      ╭──────────────────────────────╮
      │    Welcome to WOFLANG 🜂      │
      ╰──────────────────────────────╯
)";
    std::cout << "WOFLANG REPL >\n";

    while (std::getline(std::cin, line)) {
        if (line == "konami") {
            std::cout << "[easter egg] ⬆️⬆️⬇️⬇️⬅️➡️⬅️➡️🅱️🅰️ — unlocked dev mode!\n";
            continue;
        }
        std::u32string glyphLine = conv.from_bytes(line);
        interp.load(glyphLine.data(), glyphLine.size());
        interp.run();n        std::cout << "WOFLANG REPL >\n";
    }
}

int main(int argc, char** argv) {
    WofInterpreter interpreter;

    std::string coreMap = "glyphs.tsv";
    std::string pluginDir = "./plugins";
    std::string fileToRun;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--map" && i + 1 < argc) {
            coreMap = argv[++i];
        } else if (arg == "--plugins" && i + 1 < argc) {
            pluginDir = argv[++i];
        } else {
            fileToRun = arg;
        }
    }

    std::cout << "[boot] Loading core opcode map: " << coreMap << "\n";
    interpreter.loadOpcodeMapFromFile(coreMap);

    std::cout << "[boot] Loading plugins from: " << pluginDir << "\n";
    interpreter.loadPluginsFromFolder(pluginDir);

    preloadWofInit(interpreter);

    if (!fileToRun.empty()) {
        runFromFile(fileToRun, interpreter);
    } else {
        runREPL(interpreter);
    }

    return 0;
}