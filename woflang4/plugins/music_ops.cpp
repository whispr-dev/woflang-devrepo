#include "../../src/core/woflang.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <string>
#include <random>
#include <algorithm>

namespace woflang {

/**
 * @brief Helper functions and constants for music operations
 */
namespace music_helpers {
    // Constants for note frequencies (Middle A = 440 Hz)
    constexpr double A4_FREQ = 440.0;
    constexpr double SEMITONE_RATIO = 1.0594630943592953; // 2^(1/12)
    
    // Notes in an octave
    const std::vector<std::string> NOTE_NAMES = {
        "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
    };
    
    // Map of note names to semitone offsets from C
    const std::map<std::string, int> NOTE_OFFSETS = {
        {"C", 0}, {"C#", 1}, {"Db", 1}, {"D", 2}, {"D#", 3}, {"Eb", 3},
        {"E", 4}, {"F", 5}, {"F#", 6}, {"Gb", 6}, {"G", 7}, {"G#", 8},
        {"Ab", 8}, {"A", 9}, {"A#", 10}, {"Bb", 10}, {"B", 11}
    };
    
    // Common scales (semitone patterns from root)
    const std::map<std::string, std::vector<int>> SCALES = {
        {"major", {0, 2, 4, 5, 7, 9, 11}},
        {"minor", {0, 2, 3, 5, 7, 8, 10}},
        {"pentatonic", {0, 2, 4, 7, 9}},
        {"blues", {0, 3, 5, 6, 7, 10}},
        {"chromatic", {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}},
        {"dorian", {0, 2, 3, 5, 7, 9, 10}},
        {"phrygian", {0, 1, 3, 5, 7, 8, 10}},
        {"lydian", {0, 2, 4, 6, 7, 9, 11}},
        {"mixolydian", {0, 2, 4, 5, 7, 9, 10}},
        {"locrian", {0, 1, 3, 5, 6, 8, 10}}
    };
    
    // Common chord types (semitone patterns from root)
    const std::map<std::string, std::vector<int>> CHORDS = {
        {"major", {0, 4, 7}},
        {"minor", {0, 3, 7}},
        {"diminished", {0, 3, 6}},
        {"augmented", {0, 4, 8}},
        {"sus2", {0, 2, 7}},
        {"sus4", {0, 5, 7}},
        {"major7", {0, 4, 7, 11}},
        {"minor7", {0, 3, 7, 10}},
        {"dominant7", {0, 4, 7, 10}},
        {"diminished7", {0, 3, 6, 9}},
        {"augmented7", {0, 4, 8, 10}},
        {"half-diminished7", {0, 3, 6, 10}}
    };
    
    // Common chord progressions (in Roman numerals)
    const std::map<std::string, std::vector<std::string>> PROGRESSIONS = {
        {"I-IV-V", {"I", "IV", "V"}},
        {"I-V-vi-IV", {"I", "V", "vi", "IV"}},
        {"i-iv-v", {"i", "iv", "v"}},
        {"I-vi-IV-V", {"I", "vi", "IV", "V"}},
        {"ii-V-I", {"ii", "V", "I"}},
        {"I-IV-I-V", {"I", "IV", "I", "V"}},
        {"vi-IV-I-V", {"vi", "IV", "I", "V"}},
        {"I-V-vi-iii-IV-I-IV-V", {"I", "V", "vi", "iii", "IV", "I", "IV", "V"}} // Canon in D
    };
    
    // Calculate frequency of a note
    double note_to_freq(const std::string& note_name, int octave) {
        // Parse note name to get the semitone offset
        if (NOTE_OFFSETS.find(note_name) == NOTE_OFFSETS.end()) {
            throw std::runtime_error("Invalid note name: " + note_name);
        }
        
        int semitones_from_a4 = NOTE_OFFSETS.at(note_name) - NOTE_OFFSETS.at("A") + (octave - 4) * 12;
        return A4_FREQ * std::pow(SEMITONE_RATIO, semitones_from_a4);
    }
    
