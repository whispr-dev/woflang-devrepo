void* handle = dlopen("./plugins/myplugin.so", RTLD_LAZY);
auto registerFunc = (void(*)(WofInterpreter&)) dlsym(handle, "register_myplugin");
registerFunc(vm);


g++ -fPIC -shared myplugin.cpp -o myplugin.so


g++ -fPIC -shared template_plugin.cpp -o template_plugin.so


extern "C" void register_woflang_plugin(WofInterpreter& vm) { ... }


load_all_woflang_plugins(vm);  // From ./plugins/*.so


# Compile the plugin
g++ -fPIC -shared template_plugin.cpp -o plugins/template_plugin.so

# Then in your main:
#include "load_woflang_plugins.cpp"
...
load_all_woflang_plugins(interpreter);


#include "repl_plugin_watch_support.cpp"

if (line == ":watch") {
    std::thread(watch_plugins, std::ref(interpreter)).detach();
    std::cout << "[watch] Live watching started in background.\n";
    continue;
}


#include "wof_watch_autostart_patch.cpp"

int main() {
    WofInterpreter interpreter;
    start_plugin_autowatch(interpreter);  // 👈 Add this after loading glyphs/plugins
    ...
}


#include "wofreplrc_loader.cpp"

int main() {
    WofInterpreter interpreter;
    load_repl_config(interpreter);  // Loads ~/.wofreplrc
    ...
}


echo "watch=true" > ~/.wofreplrc


watch=true
autoload=true
repltheme=dark


#include "ops_control_loop.hpp"
...
register_loop_opcodes(interpreter);



struct LoopFrame {
    size_t startIP;
    size_t endIP;
    int64_t counter;  // or `std::optional` if not used
    std::string type; // "loop", "repeat", "for"
};
std::stack<LoopFrame> loopStack;



#include "load_phase1_mathlib_plugins.cpp"

...

load_phase1_mathlib_plugins(interpreter);



if (line == ":tree") {
    handle_block_tree_command(interpreter.blockRegistry);
    continue;
}



if (line.starts_with(":block ")) {
    handle_block_lookup_command(interpreter.blockRegistry, line);
    continue;
}



if (line == ":trace") { enable_trace(); continue; }
if (line == ":untrace") { disable_trace(); continue; }



if (traceEnabled) trace_step(*this, ip);



if (traceEnabled) {
    trace_step_with_blocks(*this, blockRegistry, ip);
}



struct WofValue {
    enum Type { INT, LIST };
    Type type;
    int64_t intVal;
    std::vector<WofValue> listVal;
};



line = expandKeybindings(line, keyBindingManager);



KeyBindingManager keybinds;
load_keybinds(keybinds);  // loads ~/.wofbinds on launch



if (line.starts_with(":bind")) {
    handle_bind_and_save(keybinds, line);
    continue;
}



if (interpreter.secretsUnlocked && token.glyph == U'☠') {
    dataStack.clear();
    std::cout << "[☠] Stack slain." << std::endl;
}



if (line == ":egg") {
    handle_egg_command();
    continue;
}


register_forbidden_stack_slayer(interpreter);



if (line == ":unlock chaos") {
    interpreter.secretsUnlocked = true;
    std::cout << "[chaos] Forbidden glyphs are now live.\\n";
    continue;
}



if (line == ":woflsigil") {
    handle_woflsigil_command();
    continue;
}



if (line == ":sigil ++") {
    handle_woflsigil_variants();
    continue;
}



if (line == ":sigil chaos") {
    handle_woflsigil_chaos();
    continue;
}



if (line == ":sigil dream") {
    handle_woflsigil_dream();
    continue;
}



if (line == ":sigil purge") {
    handle_woflsigil_purge(interpreter);
    continue;
}



if (line == ":mathdoc") {
    handle_mathdoc_command();
    continue;
}



#include "load_modelica_constants.cpp"
...
load_modelica_constants(interpreter);



#include "load_physics_constants.cpp"
...
load_physics_constants(interpreter);



if (line == ":physdoc") {
    handle_physdoc_command();
    continue;
}


if (line == ":units") {
    handle_units_command(unitRegistry);
    continue;
}



if (line.starts_with(":suggest ")) {
    handle_suggest_command(line);
    continue;
}


check_suggestion_trigger(line);


std::string updated = apply_first_suggestion("X + X");


if (line.starts_with(":suggest ++ ")) {
    std::string updated = apply_first_suggestion(line.substr(13));
    std::cout << updated << std::endl;
    continue;
}



std::vector<std::string> history;

if (line.starts_with(":suggest ++ ")) {
    std::string updated = apply_and_store_suggestion(line.substr(13), history);
    std::cout << "Stored: " << updated << std::endl;
    continue;
}


