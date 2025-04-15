from pathlib import Path

# Create easter egg & forbidden glyph plan markdown file
easter_eggs_doc = Path("/mnt/data/woflang_easter_eggs_and_secrets.md")

easter_eggs_doc.write_text("""\
# 🥚 WOFLANG Easter Eggs & Forbidden Glyphs

WOFLANG is a serious symbolic language — but serious symbols need strange shadows.

---

## 🧩 Hidden Commands

| Command         | Effect |
|----------------|--------|
| `:egg`          | Print a random cryptic glyph haiku |
| `:unlock chaos` | Unlock forbidden glyphs for one session |
| `:dreamlog`     | Show surreal glyph-based debug output |
| `:mirror`       | Flip interpreter view (reverse-stack mode) |
| `:deity`        | Enable unlimited recursion, disable all guards |
| `:glitchmode`   | Randomly replace glyphs with others for fun |
| `:wofsigil`     | Show the hidden glyph totem (ASCII logo) |

---

## 🚫 Forbidden Glyphs

These glyphs only activate after `:unlock chaos`:

| Glyph | Effect             | Notes |
|-------|--------------------|-------|
| `☠`   | Kills the stack    | Clears stack, emits `[☠]` |
| `⛔`   | Block execution    | Prevents block from running |
| `💀`   | Fork into error VM | Simulates crash-style path |
| `🌀`   | Infinite recurse   | Locks loopContext on itself |
| `🧿`   | Divine protect     | Prevents any opcode override |
| `🩸`   | Bleeds values      | Randomly leaks scope vars |
| `🎲`   | Push random glyph  | Useful for chaos scripts |

---

## 🕳️ Secret Behaviors

- `call 🛸` runs hidden `⊕_cosmic` if defined
- Typing `..` into REPL 5 times triggers secret poem
- `stack contains ☯` enables balance mode (warns on unbalanced blocks)
- `emojify mode` shows full stack in emoji symbols

---

## 🎨 Example Egg: `:egg`

```text
[EGG]
  ∂ dissolves
  into a sea of glyphs
  ⍺ watches silently
