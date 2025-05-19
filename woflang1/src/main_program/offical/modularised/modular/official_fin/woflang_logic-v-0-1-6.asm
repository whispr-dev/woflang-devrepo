# v0.1.6 modularised assembly logic

; Use R20-R25 for logic operations only
AND_ROUTINE:
  MOV R20, R1
  MOV R21, R2
  AND R20, R20, R21
  MOV R3, R20
  RET


AND_ROUTINE:
  ; Perform AND operation
  AND R1, R2, R3
  RET

OR_ROUTINE:
  ; Perform OR operation
  OR R1, R2, R3
  RET


; In logic.asm
GLOBAL ADD_LOGIC_ERR_ROUTINE

ADD_LOGIC_ERR_ROUTINE:
  ; Code here...


; Logic Handler Routine (define operations like AND, OR, XOR, etc.)
LOGIC_HANDLER:
    MOV R23, R20           ; Start index of logic expression
    MOV R24, [R3 + R23]    ; Load first operand (truth value)
    ; Continue processing logic operations
    ; Define specific logic operations like AND, OR, XOR, NOT


    JEQ DIV_ROUTINE

    ; MIN (AND) Functionality
    JMP R49, '而'            ; Check if command is MIN (AND) (而)
    JEQ AND_ROUTINE

    ; MAX (OR) Functionality
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

 RET


END_LOGIC_HANDLER:
    MOV MEM[201], R24      ; Store the result of logic operation
    RET                    ; Return to main execution


#######################
