; v.0.1.2 gettin slick now -we got specialised math, logic
; and string handling for optimised efficiency!
; also did some major boosts to early specialised math
; handler with greatly expanded math capability



; Initialize Registers and Memory
MOV R0, 0    ; Initialize R0 (General purpose register)
MOV R1, 0    ; Initialize R1 (General purpose register)
MOV R2, 0    ; Initialize R2 (General purpose register)
MOV R3, MEM[100]; R3: Start address of the command string in memory
MOV R4, 0    ; Initialize R4 (General purpose register)
MOV R5, 0    ; Initialize R5 (General purpose register)
MOV R6, 0    ; Initialize R6 (General purpose register)
MOV R7, 0    ; Initialize R7 (General purpose register)
MOV R8, 0    ; Initialize R8 (General purpose register)
MOV R9, 0    ; Initialize R9 (General purpose register)


; Pattern Identifiers (Types)
INTEGER EQU 1
FLOAT EQU 2
STRING EQU 3
COMMAND EQU 4
SYMBOL EQU 5
MATH_OP EQU 6   ; Identifier for math operations
LOGIC_OP EQU 7  ; Identifier for logic operations
STRING_OP EQU 8 ; Identifier for string operations


; Initialize Variables for Math, Logic, and String Processing
MOV R10, 0   ; Start index of the expression
MOV R11, 0   ; Length of the expression
MOV R12, 0   ; Type of expression (integer, float, logic, string)

; Start of Parsing Routine
PARSE_LOOP:
    LOAD R4, [R3 + R0]     ; Load the current character
    CMP R4, 0              ; Check for end of string (null terminator)
    JE PARSE_END           ; If end of string, end parsing

    ; Check if the character is a digit
    CMP R4, '0'
    JL NOT_DIGIT
    CMP R4, '9'
    JG NOT_DIGIT
    ; It's a digit, start collecting a number
    MOV R5, INTEGER        ; Set token type to INTEGER if it hasn't been set
    ADD R2, 1              ; Increment token length
    JMP NEXT_CHAR

NOT_DIGIT:
    ; Check if the character is a dot (.)
    CMP R4, '.'
    JE IS_FLOAT

    ; Check for math operators
    CMP R4, '+'            ; Check for addition operator
    JE IS_MATH_OP
    CMP R4, '-'            ; Check for subtraction operator
    JE IS_MATH_OP
    CMP R4, '*'            ; Check for multiplication operator
    JE IS_MATH_OP
    CMP R4, '/'            ; Check for division operator
    JE IS_MATH_OP

    ; Check for logic operators
    CMP R4, '而'           ; Check for AND operator
    JE IS_LOGIC_OP
    CMP R4, '或'           ; Check for OR operator
    JE IS_LOGIC_OP
    CMP R4, '⊕'            ; Check for XOR operator
    JE IS_LOGIC_OP
    CMP R4, '无'           ; Check for NOT operator
    JE IS_LOGIC_OP

    ; Existing character checks for letters, commands, symbols, etc.
    CMP R4, 'A'
    JL NOT_LETTER
    CMP R4, 'Z'
    JG CHECK_LOWERCASE
    ; Handle uppercase letter
    MOV R5, STRING
    ADD R2, 1
    JMP NEXT_CHAR

CHECK_LOWERCASE:
    CMP R4, 'a'
    JL NOT_LETTER
    CMP R4, 'z'
    JG NOT_LETTER
    ; Handle lowercase letter
    MOV R5, STRING
    ADD R2, 1
    JMP NEXT_CHAR

NOT_LETTER:
    ; Check if the character is a command symbol
    CMP R4, '門'
    JE IS_COMMAND
    CMP R4, '('
    JE IS_SYMBOL
    ; Add more checks for symbols if needed

IS_FLOAT:
    MOV R5, FLOAT          ; Set token type to FLOAT if a dot is found
    ADD R2, 1              ; Increment token length
    JMP NEXT_CHAR

IS_MATH_OP:
    MOV R5, MATH_OP        ; Set token type to MATH_OP
    ADD R2, 1              ; Increment token length
    ; Check if previous characters were digits to detect a math expression
    CMP R2, 0              ; If token length > 0, it's a math expression
    JG PROCESS_MATH_EXPRESSION
    JMP NEXT_CHAR

IS_LOGIC_OP:
    MOV R5, LOGIC_OP       ; Set token type to LOGIC_OP
    ADD R2, 1              ; Increment token length
    JMP PROCESS_LOGIC_EXPRESSION

