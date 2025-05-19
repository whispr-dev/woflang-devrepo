; Math Module

; Module Header
MODULE_NAME      DB 'MathModule', 0x00
MODULE_VERSION   DB 'v1.0.0', 0x00
MODULE_INIT_FUNC EQU INIT_MATH_MODULE

; Function Table
FUNC_ADD         EQU MATH_ADD_FUNC
FUNC_SUBTRACT    EQU MATH_SUBTRACT_FUNC

INIT_MATH_MODULE:
    ; Initialize the Math module and register functions
    MOV [MODULE_TABLE_BASE], FUNC_ADD
    MOV [MODULE_TABLE_BASE + 4], FUNC_SUBTRACT
    RET

MATH_ADD_FUNC:
    ; Perform addition
    ADD R1, R2, R1
    RET

MATH_SUBTRACT_FUNC:
    ; Perform subtraction
    SUB R1, R2, R1
    RET
