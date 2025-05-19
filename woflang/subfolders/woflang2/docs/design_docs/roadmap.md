# WOFLANG Roadmap

## 1.0 — Core Runtime (COMPLETE)
- [x] UTF-32 SIMD parsing via AVX2/AVX-512/NEON
- [x] Token pool allocator
- [x] Opcode dispatch (inline + fallback)
- [x] Block parsing and scope stack
- [x] Function calls and returns
- [x] REPL, plugins, glyphmaps

## 1.1 — Debugging + DX Tools (In Progress)
- [x] :stack / :scope / :labels / :dump REPL commands
- [x] Instruction pointer tracking and block limits
- [x] Error diagnostics with IP and offending glyph
- [ ] Tab autocompletion
- [ ] :trace stepping

## 1.2 — Advanced Language Features
- [ ] Macros and user-defined symbols
- [ ] Scoped mutation / var binding ops
- [ ] .woftok64 compressed code streams with direct execution
- [ ] Callable REPL-saved functions

## Future Ideas
- [ ] Glyph animation in REPL (ripple effects, blocks folding)
- [ ] Remote glyph eval / visualization
- [ ] Self-rewriting runtime glyphs (⟁⟁⟁)