NEXT_CHAR:
    ADD R0, 1              ; Move to the next character
    JMP PARSE_LOOP         ; Continue parsing

PARSE_END:
    ; Parsing is complete, handle the final token
    ; Reset R1, R2, R5 for next token
    MOV R1, R0             ; Set start position for the next token
    MOV R2, 0              ; Reset token length
    MOV R5, 0              ; Reset token type
    JMP NEXT_COMMAND       ; Jump to handle the next command or end

NEXT_COMMAND:
    ; Handle the next command or complete program logic
    HALT                   ; Stop execution for this example


; Math Handler Routine
MATH_HANDLER:
    ; This routine will parse and execute mathematical expressions
    MOV R13, R10           ; Set current index to start of math expression
    MOV R14, 0             ; Initialize a register to accumulate results
    MOV R15, [R3 + R13]    ; Load first operand

MATH_LOOP:
    ADD R13, 1             ; Move to the next character in the expression
    CMP R13, R11           ; Check if we've processed the entire expression
    JGE END_MATH_HANDLER

    LOAD R4, [R3 + R13]    ; Load the next character
    CMP R4, '+'            ; Check for addition operator
    JE ADDITION
    CMP R4, '-'            ; Check for subtraction operator
    JE SUBTRACTION
    CMP R4, '*'            ; Check for multiplication operator
    JE MULTIPLICATION
    CMP R4, '/'            ; Check for division operator
    JE DIVISION

    ; Handle each operation accordingly
    ; ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION should be defined below

END_MATH_HANDLER:
    ; Store the result of math operation
    MOV MEM[200], R14      ; Store result to memory for use in main logic
    RET                    ; Return to main execution


; Logic Handler Routine
LOGIC_HANDLER:
    ; This routine will parse and execute logical expressions
    MOV R13, R10           ; Set current index to start of logic expression
    MOV R14, [R3 + R13]    ; Load first operand (truth value)

LOGIC_LOOP:
    ADD R13, 1             ; Move to the next character in the expression
    CMP R13, R11           ; Check if we've processed the entire expression
    JGE END_LOGIC_HANDLER

    LOAD R4, [R3 + R13]    ; Load the next character
    CMP R4, 'AND'          ; Check for AND operator
    JE AND_OPERATION
    CMP R4, 'OR'           ; Check for OR operator
    JE OR_OPERATION
    CMP R4, 'XOR'          ; Check for XOR operator
    JE XOR_OPERATION
    CMP R4, 'NOT'          ; Check for NOT operator
    JE NOT_OPERATION

    ; Handle each operation accordingly
    ; AND_OP, OR_OP, EQ_OP, NOT_OP should be defined below

END_LOGIC_HANDLER:
    ; Store the result of logic operation
    MOV MEM[201], R14      ; Store result to memory for use in main logic
    RET                    ; Return to main execution

; String Handler Routine
STRING_HANDLER:

; This routine will parse and execute string manipulations
MOV R13, R10           ; Set current index to start of string operation
MOV R14, 0             ; Initialize a register to accumulate results
MOV R15, [R3 + R13]    ; Load first character of the string
STRING_LOOP: ADD R13, 1 ; Move to the next character in the string CMP R13, R11 ; Check if we've processed the entire string JGE END_STRING_HANDLER
LOAD R4, [R3 + R13]    ; Load the next character
; Implement specific string operations (concatenation, comparison, etc.)
END_STRING_HANDLER: ; Store the result of string operation MOV MEM[202], R14 ; Store result to memory for use in main logic RET ; Return to main execution

; Example Arithmetic Operation Routines (Addition, Subtraction, etc.) ADDITION: ADD R14, R15, [R3 + R13 + 1] ; Add the next operand to the result JMP MATH_LOOP ; Continue math loop

SUBTRACTION: SUB R14, R15, [R3 + R13 + 1] ; Subtract the next operand from the result JMP MATH_LOOP ; Continue math loop

MULTIPLICATION: MUL R14, R15, [R3 + R13 + 1] ; Multiply the result by the next operand JMP MATH_LOOP ; Continue math loop

DIVISION: DIV R14, R15, [R3 + R13 + 1] ; Divide the result by the next operand JMP MATH_LOOP ; Continue math loop

; Continue adding more routines for logic operations (AND_OP, OR_OP, etc.) and string operations as needed ; Add more error handling, checks, and advanced functionalities

; End of Program HALT ; Stop execution
