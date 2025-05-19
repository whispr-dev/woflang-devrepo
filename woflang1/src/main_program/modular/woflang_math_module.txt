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



LOGIC_MIN_FUNC;
    ; AND Functionality
    MIN  R1, R1, R2
    RET


LOGIC_MAX_FUNC;
    ; OR Functionality
    MAX  R1, R1, R2
    RET


LOGIC_XOR_FUNC;
    ; XOR Functionality
    XOR  R1, R1, R2
    RET



    LOGIC_NOT_FUNC;
    ; NOT Functionality
    NOT  R1,  R2
    RET



    LOGIC_NAND_FUNC;
    ; NAND Functionality
    NAND  R1, R1, R2
    RET




    LOGIC_NOR_FUNC;
    ; NOR Functionality
    NOR  R1, R!, R2
    RET



    LOGIC_IF_FUNC;
    ; IF Functionality
    IF R1, R1, R2
    RET



    LOGIC_THEN_FUNC;
    ; THEN Functionality
    THEN  R1, R1, R2
    RET



    LOGIC_ELSE_FUNC;
    ; ELSE Functionality
    ELSE  R1, R1, R2
    RET


; example for extending
;     LOGIC_MIN_FUNC;
;     ; AND Functionality
;      MIN  R1, R1, R2
;     RET




 JMP R49, '而'            ; Check if command is MIN (AND) (而)
 JEQ AND_ROUTINE
w ; MAX (OR) Functionality



 JMP R49, '或'            ; Check if command is MAX (OR) (或)
 JEQ OR_ROUTINE
 ; XOR Functionality




 JMP R49, '⊕'             ; Check if command is XOR (⊕)
 JEQ XOR_ROUTINE
 ; NOT Functionality



 JMP R49, '无'            ; Check if command is NOT (无)
 JEQ NOT_ROUTINE
 ; NAND Functionality



 JMP R49, '无‍而'         ; Check if command is NAND (无‍而)
 JEQ NAND_ROUTINE
 ; NOR Functionality




 JMP R49, '无‍或'         ; Check if command is NOR (无‍或)
 JEQ NOR_ROUTINE
 ; IF Functionality




 JMP R49, '若'            ; Check if command is IF (若)
 JEQ IF_ROUTINE
 ; THEN Functionality




 JMP R49, '则'            ; Check if command is THEN (则)
 JEQ THEN_ROUTINE
 




  ; ELSE Functionality
    JMP R49, '?'            ; Check if command is ELSE (?)
     JEQ ELSE_ROUTINE
