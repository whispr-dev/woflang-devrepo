# WOFLANG — The Symbolic Programming Language of Glyphs

Welcome to **WOFLANG**, a fully stack-based, Unicode-powered, REPL-driven symbolic programming language.

WOFLANG is designed for math, AI, and expressive power — built from the ground up using symbolic glyphs instead of ASCII keywords.

---

## Why WOFLANG?

- Glyphs make structure *visible*
- Functions are boxed, blocks are bounded
- Loops curve, returns point, math symbols mean what they show
- Code becomes expression — not just execution

WOFLANG is built not just to *compute*, but to *communicate thought*.

---

## Getting Started

### Folder Layout

```
woflang/
├── core/              # Interpreter core
├── parser/            # SIMD glyph stream parsing
├── repl/              # Full REPL + debugger
├── ops/               # Opcode handlers
├── io/                # Plugin + glyph loader
├── plugins/           # Glyph .so plugins + .glyphmap files
├── tests/             # .wof test scripts
└── CMakeLists.txt     # Build config
```

### Build & Run

```bash
mkdir build && cd build
cmake ..
make
./woflang
```

---

## Language Overview

WOFLANG is:

- **Stack-based**: Values are pushed and popped
- **Block-structured**: Code grouped via
- **Unicode-native**: Every operation is a glyph

---

### Key Syntax

| Glyph     | Meaning        | Description                |
|-----------|----------------|----------------------------|
| ⊕        | `define`       | Define a function          |
| ⺆ ⺘     | `begin/end`    | Encloses blocks            |
| 若 則 或  | `if then else` | Conditional execution      |
| 至        | `return`       | End a function or block    |
| ⟳        | `loop`         | Infinite loop block        |
| ⨯        | `repeat`       | Repeat N times              |
| ⍺        | `for`          | For loop with loop var `i`  |
| ↻        | `break/cont`   | Exit or continue loop       |

---

### Example

```wof
⊕double ⺆
  dup
  +
  至
⺘

push 7
call double
emit
```

---

## Math Features

WOFLANG supports symbolic and numerical math via plugins:

- ∂ → diff
- ∫ → integrate
- √ → sqrt
- π, ℯ → constants
- map, reduce, dot → vector ops

```wof
[ 1 2 3 ] map     # → [2 4 6]
[ 1 2 3 ] reduce  # → 6
[ 1 2 3 ] [ 4 5 6 ] dot  # → 32
```

---

## Control Flow

```wof
push 0
push 10
push 1
⍺ ⺆
  読 i
  emit
↻
⺘
```

Creates a for-loop from 0 to 10 by 1 using `i` as the loop variable.

---

## Lists

WOFLANG supports lists using brackets:

```wof
[ 1 2 [ 3 4 ] 5 ] length emit
```

You can `get`, `append`, `map`, `reduce`, and even nest them infinitely.

---

## .EPL Features

```txt
:stack        # view current stack
:scope        # view current variable bindings
:tree         # view block nesting tree
:blocks       # list all blocks
:block 7      # show block at IP 7
:trace        # turn on step tracer
:untrace      # disable tracer
:bindings     # list input aliases
```

---

### Sample Trace Output

```txt
[TRACE] IP 3 | Glyph: emit | Opcode: 88 | In Block: ⺆ IP 0 (loop) → ⺘ IP 7 | Stack: [42] | Scope: { i=6 }
```

---

## Input Aliases

```wof
:bind df ∂
:bind pi π
```

Aliases are saved in `~/.wofbinds` and loaded automatically on startup.

---

## Plugin System

- `.glyphmap` defines glyph → opcode
- `.cpp` file defines opcode logic
- Compile as `.so` → auto-loaded by REPL

```cpp
extern "C" void register_woflang_plugin(WofInterpreter& vm) {
  vm.registerOpcode(3010, [](WofInterpreter& vm, const WofToken&) {
    // ∂: differentiate
  });
}
```

---

## Internal Structure

### Stack Frame Diagram

```
+---------------------------+
|  returnStack              |
|  blockStack               |
|  scopeStack               |
|  loopContext              |
|  valueStack (int, list)   |
+---------------------------+
```

### Block Parsing Tree

```
⊕main ⺆
  若 ⺆
    emit
  ⺘
  ⨯ ⺆
    emit
  ⺘
⺘
```

---

## Extending the Language

Want to add a new glyph?

1. Add to `glyphs.tsv`
2. Create `.cpp` plugin file
3. Register with `registerOpcode(...)`
4. Add docs to `unicode_glyphmap_spec.md`

---

## Design Philosophy

> A language for the future of thinking.

- WOFLANG prioritizes clarity, structure, and expressivity
- It embraces the *visual*, the *symbolic*, and the *mathematical*
- It is meant to be seen — and remembered

---

## Roadmap Highlights

- [x] Full REPL with trace, scope, stack, reload
- [x] Plugin loader (.so + .glyphmap)
- [x] Phase 1 MathLib (∂, ∫, √, π, ℯ)
- [x] List types with map/reduce/dot
- [x] Keybinding + alias system
- [ ] Macros and user-definable compound glyphs
- [ ] Symbolic expression trees
- [ ] Table/map types
- [ ] Visual editor playground

---

## License

MIT License  
Made by glyphs, with glyphs, for glyphs.

