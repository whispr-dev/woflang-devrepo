#include "../../src/core/woflang.hpp"
#include <iostream>
#include <ctime>

bool is_full_moon() {
    // Dumb placeholder: always "yes" for demo; replace with proper astro-calc if you want!
    // In reality, use e.g. moon phase libraries
    return true;
}

class GlyphProphecyOpPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("glyph_prophecy", [](WoflangInterpreter&) {
            if (is_full_moon()) {
                std::cout << "🜄  The glyph prophecy reveals: 'All symbols return to void at the end.'" << std::endl;
            } else {
                std::cout << "The glyph prophecy can only be revealed at the full moon!" << std::endl;
            }
        });
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static GlyphProphecyOpPlugin plugin;
    plugin.register_ops(interp);
}
