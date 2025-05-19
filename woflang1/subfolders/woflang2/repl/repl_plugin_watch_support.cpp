// repl_plugin_watch_support.cpp
// Auto-reloads plugins when any .so or .glyphmap changes in ./plugins

// Corrected: The following includes were commented out because the files were not provided.
// Including .cpp files directly is also generally not recommended in C++.
// You will need to ensure the correct header files (.h or .hpp) for the
// declarations in these files are included, and that they are in your project's include path.
// #include "load_woflang_plugins.cpp"
// #include "dynamic_glyph_loader.cpp"

#include "wof_interpreter.hpp" // Assuming WofInterpreter definition is in this header

#include <filesystem>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <iostream>

namespace fs = std::filesystem;

// Corrected: Assuming glyphToOpcode, load_plugin_glyphmaps, and load_all_woflang_plugins
// are declared elsewhere (e.g., in header files) and accessible.
extern std::unordered_map<char32_t, int> glyphToOpcode;
extern void load_plugin_glyphmaps(WofInterpreter& vm);
extern void load_all_woflang_plugins(WofInterpreter& vm);


void watch_plugins(WofInterpreter& vm, const std::string& folder = "./plugins") {
    std::unordered_map<std::string, std::filesystem::file_time_type> timestamps;

    // Init timestamps
    for (const auto& entry : fs::directory_iterator(folder)) {
        if (entry.path().extension() == ".so" || entry.path().extension() == ".glyphmap") {
            timestamps[entry.path().string()] = fs::last_write_time(entry);
        }
    }

    std::cout << "[watch] Watching ./plugins for changes..." << std::endl;

    while (true) {
        bool changed = false;

        // Re-check directory entries in case new files are added or deleted
        std::unordered_map<std::string, std::filesystem::file_time_type> current_timestamps;
         for (const auto& entry : fs::directory_iterator(folder)) {
            auto path = entry.path();
            if (path.extension() == ".so" || path.extension() == ".glyphmap") {
                 current_timestamps[path.string()] = fs::last_write_time(path);
            }
         }

        // Check for modified or new files
        for (const auto& pair : current_timestamps) {
            const auto& path_string = pair.first;
            const auto& current_time = pair.second;

            if (timestamps.find(path_string) == timestamps.end() || timestamps[path_string] != current_time) {
                changed = true;
                timestamps[path_string] = current_time; // Update or add timestamp
            }
        }

        // Check for deleted files
        for (auto it = timestamps.begin(); it != timestamps.end(); ) {
            if (current_timestamps.find(it->first) == current_timestamps.end()) {
                changed = true;
                it = timestamps.erase(it); // Remove deleted file from timestamps
            } else {
                ++it;
            }
        }


        if (changed) {
            std::cout << "[watch] Change detected — reloading plugins/glyphmaps..." << std::endl;
            glyphToOpcode.clear();
            // Assuming these functions are defined and accessible
            load_plugin_glyphmaps(vm);
            load_all_woflang_plugins(vm);
            std::cout << "[watch] Reload complete." << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}