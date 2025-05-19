section .data
    ; Module Header Information
    MODULE_NAME      db 'woflangSymbolModule', 0x00
    MODULE_VERSION   db 'v0.0.4', 0x00
    MODULE_INIT_FUNC equ INIT_SYMBOL_MODULE
    http_request_format db 'GET / HTTP/1.1', 0x0D, 0x0A, 'Host: ', 0x00 ; Placeholder for host name
    response_buffer resb 1024       ; Buffer for storing server response
    http_post_format db 'POST / HTTP/1.1', 0x0D, 0x0A, 'Host: ', 0x00 ; Placeholder for host name
    post_content_type db 'Content-Type: application/x-www-form-urlencoded', 0x0D, 0x0A
    post_content_length db 'Content-Length: ', 0x00
    post_data db 'key1=value1&key2=value2', 0x0D, 0x0A, 0x00 ; Placeholder for actual POST data
    response_buffer resb 1024       ; Buffer for storing server response
  ; Example Constants or Buffers for Arithmetic
    some_float_constant dq 1.2345678901234567
    ; Define the file path to be modified
    file_path db 'C:\example.txt', 0x00  ; Null-terminated string for DOS
    port db 8080               ; Port number to listen on (example: 8080)
    backlog db 5               ; Number of allowed pending connections (backlog)
    ip_address db 0            ; Use 0.0.0.0 for INADDR_ANY
    socket_fd dd 0             ; File descriptor for the server socket
    proxy_env_prefix db 'export ', 0x00                ; Command prefix for setting environment variable
    http_proxy_var db 'http_proxy=', 0x00              ; Environment variable name for HTTP proxy
    https_proxy_var db 'https_proxy=', 0x00            ; Environment variable name for HTTPS proxy
    new_line db 0x0A                                   ; Newline character

    ; Character Map or List
    CHARACTER_MAP:
        ; db 'A', 'B', 'C', 'D', 0x00  ; Example map
; logic
        db '而', 0        ; AND Command
        db '或', 0        ; OR Command
        db '⊕', 0         ; XOR Command
        db '无', 0        ; NOT Command
        db '无‍而', 0     ; NAND Command
        db '无‍或', 0     ; NOR Command
        db '若', 0        ; IF Command
        db '则', 0        ; THEN Command
        db '?', 0         ; ELSE Command

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

; simd vetors and matices
        db '⼉', 0      ; vect_add
        db '⼐', 0      ; vect_sub
        db '⼝' 0	    ; dot_prod
        db '⼍', 0		; matrix_det
        db '⼹' 0		; matrix_inv
        db '⼺', 0		; 3x3_det
        db'⽇', 0

section.bss
    socket_fd resd 1                ; File descriptor for the socket

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
        db 'AND_SYMBOL', 0x00
        dd AND_SYMBOL_HANDLER
        db 'OR_SYMBOL', 0x00
        dd OR_SYMBOL_HANDLER
        db 'XOR_SYMBOL', 0x00
        dd XOR_SYMBOL_HANDLER
        db 'NOT_SYMBOL', 0x00
        dd NOT_SYMBOL_HANDLER
        db 'NAND_SYMBOL', 0x00
        dd NAND_SYMBOL_HANDLER
        db 'NOR_SYMBOL', 0x00
        dd NOR_SYMBOL_HANDLER
        db 'IF_SYMBOL', 0x00
        dd IF_SYMBOL_HANDLER
        db 'THEN_SYMBOL', 0x00
        dd THEN_SYMBOL_HANDLER
        db 'ELSE_SYMBOL', 0x00
        dd ELSE_SYMBOL_HANDLER
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
        db 'VECT_ADD_SYMBOL
        dd VECT_ADD_SYMBOL HANDLER
        db 'VECT_SUB_SYMBOL', 0x00
        dd VECT_SUB_SYMBOL_HANDLER
        db 'DOT_PROD_SYMBOL', 0x00
        dd  DOT_PROD_SYMBOL_HANDLER
        db 'MATRIX_DET_SYMBOL', 0x00
        dd  MATRIX_DET_SYMBOL_HANDLER
        db 'MATRIX_INV_SYMBOL', 0x00
        dd MATRIX_INV_SYMBOL_HANDLER
        db '3X3_DET_SYMBOL', 0x00
        dd 3X3_DET_SYMBOL_HANDLER

