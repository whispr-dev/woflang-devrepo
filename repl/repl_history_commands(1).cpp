// repl_history_commands.cpp
// Implements :history and :!! REPL features

#include <iostream>
#include <vector>
#include <string>

void handle_history_command(const std::vector<std::string>& history) {
    std::cout << "[REPL HISTORY]\n";
    for (size_t i = 0; i < history.size(); ++i) {
        std::cout << i << ": " << history[i] << "\n";
    }
}

std::string repeat_last_command(const std::vector<std::string>& history) {
    if (history.empty()) {
        std::cout << "[REPL] No history to repeat.\n";
        return "";
    }
    std::cout << "[REPL] Repeating last: " << history.back() << "\n";
    return history.back();
}