    // Get the notes in a scale
    std::vector<std::string> get_scale(const std::string& root, const std::string& scale_name) {
        if (NOTE_OFFSETS.find(root) == NOTE_OFFSETS.end()) {
            throw std::runtime_error("Invalid root note: " + root);
        }
        
        if (SCALES.find(scale_name) == SCALES.end()) {
            throw std::runtime_error("Unknown scale: " + scale_name);
        }
        
        int root_offset = NOTE_OFFSETS.at(root);
        std::vector<std::string> notes;
        
        for (int semitone : SCALES.at(scale_name)) {
            int note_idx = (root_offset + semitone) % 12;
            notes.push_back(NOTE_NAMES[note_idx]);
        }
        
        return notes;
    }
    
    // Get the notes in a chord
    std::vector<std::string> get_chord(const std::string& root, const std::string& chord_type) {
        if (NOTE_OFFSETS.find(root) == NOTE_OFFSETS.end()) {
            throw std::runtime_error("Invalid root note: " + root);
        }
        
        if (CHORDS.find(chord_type) == CHORDS.end()) {
            throw std::runtime_error("Unknown chord type: " + chord_type);
        }
        
        int root_offset = NOTE_OFFSETS.at(root);
        std::vector<std::string> notes;
        
        for (int semitone : CHORDS.at(chord_type)) {
            int note_idx = (root_offset + semitone) % 12;
            notes.push_back(NOTE_NAMES[note_idx]);
        }
        
        return notes;
    }
    
    // Generate a melody from a scale with random rhythm
    struct Note {
        std::string name;
        int octave;
        double duration; // in beats
    };
    
    std::vector<Note> generate_melody(const std::string& root, const std::string& scale_name, 
                                      int length, int seed = -1) {
        // Setup random generator
        std::mt19937 gen;
        if (seed < 0) {
            std::random_device rd;
            gen.seed(rd());
        } else {
            gen.seed(static_cast<unsigned int>(seed));
        }
        
        // Get scale notes
        std::vector<std::string> scale_notes = get_scale(root, scale_name);
        
        // Distributions for random selection
        std::uniform_int_distribution<> note_dist(0, scale_notes.size() - 1);
        std::uniform_int_distribution<> octave_dist(3, 5);  // Middle octaves
        std::uniform_int_distribution<> duration_idx(0, 3); // For note durations
        
        // Possible note durations (in beats): eighth, quarter, half, whole
        const std::vector<double> durations = {0.5, 1.0, 2.0, 4.0};
        
        // Generate melody
        std::vector<Note> melody;
        for (int i = 0; i < length; ++i) {
            Note note;
            note.name = scale_notes[note_dist(gen)];
            note.octave = octave_dist(gen);
            note.duration = durations[duration_idx(gen)];
            melody.push_back(note);
        }
        
        return melody;
    }
    
    // Convert a melody to a string representation
    std::string melody_to_string(const std::vector<Note>& melody) {
        std::string result;
        
        for (const auto& note : melody) {
            result += note.name + std::to_string(note.octave);
            
            // Add duration indicator
            if (note.duration == 0.5) {
                result += "e"; // eighth
            } else if (note.duration == 1.0) {
                result += "q"; // quarter
            } else if (note.duration == 2.0) {
                result += "h"; // half
            } else if (note.duration == 4.0) {
                result += "w"; // whole
            }
            
            result += " ";
        }
        
        return result;
    }
    
