; String Module

; Module Header
MODULE_NAME      DB 'woflStringModule', 0x00
MODULE_VERSION   DB 'v0.0.1', 0x00
MODULE_INIT_FUNC EQU INIT_STRING_MODULE

; Function Table
FUNC_PARSE         EQU STRING_PARSE_FUNC
FUNC_CMP              EQU STRING_CMP_FUNC
FUNC_DECLARE   EQU STRING_DECLARE_FUNC
FUNC_ACCESS     EQU STRING_ACCESS_FUNC
FUNC_MODIFY     EQU STRING_MODIFY_FUNC
FUNC_ITERATE   EQU STRING_ITERATE_FUNC
;
; ExaNOTle:  FUNC_XXX        EQU STRING_XXX_FUNC


INIT_STRING_MODULE:
    ; Initialize the String module and register functions
    MOV [MODULE_TABLE_BASE], FUNC_PARSE
    MOV [MODULE_TABLE_BASE], FUNC_CMP
    MOV [MODULE_TEBLE_BASE], FUNC_DECLARE
    MOV [MODULE_TEBLE_BASE], FUNC_ACCESS
    MOV [MODULE_TEBLE_BASE], FUNC_MODIFY 
    MOV [MODULE_TEBLE_BASE], FUNC_ITERATE
    RET


; PARSE Functionality
    STRING_PARSE_FUNC ;
    ; R1 = First operand, R2 = Second operand, Result in R1
    PARSE  R1, R1, R2
     RET


; CMP Functionality
    STRING_CMP_FUNC ;
    ; R1 = First operand, R2 = Second operand, Resultin R1
    CMP R1,R1, R2
    RET


; DECLARE Functionality
    STRING_DECLARE_FUNC ;
    ; R1 = First operand, R2 = Second operand, Resultin R1
    DECLARE R1,R1, R2
    RET


; ACCESS Functionality
    STRING_ACCESS_FUNC ;
    ; R1 = First operand, R2 = Second operand, Resultin R1
    ACCESS R1,R1, R2
    RET


; MODIFY Functionality
    STRING_MODIFY_FUNC ;
    ; R1 = First operand, R2 = Second operand, Resultin R1
    MODIFY R1,R1, R2
    RET


; ITERATE Functionality
    STRING_ITERATE_FUNC ;
    ; R1 = First operand, R2 = Second operand, Resultin R1
    ITERATE R1,R1, R2
    RET


; Example formatting for string module
; ; PARSE Functionality
;       STRING_PARSE_FUNC ;
;      ; R1 = First operand, R2 = Second operand, Result in R1
;      PAARSE  R1, R1, R2
;       RET
