section .data
    ; Module Header Information
    MODULE_NAME      db 'woflangSymbolModule', 0x00
    MODULE_VERSION   db 'v0.0.1', 0x00
    MODULE_INIT_FUNC equ INIT_SYMBOL_MODULE

    ; Character Map or List
    CHARACTER_MAP:
        db 'A', 'B', 'C', 'D', 0x00  ; Example map
; arithmetic
        db '齊', 0        ; ADD Command
        db '隶', 0        ; SUBTRACT Command
        db '丶', 0        ; MULTIPLY Command
        db '丿', 0        ; DIVIDE Command
        db '大', 0        ; GREATER Command
        db '小', 0        ; LESS Command
        db '卜', 0        ; EQUALS Command
        db '丨', 0        ; DOES NOT EQUAL Command
        db '走', 0        ; GREATER THAN OR EQUALS Command
        db '夊', 0        ; LESS THAN OR EQUALS Command

; loop
        db '老', 0        ; WHILE Command
        db '至', 0        ; FOR Command
        db '舛', 0        ; EXCEPT Command
        db '止', 0        ; BREAK Command
        db '己', 0        ; STRING Command
        db '支', 0        ; COUNT Command
        db '比', 0        ; BOOLEAN Command

; command
        db '終', 0        ; END Command
        db '響', 0        ; ECHO Command
        db '釆', 0        ; DONE Command
        db '卩', 0        ; EXIT Command
        db '押', 0        ; PROMPT Command
        db '⽰', 0        ; INPUT Command
        db '眠', 0        ; SLEEP Command

; interwebs
        db '⺒', 0        ; HTTP Command
        db '⺨', 0        ; PROXY Command
        db '⽪', 0        ; USER_AGENT Command
        db '⽓', 0        ; SERVER Command

; memory & printing
        db '待', 0        ; WAIT Command
        db '⻤', 0        ; NULL Command
        db '⺙', 0        ; PRINT Command
        db '⺆', 0        ; SYS_CALL Command
        db '⺘', 0        ; FUNCTION Command
        db '工', 0        ; MOVE Command
        db '⺣', 0        ; ATTRIBUTE Command
        db '道', 0        ; PATH Command
        db '⺢', 0        ; TYPE Command
        db '字', 0        ; CHAR Command
        db '読', 0        ; READ Command

    ; Command to Function Handler Mapping
    SYMBOL_COMMANDS:
        db 'ADD_SYMBOL', 0x00
        dd ADD_SYMBOL_HANDLER
        db 'SUB_SYMBOL', 0x00
        dd SUB_SYMBOL_HANDLER
        db 'MUL_SYMBOL', 0x00
        dd MUL_SYMBOL_HANDLER
        db 'DIV_SYMBOL', 0x00
        dd DIV_SYMBOL_HANDLER
        db 'GT_SYMBOL', 0x00
        dd GT_SYMBOL_HANDLER
        db 'LT_SYMBOL', 0x00
        dd LT_SYMBOL_HANDLER
        db 'EQ_SYMBOL', 0x00
        dd EQ_SYMBOL_HANDLER
        db 'DNE_SYMBOL', 0x00
        dd DNE_SYMBOL_HANDLER
        db 'GTE_SYMBOL', 0x00
        dd GTE_SYMBOL_HANDLER
        db 'LTE_SYMBOL', 0x00
        dd LTE_SYMBOL_HANDLER
        db 'WHILE_SYMBOL', 0x00
        dd WHILE_SYMBOL_HANDLER
        db 'FOR_SYMBOL', 0x00
        dd FOR_SYMBOL_HANDLER
        db 'EXCEPT_SYMBOL', 0x00
        dd EXCEPT_SYMBOL_HANDLER
        db 'BREAK_SYMBOL', 0x00
        dd BREAK_SYMBOL_HANDLER
        db 'STR_SYMBOL', 0x00
        dd STR_SYMBOL_HANDLER
        db 'COUNT_SYMBOL', 0x00
        dd COUNT_SYMBOL_HANDLER
        db 'BOOL_SYMBOL', 0x00
        dd BOOL_SYMBOL_HANDLER
        db 'END_SYMBOL', 0x00
        dd END_SYMBOL_HANDLER
        db 'ECHO_SYMBOL', 0x00
        dd ECHO_SYMBOL_HANDLER
        db 'DONE_SYMBOL', 0x00
        dd DONE_SYMBOL_HANDLER
        db 'EXIT_SYMBOL', 0x00
        dd EXIT_SYMBOL_HANDLER
        db 'PROMPT_SYMBOL', 0x00
        dd PROMPT_SYMBOL_HANDLER
        db 'INPUT_SYMBOL', 0x00
        dd INPUT_SYMBOL_HANDLER
        db 'SLEEP_SYMBOL', 0x00
        dd SLEEP_SYMBOL_HANDLER
        db 'HTTP_SYMBOL', 0x00
        dd HTTP_SYMBOL_HANDLER
        db 'PROXY_SYMBOL', 0x00
        dd PROXY_SYMBOL_HANDLER
        db 'USER_AGENT_SYMBOL', 0x00
        dd USER_AGENT_SYMBOL_HANDLER
        db 'SERVER_SYMBOL', 0x00
        dd SERVER_SYMBOL_HANDLER
        db 'WAIT_SYMBOL', 0x00
        dd WAIT_SYMBOL_HANDLER
        db 'NULL_SYMBOL', 0x00
        dd NULL_SYMBOL_HANDLER
        db 'PRINT_SYMBOL', 0x00
        dd PRINT_SYMBOL_HANDLER
        db 'SYS_CALL_SYMBOL', 0x00
        dd SYS_CALL_SYMBOL_HANDLER
        db 'FUNCTION_SYMBOL', 0x00
        dd FUNCTION_SYMBOL_HANDLER
        db 'MOVE_SYMBOL', 0x00
        dd MOVE_SYMBOL_HANDLER
        db 'ATTRIBUTE_SYMBOL', 0x00
        dd ATTRIBUTE_SYMBOL_HANDLER
        db 'PATH_SYMBOL', 0x00
        dd PATH_SYMBOL_HANDLER
        db 'TYPE_SYMBOL', 0x00
        dd TYPE_SYMBOL_HANDLER
        db 'CHAR_SYMBOL', 0x00
        dd CHAR_SYMBOL_HANDLER
        db 'READ_SYMBOL', 0x00
        dd READ_SYMBOL_HANDLER