    // Generate a chord progression from a key
    std::vector<std::string> generate_progression(const std::string& key, const std::string& progression_name) {
        if (NOTE_OFFSETS.find(key) == NOTE_OFFSETS.end()) {
            throw std::runtime_error("Invalid key: " + key);
        }
        
        if (PROGRESSIONS.find(progression_name) == PROGRESSIONS.end()) {
            throw std::runtime_error("Unknown progression: " + progression_name);
        }
        
        // Get the progression pattern
        const auto& progression = PROGRESSIONS.at(progression_name);
        
        // Generate the scale for the key
        bool is_minor = progression_name[0] == 'i'; // Check if starts with lowercase roman numeral
        std::string scale_type = is_minor ? "minor" : "major";
        std::vector<std::string> scale_notes = get_scale(key, scale_type);
        
        // Map Roman numerals to actual chords
        std::vector<std::string> chord_sequence;
        
        for (const auto& numeral : progression) {
            int degree = 0;
            bool is_chord_minor = false;
            
            // Parse the Roman numeral
            if (numeral == "I" || numeral == "i") {
                degree = 0;
                is_chord_minor = numeral == "i";
            } else if (numeral == "II" || numeral == "ii") {
                degree = 1;
                is_chord_minor = numeral == "ii";
            } else if (numeral == "III" || numeral == "iii") {
                degree = 2;
                is_chord_minor = numeral == "iii";
            } else if (numeral == "IV" || numeral == "iv") {
                degree = 3;
                is_chord_minor = numeral == "iv";
            } else if (numeral == "V" || numeral == "v") {
                degree = 4;
                is_chord_minor = numeral == "v";
            } else if (numeral == "VI" || numeral == "vi") {
                degree = 5;
                is_chord_minor = numeral == "vi";
            } else if (numeral == "VII" || numeral == "vii") {
                degree = 6;
                is_chord_minor = numeral == "vii";
            }
            
            // Get the root note for this degree
            std::string root_note = scale_notes[degree % scale_notes.size()];
            
            // Determine chord type based on scale degree and mode
            std::string chord_type;
            if (is_minor) {
                // In minor keys
                if (degree == 0 || degree == 3 || degree == 4) {
                    chord_type = "minor";
                } else if (degree == 1 || degree == 6) {
                    chord_type = "diminished";
                } else if (degree == 2 || degree == 5) {
                    chord_type = "major";
                }
            } else {
                // In major keys
                if (degree == 0 || degree == 3 || degree == 4) {
                    chord_type = "major";
                } else if (degree == 1 || degree == 2 || degree == 5) {
                    chord_type = "minor";
                } else if (degree == 6) {
                    chord_type = "diminished";
                }
            }
            
            // Override with explicit minor/major from the numeral
            if (is_chord_minor) {
                chord_type = "minor";
            } else if (!is_chord_minor && (numeral == "I" || numeral == "II" || numeral == "III" || 
                                          numeral == "IV" || numeral == "V" || numeral == "VI" || 
                                          numeral == "VII")) {
                chord_type = "major";
            }
            
            // Add to sequence
            chord_sequence.push_back(root_note + " " + chord_type);
        }
        
        return chord_sequence;
    }
}

/**
 * @brief Music operations plugin for Woflang
 * 
 * This plugin provides various music-related operations.
 */
class MusicOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        // ----- Note and Frequency Operations -----
        
        // note_to_freq: Convert a note name and octave to frequency
        interp.register_op("note_to_freq", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("note_to_freq requires note_name and octave");
            }
            
            auto octave = interp.stack.back(); interp.stack.pop_back();
            auto note = interp.stack.back(); interp.stack.pop_back();
            
            if (octave.type != WofType::Integer) {
                throw std::runtime_error("Octave must be an integer");
            }
            
            if (note.type != WofType::String && note.type != WofType::Symbol) {
                throw std::runtime_error("Note name must be a string or symbol");
            }
            
            std::string note_name = std::get<std::string>(note.value);
            int octave_num = static_cast<int>(std::get<int64_t>(octave.value));
            
