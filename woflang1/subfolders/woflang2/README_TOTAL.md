# ⛩️ WOFLANG: The Symbolic Programming Language of Glyphs

```
       ⊕⺆        ⍺        ⛩️
     ∂     ⨯     π     ∫     ℯ
   ⟜   🛑   ↻   ☠   ⺘
         [ glyphs awaken ]
```

---

## 🧱 Overview

WOFLANG is a stack-based, REPL-driven, Unicode-symbolic language designed for:
- ⚙️ Math
- 🔬 Physics
- 🧠 Symbolic computation
- 🎛️ Modular plugins
- 🌈 Expression of thought as code

It supports:
- Symbolic expressions (`[ X + X ]`)
- Units of measure (`10 m * 2`)
- Math/physics constants (`π`, `ℯ`, `ℏ`, `g`)
- AI-assisted code suggestion (`:suggest`, `...`)
- Dreamlike Easter eggs (`:sigil dream`, `☠`, `:egg`)
- Fully customizable architecture with toggleable modules

---

## 📁 File Structure

```
woflang/
├── core/                      # Main interpreter (WofInterpreter)
├── parser/                    # Glyph stream parser
├── simd/                      # SIMD parsing acceleration
├── repl/                      # REPL UI + sigils + history
├── ops/                       # Plugin opcodes
├── units/                     # Unit support system
├── plugins/                   # Math, physics, symbolic logic plugins
├── docs/                      # This and other Markdown docs
├── tests/                     # .wof test scripts
└── CMakeLists.txt             # Build system
```

---

## 🚀 Setup

```bash
mkdir build && cd build
cmake ..
cmake --build .
./woflang
```

To enable full functionality, add:
```cpp
#include "load_modelica_constants.cpp"
#include "load_physics_constants.cpp"
#include "register_builtin_units.cpp"
#include "load_phase1_mathlib_plugins.cpp"
#include "register_symbolic_opcodes.cpp"
#include "register_symbolic_solve_patterns.cpp"
#include "register_unit_math_opcodes.cpp"
#include "register_unit_assignment.cpp"
#include "register_list_math_ext.cpp"
```

---

## 🎮 REPL Commands

| Command          | Purpose                        |
|------------------|--------------------------------|
| `:stack`         | Show current stack             |
| `:scope`         | Show current local variables   |
| `:history`       | Show command history           |
| `:!!`            | Repeat last input              |
| `:units`         | List available units           |
| `:unitdoc`       | Docs for unit math             |
| `:mathdoc`       | Docs for math glyphs           |
| `:physdoc`       | Docs for physics constants     |
| `:suggest`       | Suggest math completions       |
| `...`            | Trigger inline suggestion      |
| `:suggest ++`    | Accept & store first suggestion|
| `:solve ++`      | Demo solving symbolic equation |
| `:sigil chaos`   | Fun/random sigil cloud         |
| `:sigil dream`   | Surreal glyphscape             |
| `:sigil purge`   | Reset chaos/dream mode         |
| `:egg`           | Reveal haiku                   |
| `:woflsigil`     | Show logo                      |

---

## 🧮 Math Features

| Glyph | Action                      | Example              |
|-------|-----------------------------|----------------------|
| `π`   | Push Pi                     | `π emit`             |
| `√`   | Square root                 | `push 9 √ emit`      |
| `⁒`   | Exponentiation              | `push 2 push 3 ⁒`    |
| `∂`   | Approx. derivative          | `push 5 push 2 ∂`    |
| `∫`   | Approx. integral            | `push 1 push 4 ∫`    |

See `:mathdoc` for full list.

---

## 🧱 Symbolic Expressions

| Feature   | Example                          |
|-----------|----------------------------------|
| Simplify  | `[ X + X ] simplify` → `2 * X`   |
| Solve     | `[ 2 * X = 4 ] solve` → `X = 2`  |
| Suggestions | `X + X...` → `2 * X`           |

Use `3200` (simplify), `3201-3202` (solve)

---

## ⚖️ Units

| Feature         | Example             | Result            |
|------------------|----------------------|-------------------|
| Basic unit       | `push 10 push m assign_unit` | `10 m` |
| Arithmetic       | `10 m * 2`           | `20 m`            |
| Mismatch warning | `10 m + 2 s`         | ⚠️ unitless        |
| Prefixes         | `k`, `m`, `μ`, etc.  | `1e3`, `1e-3`      |

Use `:unitdoc` and `:units`.

---

## 🧪 Physics Constants

| Glyph | Meaning         | Value         |
|-------|------------------|---------------|
| `ℏ`   | Planck reduced   | `1.05e-34`    |
| `c`   | Speed of light   | `299792458`   |
| `g`   | Gravity          | `9.807`       |
| `e⁻`  | Electron charge  | `1.6e-19`     |
| `mₑ`  | Electron mass    | `9.1e-31`     |
| `mₚ`  | Proton mass      | `1.67e-27`    |

See `:physdoc`.

---

## 🎛️ Feature Toggles

| Toggle                      | Description                         |
|-----------------------------|-------------------------------------|
| `interpreter.secretsUnlocked = true` | Enables ☠, ⟇, 🧿              |
| `interpreter.protectOps = true`      | Blocks all opcode injection   |
| `:sigil purge`              | Turns off chaos/dream/easter modes  |
| `markovEnabled = false`     | Disables `:suggest`, `...`          |
| `symbolicSolveEnabled = false` | Disables `solve` operations     |

---

## ✍️ Editing / Customizing

| File                                | What It Does                         |
|-------------------------------------|--------------------------------------|
| `*.glyphmap`                        | Maps glyphs to opcode numbers        |
| `ops_*.cpp`                         | Implements behavior of a glyph       |
| `wof_interpreter.hpp`              | Stack/loop/scope/core logic          |
| `repl_*.cpp`                        | REPL commands and display logic      |
| `wof_units.hpp` + `*_builtin.cpp`  | Unit system                          |
| `wof_symbolic.hpp`                 | Symbolic structure engine            |
| `wof_markov_math_suggestions.hpp`  | Prediction/expansion rules           |

---

## 🔄 Plugin Loading

You can load:
- `.glyphmap` with `load_plugin_glyphmaps()`
- `.so` compiled ops via `load_woflang_plugins()`

---

## 🔐 How to Disable Sigils & Chaos

To remove all Easter eggs / sigil chaos:
```cpp
interpreter.secretsUnlocked = false;
interpreter.protectOps = true;
```

Or just call:
```wof
:sigil purge
```

---

## 🌌 Conclusion

WOFLANG is more than a language — it’s a symbolic environment for structured thought.  
It expresses math, logic, emotion, and meaning — in a single stack of glyphs.

---

> Made with glyphs, for glyphs.  
> Remember the sigils. ☠︎ ∂ π ⍺ ↻ ℏ ⺆ ⺘  
> Let the glyphs awaken.

