# WOFLANG Glyph Reference

A living document mapping WOFLANG's symbolic glyphs to their purposes, opcodes, and usage.

---

## ⊕ (Function Definition)
**Opcode:** 1  
**Usage:** `⊕name ⺆ ... ⺘`  
**Summary:** Declares a new function block. Call with `call name`.

---

## 若 / 則 / 或 (Conditional If / Then / Else)
**Opcodes:** 若 = 2, 則 = 3, 或 = 4  
**Usage:**  
```
若 <condition>
  則 ⺆ ... ⺘
  或 ⺆ ... ⺘
```
**Summary:** Pops a value from the stack; if non-zero, enters 則 block, otherwise jumps to 或 or skips.

---

## 至 (Return)
**Opcode:** 5  
**Usage:** `至`  
**Summary:** Returns from the current function. Pops return address from return stack.

---

## ⺆ / ⺘ (Block Delimiters)
**Opcodes:** ⺆ = 6, ⺘ = 7  
**Usage:** `⺆ ... ⺘`  
**Summary:** Encloses function or conditional code. Tracked via block stack.

---

## emit
**Opcode:** 88  
**Usage:** `emit`  
**Summary:** Pops and prints the top of the data stack.

---

## +, -, *, /
**Opcodes:** + = 10, - = 11, * = 12, / = 13  
**Summary:** Basic math ops, operate on top 2 stack values.

---

## dup, swap, drop
**Opcodes:** dup = 20, swap = 21, drop = 22  
**Summary:** Stack manipulation.

---

## call
**Opcode:** 99  
**Usage:** `push 'name' call`  
**Summary:** Call a function by name.

---

## jump @label
**Opcode:** 100  
**Summary:** Jumps to a label defined earlier with `:label`.

---

## :label
**Opcode:** (none)  
**Summary:** Declares a label target for jump.

---

## 字 (Variable Define)
**Opcode:** 110  
**Usage:** `字 x 42`  
**Summary:** Defines variable `x = 42` in current scope.

---

## 読 (Variable Read)
**Opcode:** 111  
**Usage:** `読 x`  
**Summary:** Pushes value of `x` onto stack.

---

## assert
**Opcode:** 200  
**Summary:** Halts execution if stack top is zero.

---

(More glyphs will be added as modules expand.)

