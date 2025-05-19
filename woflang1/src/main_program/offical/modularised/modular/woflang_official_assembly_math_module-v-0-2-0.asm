; Math Module: loads all math functions as
; far as basic arithmetic. must be kept this sm0l.

; Module Header
MODULE_NAME      DB 'woflMathModule', 0x00
MODULE_VERSION   DB 'v0.0.1', 0x00
MODULE_INIT_FUNC EQU INIT_MATH_MODULE

; Function Table
FUNC_ADD         EQU MATH_ADD_FUNC
FUNC_SUBTRACT    EQU MATH_SUBTRACT_FUNC
FUNC_MULTIPLY       EQU MATH_MUL_FUNC
FUNC_DIVIDE     EQU MATH_DIV_FUNC
FUNC_GREATER_THAN    EQU MATH_Greater_Than_FUNC
FUNC_LESS_THAN  EQU MATH_Less_Than_FUNC
FUNC_EQUALS     EQU MATH_MATH_Equals_FUNC
FUNC_DOESN'T_EQUAL   EQU MATH_Does_Not_Equal_FUNC
FUNC_GRETAER_THAN_OR_EQUAL   EQU MATH_Greater_than_Or_Equal_FUNC
LESS_THAN_OR_EQUAL  EQU MATH_Less_Than_Or_Equal_FUNC



INIT_MATH_MODULE:
    ; Initialize the Math module and register functions
    MOV [MODULE_TABLE_BASE], FUNC_ADD
    MOV [MODULE_TABLE_BASE + 4], FUNC_SUBTRACT
    MOV [MODULE_TABLE_BASE], FUNC_MUL
    MOV [MODULE_TABLE_BASE], FUNC_DIV
    MOV [MODULE_TABLE_BASE], FUNC_Greater_Than
    MOV [MODULE_TABLE_BASE], FUNC_Less_Than
    MOV [MODULE_TABLE_BASE], FUNC_Equals
    MOV [MODULE_TABLE_BASE], FUNC_Does_Not_Equal
    MOV [MODULE_TABLE_BASE], FUNC_Greater_Than_Or_Equal
    MOV [MODULE_TABLE_BASE], FUNC_Less_Than_Or_Equal


    RET

MATH_ADD_FUNC:
    ; Perform addition
    ADD R1, R1, R2
    RET

; MATH_SUBTRACT_FUNC:
    ; ; Perform subtraction
    ; SUB R10 R1, R12
   ; RET

; MATH_MULTIPLICATION_FUNC;
   ; ; Perform  multiplication
    MUL R1, R1, R2      
   ; RET

; MATH_DIVISION_FUNC;
   ; ; Perform division
    DIV R1, R1, R2      
   ; RET

; MATH_Greater Than Functionality_FUNC;
    ; ; Check if command is Greater Than
    Greater Than R1, R1, R2      
   ; RET

; MATH_Less Than Functionality_FUNC;
    ; ; Check if command is Less Than
    Less Than R1, R1, R2     
   ; RET

; MATH_Equals Functionality_FUNC;
    ; ; Check if command is Equal To
    Equals R1, R1, R2        
   ; RET

; MATH_Does Not Equal Functionality_FUNC;
    ; ; Check if command is Not Equal To
     Does Not Equal R1, R1, R2       
   ; RET

; MATH_Greater Than or Equal Functionality_FUNC;
    ; ; Check if command is Greater Than Or Equal To
    Greater Than or Equal R1, R1, R2     
   ; RET

; MATH_Less Than or Equal Functionality_FUNC;
    ; ; Check if command is Less Than Or Equal To
    Less Than or Equal R1, R1, R2       
   ; RET