section .text
global INIT_SYMBOL_MODULE
global ADD_SYMBOL_HANDLER, SUB_SYMBOL_HANDLER, MUL_SYMBOL_HANDLER, DIV_SYMBOL_HANDLER
global GT_SYMBOL_HANDLER, LT_SYMBOL_HANDLER, EQ_SYMBOL_HANDLER, DNE_SYMBOL_HANDLER
global GTE_SYMBOL_HANDLER, LTE_SYMBOL_HANDLER, WHILE_SYMBOL_HANDLER, FOR_SYMBOL_HANDLER
global EXCEPT_SYMBOL_HANDLER, BREAK_SYMBOL_HANDLER, STR_SYMBOL_HANDLER, COUNT_SYMBOL_HANDLER
global BOOL_SYMBOL_HANDLER, END_SYMBOL_HANDLER, ECHO_SYMBOL_HANDLER, DONE_SYMBOL_HANDLER
global EXIT_SYMBOL_HANDLER, PROMPT_SYMBOL_HANDLER, INPUT_SYMBOL_HANDLER, SLEEP_SYMBOL_HANDLER
global HTTP_SYMBOL_HANDLER, PROXY_SYMBOL_HANDLER, USER_AGENT_SYMBOL_HANDLER, SERVER_SYMBOL_HANDLER
global WAIT_SYMBOL_HANDLER, NULL_SYMBOL_HANDLER, PRINT_SYMBOL_HANDLER, SYS_CALL_SYMBOL_HANDLER
global FUNCTION_SYMBOL_HANDLER, MOVE_SYMBOL_HANDLER, ATTRIBUTE_SYMBOL_HANDLER, PATH_SYMBOL_HANDLER
global TYPE_SYMBOL_HANDLER, CHAR_SYMBOL_HANDLER, READ_SYMBOL_HANDLER


INIT_SYMBOL_MODULE:
    ; Initialize the Symbol Module
    ; Register commands with the main system's command table
    mov esi, SYMBOL_COMMANDS  ; Start of the symbol commands in module
    call register_commands    ; Routine to add commands to the command table

    ; Additional initialization as needed
    re

