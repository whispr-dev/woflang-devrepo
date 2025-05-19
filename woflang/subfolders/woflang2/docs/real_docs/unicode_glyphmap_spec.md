# WOFLANG Unicode Glyph Mapping Spec

This document defines the visual and symbolic role of each glyph used in WOFLANG,
mapped to their opcode and intended category.

---

| Glyph | Unicode | Opcode | Role         | Category       | Notes |
|-------|---------|--------|--------------|----------------|-------|
| ⊕     | U+2295  | 1      | Define func  | Control        | Function declaration |
| 若     | U+82E5  | 2      | If           | Conditional    | Branching |
| 則     | U+5247  | 3      | Then         | Conditional    | |
| 或     | U+6216  | 4      | Else         | Conditional    | |
| 至     | U+81F3  | 5      | Return       | Control        | End function |
| ⺆     | U+2E86  | 6      | Block start  | Block          | Used with ⺘ |
| ⺘     | U+2E98  | 7      | Block end    | Block          | |
| emit  | (ASCII) | 88     | Emit stack   | IO             | Print |
| +     | +       | 10     | Add          | Math           | |
| -     | -       | 11     | Subtract     | Math           | |
| *     | *       | 12     | Multiply     | Math           | |
| /     | /       | 13     | Divide       | Math           | |
| dup   |         | 20     | Duplicate    | Stack          | |
| swap  |         | 21     | Swap top 2   | Stack          | |
| drop  |         | 22     | Drop top     | Stack          | |
| call  |         | 99     | Call func    | Control        | |
| @label|         | 100    | Jump label   | Labeling       | |
| :label|         | 101    | Define label | Labeling       | |
| 字     | U+5B57  | 110    | Define var   | Variable       | |
| 読     | U+8AAD  | 111    | Read var     | Variable       | |
| assert|         | 200    | Assert       | Debug          | |
| ⟳     | U+27F3  | 201    | Loop         | Looping        | Infinite loop |
| ⨯     | U+2A2F  | 202    | Repeat       | Looping        | Repeat N times |
| ⍺     | U+237A  | 203    | For loop     | Looping        | From X to Y step Z |
| 🛑     | U+1F6D1 | 204    | Break        | Looping        | Exit loop |
| ↻     | U+21BB  | 205    | Continue     | Looping        | Next iteration |

---

## Guidelines for Font Mapping
- All glyphs must be **monospaced**
- Looping/flow glyphs should be bold or circled
- Variable/stack glyphs can be lighter
- Color or weight tiers may be used to indicate block nesting in future

Future glyphs (macros, visual folding, metaprogramming) will occupy:
- U+2B00–2BFF (ARROWS & GLYPH BLOCK)
- U+1D400+ (Mathematical Alphanumeric Symbols)

