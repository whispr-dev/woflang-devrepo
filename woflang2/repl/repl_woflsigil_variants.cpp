// repl_woflsigil_variants.cpp
// Implements :sigil ++ to cycle alternate glyph totems

#include <iostream>
#include <vector>

void handle_woflsigil_variants() {
    static const std::vector<std::string> variants = {
        R"(
         ⊕⺆        ⍺        ⛩️
       ∂     ⨯     π     ∫     ℯ
     ⟜   🛑   ↻   ☠   ⺘
           [ glyphs awaken ]
        )",
        R"(
           [ Σ Y M B Ø L S ]
        ⨯     ∫     π     ∂     ⍺
     🧿    ⟜   ⺆   ⺘   ☠
        )",
        R"(
     🔮  ⊕      ⺆ ... ⺘      🔮
     ∂  ∫  ℯ  π    ↻  🛑  ☠
       [ the stack sees you ]
        )"
    };

    static int sigilIndex = 0;
    std::cout << variants[sigilIndex % variants.size()] << std::endl;
    sigilIndex++;
}
