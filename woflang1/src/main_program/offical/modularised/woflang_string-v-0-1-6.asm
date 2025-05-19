# v0.1.6 modularised assembly string

; Use R30-R35 for string operations only
ADD_ROUTINE:
  MOV R30, R1
  MOV R31, R2
  ADD R30, R30, R31
  MOV R3, R30


CONCAT_ROUTINE:
  ; Concatenate strings
  ; (String manipulation logic here)

  RET


; In string.asm
GLOBAL ADD_PARSER_STRING_ROUTINE

ADD_PARSEER_STRING_ROUTINE:
  ; Code here...


; String Handler Routine

; String Handler Routine (for string manipulations)
STRING_HANDLER:
    MOV R33, R30           ; Start index of string operation
    ; Continue processing string operations like concatenation, comparison, etc.

; This routine will parse and execute string manipulations
MOV R33, R30           ; Set current index to start of string operation
MOV R34, 0             ; Initialize a register to accumulate results
MOV R35, [R3 + R33]    ; Load first character of the string

  RET


; In string.asm
GLOBAL ADD_PARVAR_STRING_ROUTINE

ADD_PARVAR_STRING_ROUTINE:
  ; Code here...

; Command Parsing
PARSE_COMMAND:
    ; Parse the command...
    CMP R0, KNOWN_COMMAND
    JEQ VALID_COMMAND

RET



; In string.asm
GLOBAL ADD_PARARR_STRING_ROUTINE

ADD_PARARR_STRING_ROUTINE:
  ; Code here...

PARSE_COMMAND:
    ; Assuming R0 contains the current command
    CMP R0, 'DECLARE_ARRAY'
    JEQ DECLARE_ARRAY

    CMP R0, 'ACCESS_ARRAY_ELEMENT'
    JEQ ACCESS_ARRAY_ELEMENT

    CMP R0, 'MODIFY_ARRAY_ELEMENT'
    JEQ MODIFY_ARRAY_ELEMENT

    CMP R0, 'ITERATE_ARRAY'
    JEQ ITERATE_ARRAY

    ; Continue with other command parsing...
    RET

RET



; In string.asm
GLOBAL ADD_FUNCOVLD_STRING_ROUTINE

ADD_FUNCOVLD_STRING_ROUTINE:
  ; Code here...

PARSE_FUNCTION:
    CMP R0, 'FUNCTION'      ; Check if it's a FUNCTION keyword
    JNE NEXT_PARSE          ; If not, continue to other parse logic

    ; Parse the function name
    READ_FUNCTION_NAME      ; Read function name into R1
    MOV R2, FUNCTION_TABLE[R1] ; Check if the function already exists
    JEQ FUNCTION_OVERLOAD   ; If exists, handle overloading

    ; If not found, this is a new function
    STORE_NEW_FUNCTION      ; Store new function in FUNCTION_TABLE

    ; Parse parameters and store types in FUNCTION_TABLE
    PARSE_PARAMETERS

    ; Parse function body and store the function address
    PARSE_FUNCTION_BODY

    JMP PARSE_NEXT

FUNCTION_OVERLOAD:
    ; Check if the signature (parameter types) matches an existing overload
    CHECK_FUNCTION_SIGNATURE
    JNE STORE_OVERLOAD      ; If not matched, store as a new overload

    ; If matched, error: function already exists with the same signature
    ERROR_DUPLICATE_FUNCTION
    JMP PARSE_NEXT

STORE_OVERLOAD:
    ; Store the overloaded function in FUNCTION_TABLE with its parameter types
    STORE_FUNCTION_OVERLOAD
    JMP PARSE_NEXT


FUNCTION_TABLE:
    add -> [
        (INTEGER, INTEGER) -> address1,
        (FLOAT, FLOAT) -> address2,
        (STRING, STRING) -> address3
    ]
    ...

RET



; In string.asm
GLOBAL ADD_CMDHDL_STRING_ROUTINE

ADD_CMDHDL_STRING_ROUTINE:
  ; Code here...

    CALL PARSE_COMMAND           ; Parse the command and handle errors

RET


; String Handler Routine

; String Handler Routine (for string manipulations)
STRING_HANDLER:
    MOV R33, R30           ; Start index of string operation
    ; Continue processing string operations like concatenation, comparison, etc.

; This routine will parse and execute string manipulations
MOV R33, R30           ; Set current index to start of string operation
MOV R34, 0             ; Initialize a register to accumulate results
MOV R35, [R3 + R33]    ; Load first character of the string
STRING_LOOP: ADD R33, 1 ; Move to the next character in the string CMP R33, R31 ; Check if we've processed the entire string JGE END_STRING_HANDLER


LOAD R4, [R3 + R13]    ; Load the next character
; Implement specific string operations (concatenation, comparison, etc.)

END_STRING_HANDLER: ; Store the result of string operation     

MOV MEM[202], R34      ; Store the result of string operation ; Store result to memory for use in main logic     


RET                    ; Return to main execution


############################

string err
