# 🛠️ WOFLANG Setup Guide — Bringing the Glyph Machine to Life

This document walks you through integrating and activating every WOFLANG system currently in place — from parser to plugins, REPL to keybinds.

---

## 🔧 1. Project Structure

Ensure your folders are set up like:

```
woflang/
├── core/
├── parser/
├── simd/
├── repl/
├── ops/
├── io/
├── plugins/
├── tests/
└── CMakeLists.txt
```

---

## 🧠 2. Interpreter Integration

Ensure `WofInterpreter` includes:

- `loopContext`, `BlockRegistry`, `KeyBindingManager`
- `dataStack` → becomes `valueStack` (WofValue support)
- Methods:
  - `push(int64_t)`, `pushValue(WofValue)`, `pop()`, `popValue()`
  - `findBlockEnd()`

---

## 📦 3. Core Includes

In `main.cpp` or `woflang_vm_executor.cpp`, include:

```cpp
#include "load_woflang_plugins.cpp"
#include "dynamic_glyph_loader.cpp"
#include "wof_watch_autostart_patch.cpp"
#include "wofreplrc_loader_extended.cpp"
#include "load_phase1_mathlib_plugins.cpp"
#include "wof_keybind_autoload_patch.cpp"
```

Call in `main()`:

```cpp
WofInterpreter interpreter;
BlockRegistry blockRegistry;
KeyBindingManager keybinds;

load_repl_config(interpreter);
load_plugin_glyphmaps(interpreter);
load_all_woflang_plugins(interpreter);
load_phase1_mathlib_plugins(interpreter);
load_keybinds(keybinds);
start_plugin_autowatch(interpreter);
```

---

## 📜 4. REPL Setup

Commands to wire in:
```cpp
if (line.starts_with(":bind")) { handle_bind_and_save(keybinds, line); continue; }
if (line == ":bindings") { keybinds.listBindings(); continue; }
if (line == ":blocks") { handle_blocks_command(interpreter.blockRegistry); continue; }
if (line == ":tree") { handle_block_tree_command(interpreter.blockRegistry); continue; }
if (line.starts_with(":block ")) { handle_block_lookup_command(interpreter.blockRegistry, line); continue; }
if (line == ":trace") { enable_trace(); continue; }
if (line == ":untrace") { disable_trace(); continue; }

line = expandKeybindings(line, keybinds);  // replace aliases
```

---

## 📜 5. Glyphmap Imports

Ensure glyphmaps include:

- `[ ] length get append` (3090–3102)
- `map reduce dot` (3110–3112)
- Loop: `⟳ ⨯ ⍺ ↻ 🛑`
- Math: `∂ ∫ √ π e`

---

## ✅ 6. Final Tips

- Test mathlib with `test_list_ops.wof`
- Use `:bindings`, `:tree`, `:stack`, `:scope`, `:dump`
- Bind common glyphs (`df → ∂`, `pi → π`) with `:bind`

You're now ready to write code in glyphs, execute it symbolically, and extend your language live.

✨ WOFLANG is yours.

