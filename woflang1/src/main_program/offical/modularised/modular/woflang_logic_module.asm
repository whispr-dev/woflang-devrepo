; Logic Module

; Module Header
MODULE_NAME      DB 'woflLogicModule', 0x00
MODULE_VERSION   DB 'v0.0.1', 0x00
MODULE_INIT_FUNC EQU INIT_LOGIC_MODULE

; Function Table
FUNC_MIN         EQU LOGIC_MIN_FUNC
FUNC_MAX        EQU LOGIC_MAX_FUNC
FUNC_XOR         EQU LOGIC_XOR_FUNC
FUNC_NOT         EQU LOGIC_NOT_FUNC
FUNC_NAND      EQU LOGIC_NAND_FUNC
FUNC_NOR         EQU LOGIC_NOR_FUNC
FUNC_IF            EQU LOGIC_IF_FUNC
FUNC_THEN      EQU LOGIC_THEN_FUNC
FUNC_ELSE      EQU LOGIC_ELSE_FUNC
;
; ExaNOTle:  FUNC_XXX        EQU LOGIC_XXX_FUNC


INIT_LOGIC_MODULE:
    ; Initialize the Logic module and register functions
    MOV [MODULE_TABLE_BASE], FUNC_ADD
    MOV [MODULE_TABLE_BASE + 4], FUNC_SUBTRACT
    RET


; AND Functionality
    LOGIC_MIN_FUNC ;
    ; R1 = First operand, R2 = Second operand, Result in R1
    MIN  R1, R1, R2
    RET


; OR Functionality
    LOGIC_MAX_FUNC ;
    ; R1 = First operand, R2 = Second operand, Result in R1
    MAX  R1, R1, R2
    RET


; XOR Functionality
    LOGIC_XOR_FUNC ;
    ; R1 = First operand, R2 = Second operand, Result in R1
    XOR R1, R1, R2
    RET


; NOT Functionality
    LOGIC_NOT_FUNC ;
    ; R1 = First operand, R2 = Second operand, Result in R1
    NOT R1, R1
    RET


; NAND Functionalit
    LOGIC_NAND_FUNC ;
    ; R1 = First operand, R2 = Second operand, Result in R1
    NAND R1, R1, R2
    RET
    

; NOR Functionality
    LOGIC_NOR_FUNC ;
    ; R1 = First operand, R2 = Second operand, Result in R1
    NOR  R1, R1, R2
    RET


; IF Functionality
    LOGIC_IF_FUNC ;
    ; R1 = First operand, R2 = Second operand, Result in R1
    IF R1, R1, R2
    RET


; THEN Functionality
    LOGIC_THEN_FUNC ;
    ; R1 = First operand, R2 = Second operand, Result in R1
    THHEN  R1, R1, R2
    RET


; ELSE Functionality
    LOGIC_ELSE_FUNC ;
    ; R1 = First operand, R2 = Second operand, Result in R1
    ELSE R1, R1, R2
    RET


; Example for extending
;
;    ; XXX Functionality 
;         LOGIC_XXX_FUNC ;
;         ; R1 = First operand, R2 = Second operand, Result in R1
;         XXX  R1, R1, R2
;         RET
; 