            try {
                double freq = music_helpers::note_to_freq(note_name, octave_num);
                interp.stack.emplace_back(freq);
                
                std::cout << "Note " << note_name << octave_num << " = " << freq << " Hz\n";
            } catch (const std::exception& e) {
                throw std::runtime_error(std::string("note_to_freq error: ") + e.what());
            }
        });
        
        // freq_to_note: Find the closest note to a given frequency
        interp.register_op("freq_to_note", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("freq_to_note requires a frequency");
            }
            
            auto freq = interp.stack.back(); interp.stack.pop_back();
            
            if (!freq.is_numeric()) {
                throw std::runtime_error("Frequency must be a number");
            }
            
            double frequency = freq.as_numeric();
            
            // Calculate semitones from A4
            double semitones_from_a4 = 12.0 * std::log2(frequency / music_helpers::A4_FREQ);
            
            // Find the closest whole number of semitones
            int rounded_semitones = static_cast<int>(std::round(semitones_from_a4));
            
            // Calculate the octave and note index
            int a_idx = static_cast<int>(std::distance(music_helpers::NOTE_NAMES.begin(), 
                                                      std::find(music_helpers::NOTE_NAMES.begin(), 
                                                               music_helpers::NOTE_NAMES.end(), "A")));
            
            int note_idx = (a_idx + rounded_semitones) % 12;
            if (note_idx < 0) note_idx += 12;
            
            int octave = 4 + (a_idx + rounded_semitones) / 12;
            
            // Get the note name
            std::string note_name = music_helpers::NOTE_NAMES[note_idx];
            
            // Calculate the exact frequency of this note
            double exact_freq = music_helpers::A4_FREQ * std::pow(music_helpers::SEMITONE_RATIO, rounded_semitones);
            
            // Push the note name and octave
            interp.stack.emplace_back(note_name, WofType::String);
            interp.stack.emplace_back(static_cast<int64_t>(octave));
            
            std::cout << "Frequency " << frequency << " Hz is closest to note " 
                     << note_name << octave << " (" << exact_freq << " Hz)\n";
        });
        
        // ----- Scales and Chords -----
        
        // scale: Generate a scale from a root note
        interp.register_op("scale", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("scale requires root_note and scale_name");
            }
            
            auto scale_type = interp.stack.back(); interp.stack.pop_back();
            auto root = interp.stack.back(); interp.stack.pop_back();
            
            if ((root.type != WofType::String && root.type != WofType::Symbol) ||
                (scale_type.type != WofType::String && scale_type.type != WofType::Symbol)) {
                throw std::runtime_error("Root note and scale name must be strings or symbols");
            }
            
            std::string root_note = std::get<std::string>(root.value);
            std::string scale_name = std::get<std::string>(scale_type.value);
            
            try {
                std::vector<std::string> scale_notes = music_helpers::get_scale(root_note, scale_name);
                
                // Print the scale
                std::cout << root_note << " " << scale_name << " scale: ";
                for (const auto& note : scale_notes) {
                    std::cout << note << " ";
                }
                std::cout << "\n";
                
                // Push the scale notes onto the stack (in reverse order so they pop in correct order)
                for (auto it = scale_notes.rbegin(); it != scale_notes.rend(); ++it) {
                    interp.stack.emplace_back(*it, WofType::String);
                }
                
                // Push the scale size
                interp.stack.emplace_back(static_cast<int64_t>(scale_notes.size()));
            } catch (const std::exception& e) {
                throw std::runtime_error(std::string("scale error: ") + e.what());
            }
        });
        
        // chord: Generate a chord from a root note
        interp.register_op("chord", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("chord requires root_note and chord_type");
            }
            
            auto chord_type = interp.stack.back(); interp.stack.pop_back();
            auto root = interp.stack.back(); interp.stack.pop_back();
            
            if ((root.type != WofType::String && root.type != WofType::Symbol) ||
                (chord_type.type != WofType::String && chord_type.type != WofType::Symbol)) {
                throw std::runtime_error("Root note and chord type must be strings or symbols");
            }
            
            std::string root_note = std::get<std::string>(root.value);
            std::string chord_name = std::get<std::string>(chord_type.value);
            
            try {
                std::vector<std::string> chord_notes = music_helpers::get_chord(root_note, chord_name);
                
                // Print the chord
                std::cout << root_note << " " << chord_name << " chord: ";
                for (const auto& note : chord_notes) {
                    std::cout << note << " ";
                }
                std::cout << "\n";
                
                // Push the chord notes onto the stack (in reverse order so they pop in correct order)
                for (auto it = chord_notes.rbegin(); it != chord_notes.rend(); ++it) {
                    interp.stack.emplace_back(*it, WofType::String);
                }
                
                // Push the chord size
                interp.stack.emplace_back(static_cast<int64_t>(chord_notes.size()));
            } catch (const std::exception& e) {
                throw std::runtime_error(std::string("chord error: ") + e.what());
            }
        });
        
        // ----- Composition Operations -----
        
        // generate_melody: Create a random melody from a scale
        interp.register_op("generate_melody", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 3) {
                throw std::runtime_error("generate_melody requires root_note, scale_name, and length");
            }
            
            auto length = interp.stack.back(); interp.stack.pop_back();
            auto scale_type = interp.stack.back(); interp.stack.pop_back();
            auto root = interp.stack.back(); interp.stack.pop_back();
            
            if (!length.is_numeric()) {
                throw std::runtime_error("Melody length must be a number");
            }
            
            if ((root.type != WofType::String && root.type != WofType::Symbol) ||
                (scale_type.type != WofType::String && scale_type.type != WofType::Symbol)) {
                throw std::runtime_error("Root note and scale name must be strings or symbols");
            }
            
            std::string root_note = std::get<std::string>(root.value);
            std::string scale_name = std::get<std::string>(scale_type.value);
            int melody_length = static_cast<int>(length.as_numeric());
            
            try {
                // Optional seed from stack
                int seed = -1;
                if (!interp.stack.empty() && interp.stack.back().is_numeric()) {
                    seed = static_cast<int>(interp.stack.back().as_numeric());
                    interp.stack.pop_back();
                }
                
                // Generate the melody
                auto melody = music_helpers::generate_melody(root_note, scale_name, melody_length, seed);
                
                // Convert to string representation
                std::string melody_str = music_helpers::melody_to_string(melody);
                
                // Print the melody
                std::cout << "Generated melody (" << root_note << " " << scale_name << "):\n";
                std::cout << melody_str << "\n";
                
                // Push the melody string
                interp.stack.emplace_back(melody_str);
            } catch (const std::exception& e) {
                throw std::runtime_error(std::string("generate_melody error: ") + e.what());
            }
        });
        
        // generate_progression: Create a chord progression
        interp.register_op("generate_progression", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("generate_progression requires key and progression_name");
            }
            
            auto progression = interp.stack.back(); interp.stack.pop_back();
            auto key = interp.stack.back(); interp.stack.pop_back();
            
            if ((key.type != WofType::String && key.type != WofType::Symbol) ||
                (progression.type != WofType::String && progression.type != WofType::Symbol)) {
                throw std::runtime_error("Key and progression name must be strings or symbols");
            }
            
            std::string key_note = std::get<std::string>(key.value);
            std::string progression_name = std::get<std::string>(progression.value);
            
            try {
                // Generate the progression
                auto chord_sequence = music_helpers::generate_progression(key_note, progression_name);
                
                // Print the progression
                std::cout << key_note << " " << progression_name << " progression:\n";
                for (const auto& chord : chord_sequence) {
                    std::cout << chord << " | ";
                }
                std::cout << "\n";
                
                // Push the chords onto the stack (in reverse order)
                for (auto it = chord_sequence.rbegin(); it != chord_sequence.rend(); ++it) {
                    interp.stack.emplace_back(*it, WofType::String);
                }
                
                // Push the number of chords
                interp.stack.emplace_back(static_cast<int64_t>(chord_sequence.size()));
            } catch (const std::exception& e) {
                throw std::runtime_error(std::string("generate_progression error: ") + e.what());
            }
        });
        
        // ----- Educational Operations -----
        
        // list_scales: Display available scales
        interp.register_op("list_scales", [](WoflangInterpreter& interp) {
            std::cout << "Available scales:\n";
            for (const auto& [scale_name, _] : music_helpers::SCALES) {
                std::cout << "  * " << scale_name << "\n";
            }
        });
        
        // list_chords: Display available chord types
        interp.register_op("list_chords", [](WoflangInterpreter& interp) {
            std::cout << "Available chord types:\n";
            for (const auto& [chord_name, _] : music_helpers::CHORDS) {
                std::cout << "  * " << chord_name << "\n";
            }
        });
        
        // list_progressions: Display available chord progressions
        interp.register_op("list_progressions", [](WoflangInterpreter& interp) {
            std::cout << "Available chord progressions:\n";
            for (const auto& [prog_name, progression] : music_helpers::PROGRESSIONS) {
                std::cout << "  * " << prog_name << ": ";
                for (const auto& numeral : progression) {
                    std::cout << numeral << " ";
                }
                std::cout << "\n";
            }
        });
        
        // music_theory: Display basic music theory information
        interp.register_op("music_theory", [](WoflangInterpreter& interp) {
            std::cout << "=== Basic Music Theory ===\n\n";
            
            std::cout << "Notes in Western music: C, C#/Db, D, D#/Eb, E, F, F#/Gb, G, G#/Ab, A, A#/Bb, B\n\n";
            
            std::cout << "Intervals:\n";
            std::cout << "  * Unison: 0 semitones\n";
            std::cout << "  * Minor 2nd: 1 semitone\n";
            std::cout << "  * Major 2nd: 2 semitones\n";
            std::cout << "  * Minor 3rd: 3 semitones\n";
            std::cout << "  * Major 3rd: 4 semitones\n";
            std::cout << "  * Perfect 4th: 5 semitones\n";
            std::cout << "  * Tritone: 6 semitones\n";
            std::cout << "  * Perfect 5th: 7 semitones\n";
            std::cout << "  * Minor 6th: 8 semitones\n";
            std::cout << "  * Major 6th: 9 semitones\n";
            std::cout << "  * Minor 7th: 10 semitones\n";
            std::cout << "  * Major 7th: 11 semitones\n";
            std::cout << "  * Octave: 12 semitones\n\n";
            
            std::cout << "Common scales:\n";
            std::cout << "  * Major scale: Whole, Whole, Half, Whole, Whole, Whole, Half\n";
            std::cout << "  * Minor scale: Whole, Half, Whole, Whole, Half, Whole, Whole\n";
            std::cout << "  * Pentatonic scale: Whole, Whole, Minor 3rd, Whole, Minor 3rd\n\n";
            
            std::cout << "Basic chords:\n";
            std::cout << "  * Major: Root, Major 3rd, Perfect 5th\n";
            std::cout << "  * Minor: Root, Minor 3rd, Perfect 5th\n";
            std::cout << "  * Diminished: Root, Minor 3rd, Diminished 5th\n";
            std::cout << "  * Augmented: Root, Major 3rd, Augmented 5th\n\n";
            
            std::cout << "Use list_scales, list_chords, and list_progressions for more information.\n";
        });
        
        // ----- Musical Constants -----
        
        // middle_a: Push the frequency of middle A (440 Hz)
        interp.register_op("middle_a", [](WoflangInterpreter& interp) {
            interp.stack.emplace_back(music_helpers::A4_FREQ);
            std::cout << "Middle A (A4) = " << music_helpers::A4_FREQ << " Hz\n";
        });
        
        // semitone_ratio: Push the ratio between adjacent semitones (12-TET)
        interp.register_op("semitone_ratio", [](WoflangInterpreter& interp) {
            interp.stack.emplace_back(music_helpers::SEMITONE_RATIO);
            std::cout << "Semitone ratio (12-TET) = " << music_helpers::SEMITONE_RATIO << "\n";
        });
    }
};

} // namespace woflang

// Plugin registration function
WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::MusicOpsPlugin plugin;
    plugin.register_ops(interp);
}
