#include "../../src/core/woflang.hpp"
#include <iostream>
#include <vector>

class LearningModePlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("lesson", [](WoflangInterpreter&) {
            std::vector<std::string> lessons = {
                "Lesson 1: To add numbers, use: 2 3 + print",
                "Lesson 2: To duplicate stack top, use: dup",
                "Lesson 3: To print pi, use: pi print",
                "Lesson 4: To use a plugin, type its op name (e.g., π print)",
                "Lesson 5: Try a chemistry op: 2 mol"
            };
            int idx = std::rand() % lessons.size();
            std::cout << "[Learning Mode] " << lessons[idx] << std::endl;
        });
        interp.register_op("hint", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                std::cout << "Hint: The stack is empty! Try pushing a value.\n";
            } else {
                std::cout << "Hint: Use 'print' to see the top of the stack.\n";
            }
        });
        interp.register_op("quiz", [](WoflangInterpreter&) {
            std::cout << "[Quiz] What does 'Δ' do in Greek Math mode?\n";
            std::cout << "A) Adds two numbers\n";
            std::cout << "B) Subtracts top from next\n";
            std::cout << "C) Multiplies two numbers\n";
        });
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static LearningModePlugin plugin;
    plugin.register_ops(interp);
}
