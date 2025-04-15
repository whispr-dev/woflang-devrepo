# WOFLANG Roadmap v2 — Ascending the Glyph Mountain 🏔️

---

## ✅ COMPLETE — Core Engine Foundation
- [x] UTF-32 SIMD parser (AVX2 / AVX-512 / NEON)
- [x] Stack-based interpreter with block stack, scope stack, return stack
- [x] Scoped function execution with ⊕ ⺆ ⺘ and IP range enforcement
- [x] Inline opcode dispatch (no per-token map lookup)
- [x] Compressed token format (64-bit)
- [x] Full REPL system with history, commands, reload
- [x] Plugin loader: static, dynamic (.so), hot-reload, `.wofreplrc` config

---

## 🔜 WOFLANG 1.5 GOALS — Symbol Power & Language Control

### 🧮 Mathlib Plugin Expansion
- [ ] Implement real glyph-op logic for calculus, trig, algebra
- [ ] Create functional tests for plugins (`tests/pluginname_test.wof`)
- [ ] Enable math glyph aliases (ƒdiff → ∂, ƒint → ∫, etc.)

### ♻️ Control Flow Enhancements
- [ ] Loop constructs: `loop ⺆ ... ⺘`, `break`, `continue`
- [ ] `repeat N ⺆ ... ⺘`
- [ ] Conditional expressions as stack-returning ops

### 🪄 Macro Engine
- [ ] Define `glyph macro = expansion` (e.g. `Σ = push 0 :loop ⺆ + jump :loop`)
- [ ] Add `:macros` command + `.woflangmacros` loader

### 🧬 Symbolic Data Types
- [ ] Support symbolic expressions on stack
- [ ] Enable expression simplification, reduction, factoring
- [ ] Support `X + X = 2X`, `diff(X^2) = 2X`

---

## ✨ REPL & Dev Experience Polish
- [ ] Theme engine (`repltheme=...`)
- [ ] Custom REPL prompt string
- [ ] `.wofreplrc` advanced config loader
- [ ] `:tree`, `:scope`, `:trace` visualization

---

## 🎨 Visual + Input Layer
- [ ] Unified WOFLANG glyph font (custom .ttf or OTVar)
- [ ] Keymap/IME config: auto-suggest glyphs from ASCII
- [ ] Printable full-page glyph chart w/ categories
- [ ] Block folding, nesting tree drawing

---

## 🧠 Future & Ambitious
- [ ] Self-hosting: define WOFLANG in WOFLANG
- [ ] Visual editor: drag & drop glyphs
- [ ] Networked REPL / collaborative mode
- [ ] Remote glyph streaming / execution / storage

