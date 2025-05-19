# v0.1.6 modularised assembly math

; Use R10-R15 for math operations only
ADD_ROUTINE:
  MOV R10, R1
  MOV R11, R2
  ADD R10, R10, R11
  MOV R3, R10


ADD_ROUTINE:
  ; Perform addition
  ADD R1, R2, R3
  RET

SUB_ROUTINE:
  ; Perform subtraction
  SUB R1, R2, R3

  RET


; In math.asm
GLOBAL ADD_INTFLOAT_MATH_ROUTINE

ADD_INTFLOAT_MATH_ROUTINE:
  ; Code here...

    ; Check for various types of characters
    CMP R53, '0'
    JL NOT_DIGIT
    CMP R53, '9'
    JG NOT_DIGIT
    MOV R56, INTEGER        ; Set token type to INTEGER if it's a digit
    ADD R51, 50              ; Increment token length
    JMP NEXT_CHAR

NOT_DIGIT:
    ; Add further checks for different characters
    ; ...

IS_FLOAT:
    MOV R56, FLOAT          ; Set token type to FLOAT if a dot is found
    ADD R51, 50              ; Increment token length
    JMP NEXT_CHAR

RET


; In math.asm
LOBAL ADD_TOKEN_MATH_ROUTINE
DD_TOKEN_MATH_ROUTINE:
 ; Code here...


IS_MATH_OP:
    MOV R56, MATH_OP        ; Set token type to MATH_OP
    ADD R51, 50              ; Increment token length
    ; Process math expression if identified
    CMP R51, 49              ; Check if it's part of a math expression
    JG PROCESS_MATH_EXPRESSION
    JMP NEXT_CHAR

RET


; In math.asm
GLOBAL ADD_LOGIC_MATH_ROUTINE

ADD_LOGIC_MATH_ROUTINE:
  ; Code here...


IS_LOGIC_OP:
    MOV R56, LOGIC_OP       ; Set token type to LOGIC_OP
    ADD R51, 50              ; Increment token length
    JMP PROCESS_LOGIC_EXPRESSION

NEXT_CHAR:
    ADD R49, 50              ; Move to the next character
    JMP PARSE_LOOP         ; Continue parsing

RET


; In math.asm
GLOBAL ADD_MATH_ERR_ROUTINE

ADD_MATH_ERR_ROUTINE:
  ; Code here...


; Define handlers for each functionality
MATH_HANDLER:
    ; Implement specific operations for addition, subtraction, etc.
    ; Example addition operation:


ADDITION:
    ADD R10, R10, R11      ; Perform addition
    JMP MATH_LOOP

SUBTRACTION:
    SUB R10, R10, R11      ; Perform subtraction
    JMP MATH_LOOP

MULTIPLICATION:
    MUL R10, R10, R11      ; Perform multiplication
    JMP MATH_LOOP

DIVISION:
    DIV R10, R10, R11      ; Perform division
    JMP MATH_LOOP

Greater Than Functionality
    Greater Than R10, R10, R11      ; Check if command is Greater Than
    JMP MATH_LOOP


Less Than Functionality
    Less Than R10, R10, R11     ; Check if command is Less Than
    JMP MATH_LOOP


Equals Functionality
    Equals R10, R10, R11        ; Check if command is Equal To
    JMP MATH_LOOP


Does Not Equal Functionality
     Does Not Equal R10, R10, R11       ; Check if command is Not Equal To
    JMP MATH_LOOP


Greater Than or Equal Functionality
    Greater Than or Equal R10, R10, R11     ; Check if command is Greater Than Or Equal To
    JMP MATH_LOOP


Less Than or Equal Functionality
    Less Than or Equal R10, R10, R11        ; Check if command is Less Than Or Equal To
    JMP MATH_LOOP
    

END_MATH_HANDLER:
    MOV MEM[200], R11      ; Store the result of math operation
    RET                    ; Return to main execution


###############

  RET