section .text
global INIT_SYMBOL_MODULE   ; init main symbol ref and defs
global ADD_SYMBOL_HANDLER, SUB_SYMBOL_HANDLER, MUL_SYMBOL_HANDLER, DIV_SYMBOL_HANDLER   ; core arithmetic
global AND_ROUTINE, OR_ROUTINE, XOR_ROUTINE, NOT_ROUTINE    ; core logic
global NAND_ROUTINE, NOR_ROUTINE, IF_ROUTINE, THEN_ROUTINE, ELSE_ROUTINE    ; basic logic
; global LOGIC_HANDLER    
global GT_SYMBOL_HANDLER, LT_SYMBOL_HANDLER, EQ_SYMBOL_HANDLER, DNE_SYMBOL_HANDLER  ; basic arithmetic
global GTE_SYMBOL_HANDLER, LTE_SYMBOL_HANDLER, WHILE_SYMBOL_HANDLER, FOR_SYMBOL_HANDLER ; logic 1
global EXCEPT_SYMBOL_HANDLER, BREAK_SYMBOL_HANDLER, STR_SYMBOL_HANDLER, COUNT_SYMBOL_HANDLER    ; logic 2
global BOOL_SYMBOL_HANDLER, END_SYMBOL_HANDLER, ECHO_SYMBOL_HANDLER, DONE_SYMBOL_HANDLER    ; commands 1
global EXIT_SYMBOL_HANDLER, PROMPT_SYMBOL_HANDLER, INPUT_SYMBOL_HANDLER, SLEEP_SYMBOL_HANDLER   ; cmmands 2
global HTTP_SYMBOL_HANDLER, PROXY_SYMBOL_HANDLER, USER_AGENT_SYMBOL_HANDLER, SERVER_SYMBOL_HANDLER  ; interwebs
global WAIT_SYMBOL_HANDLER, NULL_SYMBOL_HANDLER, PRINT_SYMBOL_HANDLER, SYS_CALL_SYMBOL_HANDLER  ; memory 1
global FUNCTION_SYMBOL_HANDLER, MOVE_SYMBOL_HANDLER, ATTRIBUTE_SYMBOL_HANDLER, PATH_SYMBOL_HANDLER  ; misc 1
global TYPE_SYMBOL_HANDLER, CHAR_SYMBOL_HANDLER, READ_SYMBOL_HANDLER    ; misc 2
global VECT_ADD_SYMBOL,  VECT_SUB_SYMBOL, DOT_PROD_SYMBOL, MATRIX_INV_SYMBOL, 3X3_DET_SYMBOL    ; vector math  & matrices
global http_get_request, http_post_request, start_server_routine, stop_server_routine ; interwebs 2
global set_attribute_value, set_proxy_server    ; interwebs 3

; Initialize Symbol Module
INIT_SYMBOL_MODULE:
    mov esi, SYMBOL_COMMANDS  ; Load address of command mappings - start of the symbol commands in module
    call register_commands    ; Routine to add commands to the command table - registers commands with the main system
    ret
  
; Handler Functions for Commands
; ADD_SYMBOL_HANDLER
ADD_SYMBOL_HANDLER:
    ; Example: Adding two double-precision numbers stored in xmm0 and xmm1
    addsd xmm0, xmm1        ; xmm0 = xmm0 + xmm1
    ret

; SUB_SYMBOL_HANDLER
SUB_SYMBOL_HANDLER:
    ; Example: Subtracting two double-precision numbers stored in xmm0 and xmm1
    subsd xmm0, xmm1        ; xmm0 = xmm0 - xmm1
    ret

MUL_SYMBOL_HANDLER:
    mov eax, [R1]
    imul eax, [R2]
    mov [R0], eax
    ret

DIV_SYMBOL_HANDLER:
    mov eax, [R1]
    xor edx, edx
    div dword [R2]
    mov [R0], eax
    ret

