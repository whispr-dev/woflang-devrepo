// main.cpp - Clean Woflang entry point
#include "src/core/woflang.hpp"
#include <iostream>

using namespace std;

void print_banner() {
    cout << "╦ ╦┌─┐┌─┐┬  ┌─┐┌┐┌┌─┐" << endl;
    cout << "║║║│ │├┤ │  ├─┤││││ ┬" << endl;
    cout << "╚╩╝└─┘└  ┴─┘┴ ┴┘└┘└─┘ v3.0.0" << endl;
    cout << "A Unicode-native stack language" << endl;
    cout << endl;
}

int main() {
    print_banner();
    
    woflang::WoflangInterpreter interpreter;
    interpreter.loadPlugins();
    interpreter.repl();
    
    return 0;
}