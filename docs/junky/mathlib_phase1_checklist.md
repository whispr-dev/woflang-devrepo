# WOFLANG MathLib — Phase 1 Core Checklist

This phase establishes the foundational math operations that unlock symbolic and numeric processing.

---

## 🧠 Category: Constants

| Glyph | Name     | Opcode | Status | Notes             |
|-------|----------|--------|--------|-------------------|
| π     | Pi       | 3001   | ⏳      | Push value of π   |
| ℯ     | Euler's e| 3002   | ⏳      | Push value of e   |

---

## ∂ Calculus: Differentiation + Integration

| Glyph | Name       | Opcode | Status | Notes                   |
|-------|------------|--------|--------|-------------------------|
| ∂     | diff       | 3010   | ⏳      | Symbolic or numeric diff|
| ∫     | integrate  | 3011   | ⏳      | Symbolic or numeric int |

---

## 🔢 Exponentials and Roots

| Glyph | Name     | Opcode | Status | Notes                |
|-------|----------|--------|--------|----------------------|
| √     | sqrt     | 3020   | ⏳      | Square root          |
| ⁒     | pow      | 3021   | ⏳      | Raise to power       |
| ƒlog  | log      | 3022   | ⏳      | Natural log or base N|
| ƒexp  | exp      | 3023   | ⏳      | e^x                  |

---

## 🗃️ Files Involved

- `plugins/mathlib_constants/`
- `plugins/mathlib_calculus/`
- `plugins/mathlib_exponentials/`

Each should include:
- `*.glyphmap`
- `*.cpp`
- `spec.md` (from textbook)
- Opcode implementations with stub or real logic
- `.wof` test scripts (optional but helpful)

---

## 🔜 Next Step
Once these are solid, we can extend to:
- Trig: `sin cos tan`
- Complex: `re`, `im`, `conj`
- Modular: `mod`, `invmod`
- Symbolic algebra: `reduce`, `factor`, `solve`

