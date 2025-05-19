// repl_egg_command.cpp
// Implements :egg REPL command that reveals a glyph haiku

#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

void handle_egg_command() {
    static const std::vector<std::vector<std::string>> haikus = {
        {
            "∂ dissolves",
            "into a sea of glyphs",
            "⍺ watches silently"
        },
        {
            "π circles itself",
            "between ⺆ and ⺘",
            "至 whispers return"
        },
        {
            "stack overflows now",
            "☠ beckons the final call",
            "yet ⊕ begins still"
        },
        {
            "read i again",
            "watch ∫ accumulate time",
            "break only for dreams"
        },
        {
            "loop ⟳ eternal",
            "with ↻ in quiet orbit",
            "block never ⺘ ends"
        }
    };

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    const auto& h = haikus[std::rand() % haikus.size()];

    std::cout << "[EGG]\n";
    for (const auto& line : h) {
        std::cout << "  " << line << "\n";
    }
}