GT_SYMBOL_HANDLER:
    mov eax, [R1]
    cmp eax, [R2]
    setg al
    movzx eax, al
    mov [R0], eax

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

AND_ROUTINE:
    mov eax, edx
    and eax, ecx
    ret

OR_ROUTINE:
    mov eax, edx
    or eax, ecx
    ret

XOR_ROUTINE:
    mov eax, edx
    xor eax, ecx
    ret

NOT_ROUTINE:
    mov eax, edx
    not eax
    ret

NAND_ROUTINE:
    mov eax, edx
    and eax, ecx
    not eax
    ret

NOR_ROUTINE:
    mov eax, edx
    or eax, ecx
    not eax
    ret

IF_ROUTINE:
    test edx, edx
    jz .if_false
    mov eax, ecx
    jmp .end_if
.if_false:
    mov eax, ebx
.end_if:
    ret

; THEN_ROUTINE: Executes logic if the condition is true
THEN_ROUTINE:
    ; Example logic for the THEN block
    ; Assumes eax has been set with the condition result
    cmp eax, 0              ; Compare eax with 0
    je else_skip            ; If zero (false), skip to ELSE_ROUTINE

    ; Logic for THEN block (executed when condition is true)
    ; Add your specific code here
    mov edx, 1              ; Example: Set edx to 1 to indicate true condition
    ; Perform operations for the true condition
    ; ...
    
    jmp end_then_else       ; Skip ELSE block after executing THEN logic

else_skip:                  ; Label to skip to ELSE_ROUTINE if condition is false
    call ELSE_ROUTINE       ; Call ELSE_ROUTINE if condition is false

end_then_else:
    ret

; ELSE_ROUTINE: Executes logic if the condition is false
ELSE_ROUTINE:
    ; Logic for ELSE block (executed when condition is false)
    ; Add your specific code here
    mov edx, 0              ; Example: Set edx to 0 to indicate false condition
    ; Perform operations for the false condition
    ; ...

    ret

END_LOGIC_HANDLER:
    mov dword [MEM + 201], eax ; Store the result of the logic operation
    ret                        ; Return to main execution

ADD_LOGIC_ERR_ROUTINE:
    ; Handle unexpected or invalid logic commands
    ; Could set an error flag, log an error, or return a default value
    ret

WHILE_SYMBOL_HANDLER:
    call [R1]
    test eax, eax
    jz end_while
    jmp WHILE_SYMBOL_HANDLER
end_while:
    ret

FOR_SYMBOL_HANDLER:
    mov ecx, [R1]
for_loop:
    cmp ecx, [R2]
    jge end_for
    add ecx, [R3]
    jmp for_loop
end_for:
    ret

EXCEPT_SYMBOL_HANDLER:
    mov eax, [R1]
    sub eax, [R2]
    mov [R0], eax
    ret

BREAK_SYMBOL_HANDLER:
    mov eax, 1
    mov [R0], eax
    ret

STR_SYMBOL_HANDLER:
    mov esi, [R1]
    mov edi, [R0]
    cld
    rep movsb
    mov esi, [R2]
    rep movsb
    ret

COUNT_SYMBOL_HANDLER:
    mov eax, [R1]
    xor ecx, ecx
count_loop:
    cmp byte [eax], 0
    je count_done
    inc ecx
    inc eax
    jmp count_loop
count_done:
    mov [R0], ecx
    ret

BOOL_SYMBOL_HANDLER:
    mov eax, [R1]
    test eax, eax
    setnz al
    movzx eax, al
    mov [R0], eax
    ret

END_SYMBOL_HANDLER:
    xor eax, eax
    mov [R0], eax
    ret

DONE_SYMBOL_HANDLER:
    mov eax, 1
    mov [R0], eax
    ret

EXIT_SYMBOL_HANDLER:
    mov eax, 0
    mov [R0], eax
    ret

PROMPT_SYMBOL_HANDLER:
    call show_prompt
    ret

INPUT_SYMBOL_HANDLER:
    call read_input
    ret

SLEEP_SYMBOL_HANDLER:
    mov eax, [R1]
    call sleep_routine
    ret

