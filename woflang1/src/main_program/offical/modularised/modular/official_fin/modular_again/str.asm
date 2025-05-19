; str.asm

STR_CONCAT:
    ; String concatenation logic
    ; Assume R14 points to the start of the first string, R15 to the second
    ; Result in R16
    CONCAT R16, R14, R15
    JMP STR_LOOP

STR_PRINT:
    ; Print string logic
    ; Assume R14 contains address of string to print
    PRINT [R14]
    JMP STR_LOOP

STR_COMPARE:
    ; String comparison logic
    CMP R14, R15
    JEQ STR_EQUAL
    JNE STR_NOT_EQUAL

STR_EQUAL:
    MOV R16, 1  ; Strings are equal
    JMP STR_LOOP

STR_NOT_EQUAL:
    MOV R16, 0  ; Strings are not equal

STR_LOOP:
    MOV MEM[202], R16  ; Store result
    RET
