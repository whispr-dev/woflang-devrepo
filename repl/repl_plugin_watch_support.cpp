// repl_plugin_watch_support.cpp
// Auto-reloads plugins when any .so or .glyphmap changes in ./plugins

#include "load_woflang_plugins.cpp"
#include "dynamic_glyph_loader.cpp"

#include <filesystem>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <iostream>

namespace fs = std::filesystem;

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

        for (const auto& entry : fs::directory_iterator(folder)) {
            auto path = entry.path();
            if (path.extension() == ".so" || path.extension() == ".glyphmap") {
                auto new_time = fs::last_write_time(path);
                if (timestamps[path.string()] != new_time) {
                    changed = true;
                    timestamps[path.string()] = new_time;
                }
            }
        }

        if (changed) {
            std::cout << "[watch] Change detected — reloading plugins/glyphmaps..." << std::endl;
            glyphToOpcode.clear();
            load_plugin_glyphmaps(vm);
            load_all_woflang_plugins(vm);
            std::cout << "[watch] Reload complete." << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}
