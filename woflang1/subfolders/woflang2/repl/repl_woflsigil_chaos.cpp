// repl_woflsigil_chaos.cpp
// Implements :sigil chaos — sprays a wall of random glyphs

#include <iostream>
#include <string>
#include <vector>
#include <random>

const std::string chaosSigils[] = {
    "☠", "★", "✝", "✸", "✹", "✺", "✻",
    "✼", "✽", "✾", "✿", "❀", "❁", "❂",
    "❃", "❄", "❅", "❆", "❇", "❈", "❉",
    "❊", "❋"
};

std::string getChaosSigil() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<size_t> dis(0, sizeof(chaosSigils) / sizeof(chaosSigils[0]) - 1);
    return chaosSigils[dis(gen)];
}
