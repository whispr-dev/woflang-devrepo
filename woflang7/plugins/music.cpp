// ==================================================
// FIXED: music.cpp
// ==================================================
#include "../../src/core/woflang.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <map>

namespace woflang {

class MusicOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        // Note frequencies (A4 = 440Hz)
        std::map<std::string, double> notes = {
            {"C", 261.63}, {"C#", 277.18}, {"D", 293.66}, {"D#", 311.13},
            {"E", 329.63}, {"F", 349.23}, {"F#", 369.99}, {"G", 392.00},
            {"G#", 415.30}, {"A", 440.00}, {"A#", 466.16}, {"B", 493.88}
        };
        
        // Register note operations
        for (const auto& [note, freq] : notes) {
            interp.register_op(note, [freq](std::stack<WofValue>& stack) {
                stack.push(WofValue(freq));
                std::cout << "♪ " << freq << " Hz\n";
            });
        }
        
        // Chord operations
        interp.register_op("major", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                std::cout << "major: needs a root note frequency\n";
                return;
            }
            
            auto root = stack.top(); stack.pop();
            double root_freq = root.as_numeric();
            
            // Major chord: root, major third, perfect fifth
            stack.push(WofValue(root_freq));
            stack.push(WofValue(root_freq * 1.25));    // Major third
            stack.push(WofValue(root_freq * 1.5));     // Perfect fifth
            
            std::cout << "♫ Major chord: " << root_freq << " Hz\n";
        });
        
        interp.register_op("minor", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                std::cout << "minor: needs a root note frequency\n";
                return;
            }
            
            auto root = stack.top(); stack.pop();
            double root_freq = root.as_numeric();
            
            // Minor chord: root, minor third, perfect fifth
            stack.push(WofValue(root_freq));
            stack.push(WofValue(root_freq * 1.2));     // Minor third
            stack.push(WofValue(root_freq * 1.5));     // Perfect fifth
            
            std::cout << "♫ Minor chord: " << root_freq << " Hz\n";
        });
        
        // Rhythm operations
        interp.register_op("♩", [](std::stack<WofValue>& stack) {
            stack.push(WofValue(1.0));  // Quarter note
            std::cout << "♩ Quarter note\n";
        });
        
        interp.register_op("♪", [](std::stack<WofValue>& stack) {
            stack.push(WofValue(0.5));  // Eighth note
            std::cout << "♪ Eighth note\n";
        });
        
        interp.register_op("♫", [](std::stack<WofValue>& stack) {
            stack.push(WofValue(0.25)); // Sixteenth note
            std::cout << "♫ Sixteenth note\n";
        });
        
        interp.register_op("bpm", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                std::cout << "bpm: needs a tempo value\n";
                return;
            }
            
            auto tempo = stack.top(); stack.pop();
            double bpm = tempo.as_numeric();
            double beat_duration = 60.0 / bpm;
            
            std::cout << "Tempo: " << bpm << " BPM (beat = " 
                     << beat_duration << " seconds)\n";
            
            stack.push(WofValue(beat_duration));
        });
    }
};

} // namespace woflang

WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::MusicOpsPlugin plugin;
    plugin.register_ops(interp);
}