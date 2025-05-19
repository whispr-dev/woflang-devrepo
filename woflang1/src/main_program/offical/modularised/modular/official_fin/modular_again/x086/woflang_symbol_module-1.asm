section .data
    ; Command to function handler mapping
    command_table:
        db '齊', 0       ; ADD Command
        dd add_handler   ; Address of ADD handler routine

        db '隶', 0       ; SUBTRACT Command
        dd sub_handler   ; Address of SUB handler routine

        db '丶', 0       ; MULTIPLY Command
        dd mul_handler   ; Address of MUL handler routine

        db '丿', 0       ; DIVIDE Command
        dd div_handler   ; Address of DIV handler routine

        db ''大', 0     ; GREATER Command
        dd gt_handler   ; address of GT handler routine
        
        db '小', 0      ; LESS Command
        dd LT_handler   ;  address of LT handler routine

        db '卜', 0       ; EQUALS Command
        dd EQ_handler   ; Address of EQUALS handler routine

        db '丨', 0       ; DOES NOT EQUAL Command
        dd DNE_handler   ; Address of DNE handler routine

        db '走', 0       ; GREATER THAN OR EQUALS Command
        dd GTE_handler   ; Address of GTE handler routine

        db '夊', 0       ; LESS THAN OR EQUALSCommand
        dd LTE_handler   ; Address of LTE handler routine

        db '老', 0            ; WHILE (老)Command
        dd WHILE_handler   ; Address of Loop handler routine

        db '至', 0            ; FOR (至)Command
        dd FOR_handler    ; Address of FOR handler routine

        db '舛', 0            ; EXCEPT (舛)Command
        dd EXCEPT_handler;  Address of Except handler routine

        db '止', 0            ; BREAK (止)Command
        dd BREAK_handler     ; Address of  Break  handler routine

        db '己', 0            ; STRING (己)Command
        dd STR_handler   ; Address of  String  handler routine

        db '支', 0            ; COUNT (支)Command
        dd COUNT_handler ; Address of  Count  handler routine

        db '比', 0            ; BOOLEAN (比)Command
        dd BOOL_handler   ; Address of  Boolean  handler routine

        db '終', 0            ; END (終)Command
        dd END_handler    ; Address of  End  handler routine

        db '響', 0            ; ECHO (響)Command
        dd ECHO_handler ; Address of  Echo  handler routine

        db '釆', 0            ; DONE (釆)Command
        dd DONE_handler    ; Address of  Done  handler routine

        db '卩', 0            ; EXIT (卩)Command
        dd EXIT_handler    ; Address of  Exit  handler routine

        db '押', 0            ; PROMPT (押)Command
        dd PROMPT_handler    ; Address of  Prompt  handler routine

        db '⽰', 0            ; INPUT (⽰)Command
        dd INPUT_handler  ; Address of  Input  handler routine

        db '眠', 0            ; SLEEP (眠)Command
        dd SLEEP_handler   ; Address of  Sleep  handler routine

        db '⺒', 0            ; HTTP (⺒)Command
        dd HTTP_handler   ; Address of  HTTP  handler routine

        db '⺨', 0            ; PROXY (⺨)Command
        dd PROXY_handler    ; Address of  Proxy  handler routine

        db '⽪', 0            ; USER_AGENT (⽪)Command
        dd USER_AGENT_handler   ; Address of  User Agent  handler routine

        db '⽓', 0            ; SERVER (⽓)Command
        dd SERVER_handler  ; Address of  Server  handler routine

        db '待', 0            ; WAIT (待)Command
        dd WAIT_handler  ; Address of  Wait  handler routine

        db '⻤', 0            ; NULL (⻤)Command
        dd NULL_handler    ; Address of  Null  handler routine

        db '⺙', 0            ; PRINT (⺙)Command
        dd PRINT_handler    ; Address of  Print  handler routine

        db '⺆', 0            ; SYS_CALL (⺆)Command
        dd SYS_CALL_handler   ; Address of  System Call  handler routine

        db '⺘', 0            ;(⺘)Command
        dd FUNCTION_handler    ; Address of  Function Call  handler routine

        db '工', 0            ; MOVE (工)Command
        dd MOVE_handler    ; Address of  Move  handler routine

        db '⺣', 0            ;ATTRIBUTE (⺣)Command
        dd ATTRIBUTE_handler    ; Address of  Attribute  handler routine

        db '道', 0            ; PATH (道)Command
        dd PATH_handler   ; Address of  Path  handler routine

        db '⺢', 0            ; TYPE (⺢)Command
        dd TYPE_handler    ; Address of  Type  handler routine

        db '字', 0            ; CHAR (字)Command
        dd CHAR_handler    ; Address of  Character  handler routine

        db '読', 0            ; READ (読)Command
        dd READ_handler    ; Address of  Read  handler routine 

        MAIN_EXECUTION:
    ; Initialize the command pointer
    mov esi, command_table

command_lookup_loop:
    ; Load command from the table
    lodsb                      ; Load command byte into AL
    test al, al                ; Check for null terminator
    jz command_not_found       ; If null, command not found

    ; Compare the input command with the current table entry
    cmp al, [R0]
    jne command_next           ; If not equal, continue to next

    ; Load the function handler address
    lodsd                      ; Load the handler address into EAX
    call eax                   ; Call the function handler
    jmp command_executed       ; Command found and executed

command_next:
    add esi, 4                 ; Move to the next command entry
    jmp command_lookup_loop    ; Loop to check the next command

command_not_found:
    ; Handle case when command is not found
    ; Error routine or default action
    call error_command_not_found
    jmp command_end

command_executed:
    ; Handle successful command execution
    ; Continue to next command or exit
    jmp command_end

command_end:
    ; End of command processing loop
    ; Loop back to read the next command or exit
    jmp MAIN_EXECUTION
