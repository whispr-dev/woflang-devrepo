; err.asm

ERR_REPORT:
    MOV R96, R95  ; Load error code
    MOV R97, R94  ; Load line number
    ; Display error code and line number
    HALT
    RET

ERR_DIVISION_BY_ZERO:
    MOV R95, ERR_RUNTIME  ; Set runtime error code
    JMP ERR_REPORT

ERR_UNRECOGNIZED_COMMAND:
    MOV R95, ERR_UNRECOGNIZED
    JMP ERR_REPORT

ERR_RUNTIME:
    MOV R95, ERR_RUNTIME
    JMP ERR_REPORT

; Error codes
ERR_RUNTIME EQU 0x05
ERR_UNRECOGNIZED EQU 0x03
