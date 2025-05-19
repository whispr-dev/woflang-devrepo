
若 (opcode 2) → pops a condition value from the stack

If true → continues into the 則 (then) block

If false → jumps directly to the next 或 (else) or ⺘ (block end)

則 (opcode 3) → acts as a no-op anchor (just structural)

或 (opcode 4) → acts as the else fallback branch