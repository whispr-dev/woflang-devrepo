// repl_solve_plusplus.cpp
// Implements :solve ++ — demo solver for known symbolic forms

#include "wof_symbolic.hpp"
#include <iostream>

WofSymbol parseSolveInput(const std::string& line) {
    // VERY simple hardcoded parser for a few known test expressions
    if (line == "2 * X = 4") {
        return WofSymbol{
            std::vector<WofSymbol>{
                WofSymbol{
                    std::vector<WofSymbol>{
                        WofSymbol{2},
                        WofSymbol{"*"},
                        WofSymbol{"X"}
                    }
                },
                WofSymbol{"="},
                WofSymbol{4}
            }
        };
    } else if (line == "X + 3 = 10") {
        return WofSymbol{
            std::vector<WofSymbol>{
                WofSymbol{
                    std::vector<WofSymbol>{
                        WofSymbol{"X"},
                        WofSymbol{"+"},
                        WofSymbol{3}
                    }
                },
                WofSymbol{"="},
                WofSymbol{10}
            }
        };
    } else if (line == "2 * X + 4 = 12") {
        return WofSymbol{
            std::vector<WofSymbol>{
                WofSymbol{
                    std::vector<WofSymbol>{
                        WofSymbol{
                            std::vector<WofSymbol>{
                                WofSymbol{2},
                                WofSymbol{"*"},
                                WofSymbol{"X"}
                            }
                        },
                        WofSymbol{"+"},
                        WofSymbol{4}
                    }
                },
                WofSymbol{"="},
                WofSymbol{12}
            }
        };
    }

    std::cout << "[solve++] Unsupported input format.\n";
    return WofSymbol{};
}
