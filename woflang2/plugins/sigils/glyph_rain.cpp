#include "../../src/core/woflang.hpp"
#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <chrono>

// You can customize this with more glyphs or by loading from a list!
static const std::vector<std::u32string> glyph_set = {
    U"π", U"σ", U"Δ", U"Ω", U"∴", U"Ψ", U"Λ", U"Φ", U"Ψ", U"⊕", U"∀", U"∃", U"学", U"心", U"空", U"無", U"力", U"水", U"火", U"風"
};

#ifdef _WIN32
#include <windows.h>
void enable_virtual_terminal_processing() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;
    dwMode |= 0x0004; // ENABLE_VIRTUAL_TERMINAL_PROCESSING
    SetConsoleMode(hOut, dwMode);
}
#else
void enable_virtual_terminal_processing() {}
#endif

class GlyphRainPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("glyph_rain", [](WoflangInterpreter&) {
            enable_virtual_terminal_processing();

            int width = 80, height = 24;
#ifdef _WIN32
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
                width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
                height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
            }
#else
            if (const char* env = std::getenv("COLUMNS")) width = std::atoi(env);
            if (const char* env = std::getenv("LINES")) height = std::atoi(env);
#endif
            std::mt19937 rng(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
            std::uniform_int_distribution<int> col_dist(0, width - 1);
            std::uniform_int_distribution<int> glyph_dist(0, glyph_set.size() - 1);
            std::uniform_int_distribution<int> drop_dist(0, height - 1);

            std::vector<int> drops(width, 0);
            for (int i = 0; i < width; ++i)
                drops[i] = drop_dist(rng);

            std::cout << "\033[?25l"; // Hide cursor
            for (int frame = 0; frame < height * 4; ++frame) {
                for (int y = 0; y < height; ++y) {
                    for (int x = 0; x < width; ++x) {
                        if (drops[x] == y) {
                            std::string g;
                            if constexpr (sizeof(wchar_t) == 4) {
                                wchar_t wc = static_cast<wchar_t>(glyph_set[glyph_dist(rng)][0]);
                                g = std::wstring(1, wc).begin(), std::wstring(1, wc).end();
                            } else {
                                // Most compilers, just output '?'
                                g = "?";
                            }
                            std::cout << "\033[32m" << glyph_set[glyph_dist(rng)] << "\033[0m";
                        } else {
                            std::cout << " ";
                        }
                    }
                    std::cout << "\n";
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(75));
                for (int i = 0; i < width; ++i)
                    drops[i] = (drops[i] + (rng() % 2)) % height;
                std::cout << "\033[" << height << "A"; // Move cursor up to redraw
            }
            std::cout << "\033[?25h\n"; // Show cursor again
        });
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static GlyphRainPlugin plugin;
    plugin.register_ops(interp);
}
