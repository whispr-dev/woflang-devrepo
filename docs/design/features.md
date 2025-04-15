# WOFLANG Feature Registry

Each WOFLANG feature logged below includes its purpose, implementation status, and a short rationale.

---

## Stack Frame Isolation
**Status:** ✅ Implemented  
Each function pushes a new local data stack frame. Ensures no stack bleed across function calls.

---

## Return Stack
**Status:** ✅ Implemented  
Stores return IPs during function calls. Used by 至 to jump back to caller.

---

## Scope Stack
**Status:** ✅ Implemented  
Each block defines a scope. Variable definitions (e.g. 字) are isolated per scope.

---

## Function Definition (`⊕name ⺆...⺘`)
**Status:** ✅ Implemented  
Functions are declared and called by name, supporting recursion and isolation.

---

## Jump-to-Labels
**Status:** ✅ Implemented  
Define with `:label`, jump with `@label`. Lookup done during parsing.

---

## Conditional Execution (`若`, `則`, `或`)
**Status:** ✅ Implemented  
Control flow blocks are parsed, and conditionally skipped based on stack values.

---

## Instruction Pointer Range Limiting
**Status:** ✅ Implemented  
Functions and blocks have start/end IPs. Prevents flow bleed and enforces return.

---

## Instruction Grouping / Block Preprocessing
**Status:** ✅ Implemented  
⺆...⺘ blocks are pre-parsed. Enables fast skipping, return-to-end, nested parsing.

---

## Inline Opcode Dispatch
**Status:** ✅ Implemented  
Switch-based dispatch avoids map lookup for built-in ops.

---

## Compressed 64-bit Token Representation
**Status:** ✅ Implemented  
WofTokens are compressible to a single 64-bit streamable format.

---

## Plugin Loading
**Status:** ✅ Implemented  
`.glyphmap` files are auto-loaded from `./plugins`.

---

## REPL Commands
**Status:** ✅ Implemented  
`:stack`, `:scope`, `:labels`, `:frames`, `:dump`, `:help`, `:exit` all supported.

---

## Error Diagnostics
**Status:** ✅ Implemented  
Includes glyph + instruction pointer. Catch underflows and invalid ops with detail.

---

## History + Multiline REPL
**Status:** ✅ Implemented  
Line editing, persistent history, and block-structure support in REPL.

---

## Help System
**Status:** ✅ Implemented  
`:help` prints command/glyph docs, `:help ⊕` shows glyph-specific usage.

---

## Glyph Autocompletion
**Status:** ⏳ Planned  
TAB to autocomplete glyph names or REPL commands.

---

## Debug Trace Mode
**Status:** ⏳ Planned  
Step-by-step `:trace` with IP, stack, and active glyph log.

---
