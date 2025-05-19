// dynamic_glyph_loader.cpp
// Loads .glyphmap files from ./plugins and registers glyph → opcode pairs

#include "wof_interpreter.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

void load_plugin_glyphmaps(WofInterpreter& vm, const std::string& plugin_dir = "./plugins") {
    for (const auto& entry : fs::directory_iterator(plugin_dir)) {
        if (entry.path().extension() == ".glyphmap") {
            std::ifstream file(entry.path());
            if (!file) {
                std::cerr << "[glyphmap] Failed to read: " << entry.path() << "\n";
                continue;
            }

            std::cout << "[glyphmap] Loading " << entry.path().filename() << "\n";
            std::string line;
            while (std::getline(file, line)) {
                if (line.empty() || line[0] == '#') continue;

                size_t tab = line.find('\t');
                if (tab == std::string::npos) continue;

                std::string glyph_utf8 = line.substr(0, tab);
                uint16_t opcode = static_cast<uint16_t>(std::stoi(line.substr(tab + 1)));

                std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
                char32_t glyph = conv.from_bytes(glyph_utf8)[0];
                glyphToOpcode[glyph] = opcode;
            }
        }
    }
}
