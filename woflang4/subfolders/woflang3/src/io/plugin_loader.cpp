#include "../core/woflang.hpp"
#include <filesystem>
#include <iostream>
#include <filesystem>
#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <algorithm>

namespace fs = std::filesystem;

// Helper: Get all plugins in group
std::vector<fs::path> get_plugins_by_group(const std::string& group) {
    std::vector<fs::path> found;
    fs::path group_dir = fs::path("plugins") / group;
    for (auto& entry : fs::recursive_directory_iterator(group_dir)) {
        if (entry.path().extension() == ".dll" || entry.path().extension() == ".so" || entry.path().extension() == ".dylib")
            found.push_back(entry.path());
    }
    return found;
}

// Helper: Get all plugins and group them by subdir
std::map<std::string, std::vector<fs::path>> discover_all_plugins() {
    std::map<std::string, std::vector<fs::path>> plugin_groups;
    for (auto& entry : fs::recursive_directory_iterator("plugins")) {
        if (entry.path().extension() == ".dll" || entry.path().extension() == ".so" || entry.path().extension() == ".dylib") {
            auto rel = fs::relative(entry.path(), "plugins");
            auto group = rel.begin()->string(); // top-level subfolder
            plugin_groups[group].push_back(entry.path());
        }
    }
    return plugin_groups;
}

// Helper: Always load some random sigil plugins
std::vector<fs::path> get_random_sigil_plugins() {
    std::vector<fs::path> sigils;
    for (auto& entry : fs::directory_iterator("plugins/sigils")) {
        if (entry.path().extension() == ".dll" || entry.path().extension() == ".so" || entry.path().extension() == ".dylib")
            sigils.push_back(entry.path());
    }
    // Randomly pick at least 1, up to half (but at least 1 if only 1 exists)
    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(sigils.begin(), sigils.end(), rng);
    int n = std::max(1, (int)sigils.size() / 2 + (rng() % ((int)sigils.size() / 2 + 1)));
    sigils.resize(std::min(n, (int)sigils.size()));
    return sigils;
}

// Interactive menu for group selection
std::vector<fs::path> choose_plugins_menu() {
    auto plugin_groups = discover_all_plugins();
    std::vector<std::string> group_names;
    for (const auto& [group, _] : plugin_groups)
        group_names.push_back(group);

    std::cout << "Select plugin group:\n";
    for (size_t i = 0; i < group_names.size(); ++i)
        std::cout << "  " << (i + 1) << ". " << group_names[i] << "\n";
    std::cout << "  " << (group_names.size() + 1) << ". all\n";
    std::cout << "  " << (group_names.size() + 2) << ". custom (choose up to 10)\n";
    std::cout << "Enter selection: ";
    int sel;
    std::cin >> sel;
    std::vector<fs::path> chosen;
    if (sel >= 1 && sel <= (int)group_names.size()) {
        chosen = plugin_groups[group_names[sel - 1]];
    } else if (sel == (int)group_names.size() + 1) {
        // all
        for (const auto& [_, files] : plugin_groups)
            chosen.insert(chosen.end(), files.begin(), files.end());
    } else {
        // custom
        std::vector<fs::path> all_plugins;
        for (const auto& [_, files] : plugin_groups)
            all_plugins.insert(all_plugins.end(), files.begin(), files.end());
        std::cout << "Select up to 10 plugins by number (comma separated):\n";
        for (size_t i = 0; i < all_plugins.size(); ++i)
            std::cout << "  " << (i + 1) << ". " << all_plugins[i].string() << "\n";
        std::cout << "Input (e.g. 1,2,3): ";
        std::string input;
        std::cin >> input;
        std::vector<int> nums;
        size_t p = 0;
        while (p < input.size()) {
            size_t q = input.find(',', p);
            if (q == std::string::npos) q = input.size();
            try {
                int n = std::stoi(input.substr(p, q - p));
                if (n >= 1 && n <= (int)all_plugins.size())
                    chosen.push_back(all_plugins[n - 1]);
            } catch (...) {}
            p = q + 1;
            if ((int)chosen.size() >= 10) break;
        }
    }
    // Always add random sigil modules (no duplicates)
    auto sigils = get_random_sigil_plugins();
    chosen.insert(chosen.end(), sigils.begin(), sigils.end());
    return chosen;
}

void load_all_plugins(WoflangInterpreter& interp, const std::filesystem::path& plugin_dir) {
    for (const auto& entry : std::filesystem::directory_iterator(plugin_dir)) {
        if (entry.path().extension() == ".dll") {
            try {
                interp.load_plugin(entry.path());
                std::cout << "Loaded plugin: " << entry.path().filename().string() << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Plugin load failed: " << e.what() << std::endl;
            }
        }
    }
}