; Handler Functions for Commands
section .text
global ADD_SYMBOL_HANDLER

ADD_SYMBOL_HANDLER:
    ; Example: Adding two numbers stored in registers R1 and R2
    ; and storing the result in register R0
    ; Load the operands (assuming R1 and R2 are set up with the operands)
    mov eax, [R1]   ; Load the first operand into EAX
    add eax,  [R2]  ; ; EAX = EAX + second operand
    ; Perform the addition
    ; Store the result in R0 (or any desired location)
    mov [R0], eax   ; Store the result back in R0
    ; Return to the caller
    ret
; Example: Adding two numbers stored in registers R1 and R2
; and storing the result in register R0

SUB_SYMBOL_HANDLER:
    mov eax, [R1]   ; Load the first operand into EAX
    sub eax, [R2]   ; Subtract the second operand
    mov [R0], eax   ; Store the result in R0
    ret

MUL_SYMBOL_HANDLER:
    mov eax, [R1]   ; Load the first operand into EAX
    imul eax, [R2]  ; Multiply with the second operand
    mov [R0], eax   ; Store the result in R0
    ret

DIV_SYMBOL_HANDLER:
    mov eax, [R1]   ; Load the dividend into EAX
    xor edx, edx    ; Clear the high bits of EDX for unsigned division
    div dword [R2]  ; Divide EAX by the operand in R2
    mov [R0], eax   ; Store the quotient in R0
    ret

GT_SYMBOL_HANDLER:
    mov eax, [R1]   ; Load the first operand into EAX
    cmp eax, [R2]   ; Compare with the second operand
    setg al         ; Set AL to 1 if greater, otherwise 0
    movzx eax, al   ; Zero-extend AL to EAX
    mov [R0], eax   ; Store the result in R0
    ret

LT_SYMBOL_HANDLER:
    mov eax, [R1]
    cmp eax, [R2]
    setl al
    movzx eax, al
    mov [R0], eax
    ret

EQ_SYMBOL_HANDLER:
    mov eax, [R1]
    cmp eax, [R2]
    sete al
    movzx eax, al
    mov [R0], eax
    ret

DNE_SYMBOL_HANDLER:
    mov eax, [R1]
    cmp eax, [R2]
    setne al
    movzx eax, al
    mov [R0], eax
    ret

GTE_SYMBOL_HANDLER:
    mov eax, [R1]
    cmp eax, [R2]
    setge al
    movzx eax, al
    mov [R0], eax
    ret

LTE_SYMBOL_HANDLER:
    mov eax, [R1]
    cmp eax, [R2]
    setle al
    movzx eax, al
    mov [R0], eax
    ret

WHILE_SYMBOL_HANDLER:
    ; Example: simple loop checking a condition
    ; (Assuming R1 holds the address of a condition check function)
    call [R1]       ; Call the condition check function
    test eax, eax   ; Test the result
    jz end_while    ; If zero (false), exit loop
    ; Loop body code goes here
    jmp WHILE_SYMBOL_HANDLER ; Repeat loop
end_while:
    ret

FOR_SYMBOL_HANDLER:
    ; Example: A simple counter loop (Assume R1=start, R2=end, R3=step)
    mov ecx, [R1]   ; Initialize counter
for_loop:
    cmp ecx, [R2]   ; Check if end is reached
    jge end_for
    ; Loop body code goes here
    add ecx, [R3]   ; Increment counter
    jmp for_loop
end_for:
    ret

EXCEPT_SYMBOL_HANDLER:
    ; Assuming it's about excluding a value, we perform subtraction
    mov eax, [R1]    ; Load the first operand into EAX
    sub eax, [R2]    ; Subtract the second operand from EAX
    mov [R0], eax    ; Store the result in R0
    ret

BREAK_SYMBOL_HANDLER:
    mov eax, 1       ; Set a flag or status to indicate a break
    mov [R0], eax    ; Store the status in R0
    ret

