// repl_mathdoc_command.cpp
// Implements :mathdoc — lists math glyphs and descriptions

#include <iostream>

void handle_mathdoc_command() {
    std::cout << "[WOFLANG MATHDOC]\n";

    std::cout << "\n-- Constants --\n";
    std::cout << "π     (3001)  — Pi constant\n";
    std::cout << "ℯ     (3002)  — Euler's e\n";

    std::cout << "\n-- Calculus --\n";
    std::cout << "∂     (3010)  — Approx. derivative: x2 - x1\n";
    std::cout << "∫     (3011)  — Approx. integral: trapezoid rule\n";

    std::cout << "\n-- Exponentials --\n";
    std::cout << "√     (3020)  — Square root\n";
    std::cout << "⁒     (3021)  — Power: pow(base, exp)\n";
    std::cout << "ƒlog  (3022)  — Natural log\n";
    std::cout << "ƒexp  (3023)  — e^x\n";

    std::cout << "\n-- List Ops --\n";
    std::cout << "length (3100)  — Count elements\n";
    std::cout << "get    (3101)  — Get index\n";
    std::cout << "append (3102)  — Add to list\n";
    std::cout << "map    (3110)  — Apply op to list\n";
    std::cout << "reduce (3111)  — Collapse list via sum\n";
    std::cout << "dot    (3112)  — Dot product\n";
    std::cout << "sum    (3113)  — Add all elements\n";
    std::cout << "avg    (3114)  — Average\n";
    std::cout << "min    (3115)  — Minimum\n";
    std::cout << "max    (3116)  — Maximum\n";
    std::cout << "norm   (3117)  — L2 vector norm\n";
}
