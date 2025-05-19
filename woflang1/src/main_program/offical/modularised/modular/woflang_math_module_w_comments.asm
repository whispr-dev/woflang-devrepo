; MathModule.asm
; This is an example module providing basic math functions.

; Module Header
MODULE_NAME      DB 'MathModule', 0x00
MODULE_VERSION   DB 'v1.0.0', 0x00
MODULE_INIT_FUNC EQU INIT_MATH_MODULE

; Function Table
FUNC_ADD         EQU MATH_ADD_FUNC
FUNC_SUBTRACT    EQU MATH_SUBTRACT_FUNC

; Initialization Function
INIT_MATH_MODULE:
    ; Register functions in the interpreter's function table
    MOV [MODULE_TABLE_BASE], FUNC_ADD          ; Register ADD function
    MOV [MODULE_TABLE_BASE + 4], FUNC_SUBTRACT ; Register SUBTRACT function
    RET

; ADD Function
MATH_ADD_FUNC:
    ; R1 = First operand, R2 = Second operand, Result in R1
    ADD R1, R1, R2
    RET

; SUBTRACT Function
MATH_SUBTRACT_FUNC:
    ; R1 = First operand, R2 = Second operand, Result in R1
    SUB R1, R1, R2
    RET
