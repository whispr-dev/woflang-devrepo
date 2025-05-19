#include "../../src/core/woflang.hpp"
#include <iostream>
#include <vector>
#include <string>

class MusicOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        // Simple stack-to-melody (text)
        interp.register_op("C", [](WoflangInterpreter& interp) { interp.stack.emplace_back(60); }); // MIDI C4
        interp.register_op("D", [](WoflangInterpreter& interp) { interp.stack.emplace_back(62); });
        interp.register_op("E", [](WoflangInterpreter& interp) { interp.stack.emplace_back(64); });
        interp.register_op("F", [](WoflangInterpreter& interp) { interp.stack.emplace_back(65); });
        interp.register_op("G", [](WoflangInterpreter& interp) { interp.stack.emplace_back(67); });
        interp.register_op("A", [](WoflangInterpreter& interp) { interp.stack.emplace_back(69); });
        interp.register_op("B", [](WoflangInterpreter& interp) { interp.stack.emplace_back(71); });

        interp.register_op("melody", [](WoflangInterpreter& interp) {
            std::vector<std::string> notes;
            for (const auto& v : interp.stack) {
                if (v.type == WofType::Integer) {
                    int n = std::get<int64_t>(v.value);
                    switch (n) {
                        case 60: notes.push_back("C"); break;
                        case 62: notes.push_back("D"); break;
                        case 64: notes.push_back("E"); break;
                        case 65: notes.push_back("F"); break;
                        case 67: notes.push_back("G"); break;
                        case 69: notes.push_back("A"); break;
                        case 71: notes.push_back("B"); break;
                        default: notes.push_back("?");
                    }
                }
            }
            std::cout << "Melody: ";
            for (auto& n : notes) std::cout << n << " ";
            std::cout << std::endl;
        });
        // Add chords, scales, playback/export, etc.
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static MusicOpsPlugin plugin;
    plugin.register_ops(interp);
}
