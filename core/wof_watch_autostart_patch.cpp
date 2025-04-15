// wof_watch_autostart_patch.cpp
// Automatically launches plugin watcher in a background thread on interpreter startup

#include "repl_plugin_watch_support.cpp"

void start_plugin_autowatch(WofInterpreter& vm) {
    std::thread(watch_plugins, std::ref(vm)).detach();
    std::cout << "[auto-watch] Plugin watcher started.
";
}