WAIT_SYMBOL_HANDLER:
    mov eax, [R1]
    call wait_routine
    ret

NULL_SYMBOL_HANDLER:
    xor eax, eax
    mov [R0], eax
    ret

PRINT_SYMBOL_HANDLER:
    mov eax, [R1]
    call print_string
    ret

SYS_CALL_SYMBOL_HANDLER:
    mov eax, [R1]
    int 0x80
    mov [R0], eax
    ret

FUNCTION_SYMBOL_HANDLER:
    call [R1]
    ret

ECHO_SYMBOL_HANDLER:
    mov eax, [R1]
    call print_value
    ret

MOVE_SYMBOL_HANDLER:
    mov eax, [R1]
    mov [R2], eax
    ret

TYPE_SYMBOL_HANDLER:
    mov eax, [R1]
    call check_type
    ret

CHAR_SYMBOL_HANDLER:
    mov eax, [R1]
    call handle_char
    ret

READ_SYMBOL_HANDLER:
    call read_data
    ret

HTTP_SYMBOL_HANDLER:
    ; Assume that R1 holds the URL, R2 holds the method (GET/POST), and R3 holds the data for POST
    ; This example uses a simplified approach and doesn't include full HTTP protocol handling.
    
    ; Set up HTTP request (simplified example, not a real HTTP implementation)
    push eax                 ; Preserve register state
    push ebx
    push ecx
    push edx

    mov eax, [R1]            ; Load URL into EAX
    mov ebx, [R2]            ; Load HTTP method into EBX
    cmp ebx, 'GET'           ; Check if method is GET
    jne .check_post          ; If not GET, check for POST

    ; HTTP GET request routine
    call http_get_request    ; Call a function to perform a GET request
    jmp .done                ; Skip POST handling

.check_post:
    cmp ebx, 'POST'          ; Check if method is POST
    jne .done                ; If not POST, end (for now, only handle GET/POST)
    
    ; HTTP POST request routine
    mov ecx, [R3]            ; Load POST data into ECX
    call http_post_request   ; Call a function to perform a POST request

.done:
    pop edx                  ; Restore register state
    pop ecx
    pop ebx
    pop eax
    ret

http_get_request:
    ; Arguments:
    ; R1: Pointer to server address
    ; R2: Pointer to port number
    ; R3: Pointer to the path (optional, default to "/")
    
    ; Step 1: Create a socket
    mov eax, 1            ; sys_socketcall
    mov ebx, 1            ; sys_socketcall - SYS_SOCKET
    mov ecx, 0x00000201   ; AF_INET, SOCK_STREAM
    int 0x80              ; Interrupt for system call
    test eax, eax
    js socket_error
    mov [socket_fd], eax  ; Save socket descriptor
    
    ; Step 2: Connect to the server
    mov ecx, esp          ; Allocate memory for sockaddr_in
    sub esp, 16           ; sockaddr_in is 16 bytes
    xor edx, edx
    mov word [ecx], 0x0002 ; AF_INET (IPv4)
    mov ax, [R2]          ; Load port number into AX
    xchg ax, [ecx + 2]    ; Set port in sockaddr_in
    mov eax, [R1]         ; Server IP address (big-endian)
    mov [ecx + 4], eax    ; Set IP address in sockaddr_in

    mov eax, 1            ; sys_socketcall
    mov ebx, 3            ; sys_socketcall - SYS_CONNECT
    mov ecx, [socket_fd]  ; Load socket descriptor
    int 0x80              ; Make the system call
    test eax, eax
    js connect_error
    
    ; Step 3: Send the HTTP GET request
    push dword '1.1 '     ; Push "1.1 " (little-endian for "1.1 ")
    push dword '/ HTTP/'  ; Push "/ HTTP/"
    push dword 'T GE'     ; Push "GET "
    mov esi, esp          ; Pointer to "GET / HTTP/1.1 "
    mov edi, http_request_format + 7
    mov ecx, 12
    rep movsb             ; Copy the GET request format
    
    mov eax, 1            ; sys_socketcall
    mov ebx, 4            ; sys_socketcall - SYS_SEND
    mov ecx, [socket_fd]  ; Load socket descriptor
    mov edx, http_request_format ; Load pointer to the request
    mov esi, 17           ; Request length (strlen("GET / HTTP/1.1") + CRLF)
    int 0x80              ; Make the system call
    test eax, eax
    js send_error
    
    ; Step 4: Receive the response
    mov eax, 1            ; sys_socketcall
    mov ebx, 5            ; sys_socketcall - SYS_RECV
    mov ecx, [socket_fd]  ; Load socket descriptor
    mov edx, response_buffer ; Buffer to store the response
    mov esi, 1024         ; Max response length
    int 0x80              ; Make the system call
    test eax, eax
    js recv_error
    
    ; Step 5: Clean up and exit
    mov eax, 1            ; sys_exit
    xor ebx, ebx          ; Exit code 0
    int 0x80              ; Exit system call