STR_SYMBOL_HANDLER:
    ; Placeholder for string operation, e.g., concatenation
    ; Assuming R1 and R2 point to strings, and R0 is the destination
    ; Actual string concatenation requires a loop to copy bytes
    ; This is just a simplified placeholder
    mov esi, [R1]    ; Load the address of the first string into ESI
    mov edi, [R0]    ; Load the destination address into EDI
    cld              ; Clear direction flag for forward movement
    rep movsb        ; Copy first string
    mov esi, [R2]    ; Load the address of the second string
    rep movsb        ; Copy second string
    ret

COUNT:
    mov eax, [R1]    ; Load the address of the data to count
    xor ecx, ecx     ; Clear counter
count_loop:
    cmp byte [eax], 0 ; Check if the current byte is null terminator
    je count_done     ; Exit loop if end of string/data
    inc ecx          ; Increment count
    inc eax          ; Move to the next byte
    jmp count_loop
count_done:
    mov [R0], ecx    ; Store the count in R0
    ret

BOOL:
    mov eax, [R1]    ; Load value into EAX
    test eax, eax    ; Perform logical test
    setnz al         ; Set AL to 1 if non-zero (true), 0 if zero (false)
    movzx eax, al    ; Zero-extend AL to EAX
    mov [R0], eax    ; Store the boolean result in R0
    ret

END:
    mov eax, 0       ; Set a code or flag for ending
    mov [R0], eax    ; Store this in R0 as an indicator
    ret

DONE:
    mov eax, 1       ; Set a flag indicating done or completion
    mov [R0], eax    ; Store this in R0
    ret

EXIT:
    mov eax, 0       ; Set an exit code
    mov [R0], eax    ; Store the exit code in R0
    ; Here you might actually use a system call to exit if in real mode
    ret

PROMPT:
    ; Placeholder for showing a prompt to the user
    call show_prompt ; Assume show_prompt is a subroutine
    ret

INPUT:
    ; Placeholder for reading user input
    call read_input  ; Assume read_input is a subroutine that stores input in R0
    ret

SLEEP:
    mov eax, [R1]    ; Load the sleep duration into EAX
    call sleep_routine ; Call a sleep routine
    ret

HTTP:
    ; Placeholder for HTTP operation
    call http_request ; Assume http_request handles HTTP operations
    ret

PROXY:
    ; Placeholder for proxy setting
    call set_proxy ; Assume set_proxy is a subroutine for proxy settings
    ret

USER_AGENT:
    ; Placeholder for setting user agent
    call set_user_agent ; Assume set_user_agent is a subroutine
    ret

SERVER:
    ; Placeholder for server control
    call start_server ; Assume start_server handles server operations
    ret

WAIT:
    mov eax, [R1]    ; Load wait time or condition into EAX
    call wait_routine ; Call a wait routine
    ret

NULL:
    xor eax, eax     ; Clear EAX
    mov [R0], eax    ; Store zero in R0
    ret

PRINT:
    mov eax, [R1]    ; Load address of the string to print
    call print_string ; Assume print_string prints a null-terminated string
    ret

SYS_CALL:
    mov eax, [R1]    ; Load system call number or code
    int 0x80         ; Interrupt for system call (for Linux x86)
    mov [R0], eax    ; Store the result in R0
    ret

FUNCTION:
    call [R1]        ; Call function at address in R1
    ret

ECHO:
    mov eax, [R1]    ; Load value to be echoed
    call print_value ; Assume print_value prints the value in EAX
    ret

DONE:
    mov eax, 1       ; Indicate completion
    mov [R0], eax    ; Store in R0
    ret

EXIT:

MOVE:
    mov eax, [R1]    ; Load source data
    mov [R2], eax    ; Store to destination
    ret

ATTRIBUTE:
    ; Placeholder for attribute modification
    call set_attribute ; Assume set_attribute modifies an attribute
    ret

PATH:
    ; Placeholder for path handling
    call set_path ; Assume set_path modifies or handles paths
    ret

TYPE:
    ; Placeholder for type operations
    mov eax, [R1]    ; Load data to check type
    call check_type  ; Assume check_type determines the type
    ret

CHAR:
    ; Placeholder for character handling
    mov eax, [R1]    ; Load character
    call handle_char ; Assume handle_char processes the character
    ret

READ:
    ; Placeholder for reading data
    call read_data   ; Assume read_data handles data reading
    ret

; Define other handlers as needed...

; Handle missing commands or errors
error_command_not_found:
    ; Handle an unknown command
    ret
