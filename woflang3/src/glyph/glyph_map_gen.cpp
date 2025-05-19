#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: glyph_map_gen input.csv output.hpp\n";
        return 1;
    }
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    fout << "#pragma once\n#include <unordered_map>\n#include <string>\n#include <cstdint>\n";
    fout << "inline const std::unordered_map<char32_t, std::string> woflang_glyph_map = {\n";

    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        std::string glyph, name;
        if (!std::getline(iss, glyph, ',')) continue;
        if (!std::getline(iss, name)) continue;
        // Assume glyph as UTF-8 char in CSV
        fout << "    { U'" << glyph << "', \"" << name << "\" },\n";
    }
    fout << "};\n";
    return 0;
}