socket_error:
    ; Handle socket creation error
    mov eax, 1            ; sys_exit
    mov ebx, 1            ; Exit code 1
    int 0x80

connect_error:
    ; Handle connection error
    mov eax, 1            ; sys_exit
    mov ebx, 2            ; Exit code 2
    int 0x80

send_error:
    ; Handle send error
    mov eax, 1            ; sys_exit
    mov ebx, 3            ; Exit code 3
    int 0x80

recv_error:
    ; Handle receive error
    mov eax, 1            ; sys_exit
    mov ebx, 4            ; Exit code 4
    int 0x80

http_post_request:
    ; Arguments:
    ; R1: Pointer to server address
    ; R2: Pointer to port number
    ; R3: Pointer to POST data
    
    ; Step 1: Create a socket
    mov eax, 1            ; sys_socketcall
    mov ebx, 1            ; sys_socketcall - SYS_SOCKET
    mov ecx, 0x00000201   ; AF_INET, SOCK_STREAM
    int 0x80              ; Interrupt for system call
    test eax, eax
    js socket_error
    mov [socket_fd], eax  ; Save socket descriptor
    
    ; Step 2: Connect to the server
    mov ecx, esp          ; Allocate memory for sockaddr_in
    sub esp, 16           ; sockaddr_in is 16 bytes
    xor edx, edx
    mov word [ecx], 0x0002 ; AF_INET (IPv4)
    mov ax, [R2]          ; Load port number into AX
    xchg ax, [ecx + 2]    ; Set port in sockaddr_in
    mov eax, [R1]         ; Server IP address (big-endian)
    mov [ecx + 4], eax    ; Set IP address in sockaddr_in

    mov eax, 1            ; sys_socketcall
    mov ebx, 3            ; sys_socketcall - SYS_CONNECT
    mov ecx, [socket_fd]  ; Load socket descriptor
    int 0x80              ; Make the system call
    test eax, eax
    js connect_error
    
    ; Step 3: Send the HTTP POST request
    push dword '1.1 '     ; Push "1.1 " (little-endian for "1.1 ")
    push dword '/ HTTP/'  ; Push "/ HTTP/"
    push dword 'T SOP'    ; Push "POST "
    mov esi, esp          ; Pointer to "POST / HTTP/1.1 "
    mov edi, http_post_format + 8
    mov ecx, 12
    rep movsb             ; Copy the POST request format
    
    mov eax, 1            ; sys_socketcall
    mov ebx, 4            ; sys_socketcall - SYS_SEND
    mov ecx, [socket_fd]  ; Load socket descriptor
    mov edx, http_post_format ; Load pointer to the request
    mov esi, 47           ; Request length (strlen("POST / HTTP/1.1") + CRLF + headers)
    int 0x80              ; Make the system call
    test eax, eax
    js send_error
    
    ; Send POST data
    mov eax, 1            ; sys_socketcall
    mov ebx, 4            ; sys_socketcall - SYS_SEND
    mov ecx, [socket_fd]  ; Load socket descriptor
    mov edx, R3           ; Load pointer to the POST data
    mov esi, [R3 + 8]     ; Data length (assuming it's stored at [R3 + 8])
    int 0x80              ; Make the system call
    test eax, eax
    js send_error
    
    ; Step 4: Receive the response
    mov eax, 1            ; sys_socketcall
    mov ebx, 5            ; sys_socketcall - SYS_RECV
    mov ecx, [socket_fd]  ; Load socket descriptor
    mov edx, response_buffer ; Buffer to store the response
    mov esi, 1024         ; Max response length
    int 0x80              ; Make the system call
    test eax, eax
    js recv_error
    
    ; Step 5: Clean up and exit
    mov eax, 1            ; sys_exit
    xor ebx, ebx          ; Exit code 0
    int 0x80              ; Exit system call

socket_error:
    ; Handle socket creation error
    mov eax, 1            ; sys_exit
    mov ebx, 1            ; Exit code 1
    int 0x80

connect_error:
    ; Handle connection error
    mov eax, 1            ; sys_exit
    mov ebx, 2            ; Exit code 2
    int 0x80

send_error:
    ; Handle send error
    mov eax, 1            ; sys_exit
    mov ebx, 3            ; Exit code 3
    int 0x80

recv_error:
    ; Handle receive error
    mov eax, 1            ; sys_exit
    mov ebx, 4            ; Exit code 4
    int 0x80

PROXY_SYMBOL_HANDLER:

set_proxy_server:
    ; Arguments:
    ; R1: Pointer to proxy server address (e.g., "http://proxy.example.com:8080")
    ; R2: Pointer to proxy type (e.g., "http" or "https")

    ; Assume that R1 holds the proxy server address (e.g., "proxy.example.com") 
    ; and R2 holds the port number.

    ; PReserve register data
    push eax                 ; Preserve register state
    push ebx
    push ecx

    ; Step 1: Prepare the proxy environment variable command
    mov esi, proxy_env_prefix          ; Load the export command prefix
    mov edi, environment_buffer        ; Load destination buffer for the environment command
    call copy_string                   ; Copy "export " to the buffer

    ; Step 2: Check proxy type (http or https)
    mov esi, [R2]                      ; Load the proxy type string into ESI
    mov edi, environment_buffer        ; Destination buffer to append the variable name
    add edi, 7                         ; Skip past "export "
    call compare_http_https            ; Check if type is "http" or "https"
    jz set_http_proxy                  ; Jump if type is "http"
    cmp esi, 'https'                   ; Compare with "https"
    jz set_https_proxy                 ; Jump if type is "https"
    jmp invalid_proxy_type             ; If neither, jump to error handler

set_http_proxy:
    mov esi, http_proxy_var            ; Load HTTP proxy environment variable name
    mov edi, environment_buffer        ; Destination buffer to append the variable name
    add edi, 7                         ; Skip past "export "
    call copy_string                   ; Copy "http_proxy="

    jmp setup_proxy_command            ; Continue with setting proxy

set_https_proxy:
    mov esi, https_proxy_var           ; Load HTTPS proxy environment variable name
    mov edi, environment_buffer        ; Destination buffer to append the variable name
    add edi, 7                         ; Skip past "export "
    call copy_string                   ; Copy "https_proxy="
    
    jmp setup_proxy_command            ; Continue with setting proxy

setup_proxy_command:
    mov esi, [R1]                      ; Load proxy server address
    mov edi, environment_buffer        ; Destination buffer
    add edi, 18                        ; Skip past "export http_proxy=" or "export https_proxy="
    call copy_string                   ; Copy the proxy address

    ; Append new line character
    mov byte [edi], new_line           ; Append newline character to the command
    inc edi

    ; Step 3: Execute the command to set the environment variable
    mov eax, 11                        ; sys_execve syscall number
    mov ebx, environment_buffer        ; Pointer to command string (command to be executed)
    xor ecx, ecx                       ; No arguments
    xor edx, edx                       ; No environment
    int 0x80                           ; Trigger the syscall

    ret

compare_http_https:
    ; Compare the proxy type with "http" or "https"
    mov edi, 'http'                    ; Compare with "http"
    repe cmpsb                         ; Repeat while equal and counter not zero
    ret

copy_string:
    ; Copy string from ESI to EDI
    .copy_loop:
        lodsb                          ; Load byte from source (ESI)
        stosb                          ; Store byte to destination (EDI)
        test al, al                    ; Check if end of string (null terminator)
        jnz .copy_loop                 ; Continue copying until null terminator
    ret

restore_register_data:
    pop ecx                  ; Restore register state
    pop ebx
    pop eax
    ret

invalid_proxy_type:
    ; Handle error for invalid proxy type
    ; Placeholder code
    ret


USER_AGENT_SYMBOL_HANDLER:
    ; Assume that R1 holds the User-Agent string.
    
    push eax                 ; Preserve register state

    mov eax, [R1]            ; Load User-Agent string into EAX
    call set_user_agent_string ; Call function to set the User-Agent string

    pop eax                  ; Restore register state
    ret

set_user_agent_string:
    ; Placeholder for actual User-Agent setting implementation
    ; This would involve storing the User-Agent string to be used in HTTP headers
    ret

SERVER_SYMBOL_HANDLER:
    ; Assume that R1 indicates the operation ('start' or 'stop').

    push eax                 ; Preserve register state
    mov eax, [R1]            ; Load the operation (start/stop) into EAX
    cmp eax, 'start'         ; Check if the command is to start the server
    jne .stop_server         ; If not 'start', assume 'stop'

    ; Start the server routine
    call start_server_routine ; Call function to start the server
    jmp .done

.stop_server:
    ; Stop the server routine
    call stop_server_routine ; Call function to stop the server

.done:
    pop eax                  ; Restore register state
    ret

start_server_routine:
    ; Step 1: Create a socket
    mov eax, 0x66              ; syscall: socketcall
    mov ebx, 1                 ; socketcall: SYS_SOCKET
    mov ecx, esp               ; Pointer to arguments
    push dword 0               ; Protocol: IP (0)
    push dword 1               ; Type: SOCK_STREAM (TCP)
    push dword 2               ; Domain: AF_INET (IPv4)
    int 0x80                   ; Interrupt for syscall
    mov [socket_fd], eax       ; Save the socket file descriptor

    ; Check for socket creation error
    cmp eax, 0
    jl socket_error            ; Jump if error (eax < 0)

    ; Step 2: Bind the socket to a port
    mov eax, 0x66              ; syscall: socketcall
    mov ebx, 2                 ; socketcall: SYS_BIND
    mov ecx, esp               ; Pointer to arguments
    push byte 16               ; Length of sockaddr_in structure
    push dword sock_addr       ; Pointer to sockaddr_in structure
    push dword [socket_fd]     ; Server socket file descriptor
    int 0x80                   ; Interrupt for syscall

    ; Check for bind error
    cmp eax, 0
    jl bind_error              ; Jump if error (eax < 0)

    ; Step 3: Listen on the socket
    mov eax, 0x66              ; syscall: socketcall
    mov ebx, 4                 ; socketcall: SYS_LISTEN
    mov ecx, esp               ; Pointer to arguments
    push dword [backlog]       ; Backlog: Number of connections allowed
    push dword [socket_fd]     ; Server socket file descriptor
    int 0x80                   ; Interrupt for syscall

    ; Check for listen error
    cmp eax, 0
    jl listen_error            ; Jump if error (eax < 0)

    ; Step 4: Accept connections (loop to accept multiple clients)
accept_loop:
    mov eax, 0x66              ; syscall: socketcall
    mov ebx, 5                 ; socketcall: SYS_ACCEPT
    mov ecx, esp               ; Pointer to arguments
    push dword 0               ; NULL for client address
    push dword 0               ; NULL for address length
    push dword [socket_fd]     ; Server socket file descriptor
    int 0x80                   ; Interrupt for syscall

    ; Check for accept error
    cmp eax, 0
    jl accept_error            ; Jump if error (eax < 0)

    ; Handle client connection (e.g., read/write to socket)
    ; This is a placeholder where you'd implement communication with the client
    ; After handling the client, loop back to accept more connections
    jmp accept_loop

    ; Error handling labels
socket_error:
    ; Set error code for socket creation failure
    mov dword [error_code], ERR_SOCKET_CREATION
    call REPORT_ERROR          ; Call the error reporting routine from err.asm
    ret

bind_error:
    ; Set error code for bind failure
    mov dword [error_code], ERR_BIND
    call REPORT_ERROR          ; Call the error reporting routine from err.asm
    ret

listen_error:
    ; Set error code for listen failure
    mov dword [error_code], ERR_LISTEN
    call REPORT_ERROR          ; Call the error reporting routine from err.asm
    ret

accept_error:
    ; Set error code for accept failure
    mov dword [error_code], ERR_ACCEPT
    call REPORT_ERROR          ; Call the error reporting routine from err.asm
    ret
    
stop_server_routine:
    ; Step 1: Close the server socket
    mov eax, 6                 ; syscall: close
    mov ebx, [socket_fd]       ; Server socket file descriptor
    int 0x80                   ; Interrupt for syscall

    ; Check for close error
    cmp eax, 0
    jl close_error             ; Jump if error (eax < 0)

    ret

close_error:
    ; Set error code for close failure
    mov dword [error_code], ERR_CLOSE
    call REPORT_ERROR          ; Call the error reporting routine from err.asm
    ret

ATTRIBUTE_SYMBOL_HANDLER:
    ; Assume R1 is the attribute name, R2 is the attribute value.
    
    push eax                 ; Preserve register state
    push ebx

    mov eax, [R1]            ; Load attribute name into EAX
    mov ebx, [R2]            ; Load attribute value into EBX
    call set_attribute_value ; Call function to set the attribute

    pop ebx                  ; Restore register state
    pop eax
    ret

set_attribute_value:
    ; Example file attributes

set_attribute_value:
    ; Set file attribute to read-only using DOS interrupt 21h, function 43h (Set File Attributes)
    
    mov ah, 0x43          ; DOS function 43h - Set file attributes
    mov al, 0x01          ; Subfunction 01h - Set file attributes
    mov dx, file_path     ; DS:DX points to the file path string
    mov cx, 0x01          ; File attribute: 01h = read-only
    
    int 0x21              ; Call DOS interrupt
    
    jc attribute_error    ; Jump if carry flag is set (indicating an error)

    ret

attribute_error:
    ; Error handling routine
    ; Here, you can define what happens if setting the attribute fails.
    ; This could involve logging the error, retrying, or returning an error code.
    mov ax, 0x1           ; Return error code 1 to indicate failure
    ret

    ; Actual implementation would depend on the attribute type (e.g., file attribute, system setting)
    ret

PATH_SYMBOL_HANDLER:
    ; Assume R1 holds the path to be added or set.
    
    push eax                 ; Preserve register state

    mov eax, [R1]            ; Load the path into EAX
    call set_system_path     ; Call function to set the system path

    pop eax                  ; Restore register state
    ret

FFT_SYMBOL_HANDLER:
    ; Call the FFT routine from mth.asm
    call FFT_ROUTINE
    ret

ADD_VECTOR_SYMBOL_HANDLER:
    ; Call the Vector Addition routine from mth.asm
    call ADD_VECTOR_ROUTINE
    ret

SUB_VECTOR_SYMBOL_HANDLER:
    ; Call the Vector Addition routine from mth.asm
    call SUB_VECTOR_ROUTINE
    ret

DOT_PRODUCT_SYMBOL_HANDLER:
    ; Call the Vector Addition routine from mth.asm
    call DOT_PRODUCT_ROUTINE
    ret

MATRIX_DETERMINANT_SYMBOL_HANDLER:
    ; Call the Vector Addition routine from mth.asm
    call MATRIX DETERMINANT_ROUTINE
    ret

MATRIX_INVERSE_SYMBOL_HANDLER:
    ; Call the Vector Addition routine from mth.asm
    call MATIX_INVERSE_ROUTINE
    ret

MATRIX_DETERMINANT_3X3_SYMBOL_HANDLER:
    ; Call the Vector Addition routine from mth.asm
    call MATRIX_DETERMIMNANT_3X3_ROUTINE
    ret


; Error handler for unknown commands
error_command_not_found:
    ; Set error code for unrecognized command
    mov dword [error_code], ERR_UN
