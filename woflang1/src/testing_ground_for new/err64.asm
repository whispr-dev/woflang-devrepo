; `err64.asm` optimised universal error handler for woflang x086 64bit float fuzzy

section .data
    ; Memory boundaries and validation constants
    MIN_MEMORY_ADDRESS   equ 0x1000
    MAX_MEMORY_ADDRESS   equ 0x7FFFFFFF
    MAX_VALID_MEM_OP     equ 0xFF
    expected_value       equ 0x12345678    ; Example initialization value

    ; Error codes
    ERR_HEADER_MISSING      equ 0x01
    ERR_BLOCK_ORDER         equ 0x02
    ERR_UNRECOGNIZED        equ 0x03
    ERR_TYPE_MISMATCH       equ 0x04
    ERR_RUNTIME             equ 0x05
    ERR_OUT_OF_BOUNDS       equ 0xFF05
    ERR_SOCKET_CREATION     equ 0x06
    ERR_BIND                equ 0x07
    ERR_LISTEN              equ 0x08
    ERR_ACCEPT              equ 0x09
    ERR_CLOSE              equ 0x0A
    ERR_ATTRIBUTE          equ 0x0B
    ERR_RUNTIME_DIV_ZERO   equ 0x11
    ERR_RUNTIME_NULL_PTR   equ 0x12
    ERR_RUNTIME_OVF        equ 0x13
    ERR_MEM_INVALID_ADDRESS equ 0x40
    ERR_MEM_INVALID_OP     equ 0x41
    ERR_STRING_NULL_PTR    equ 0x30
    ERR_STRING_OVERFLOW    equ 0x31
    ERR_STRING_INVALID_OP  equ 0x32
    ERR_LOGIC_UNDEFINED_OP equ 0x20
    ERR_LOGIC_INVALID_COND equ 0x21
    ERR_LOGIC_INCONSISTENT equ 0x22
    ERR_MATH_OVERFLOW      equ 0x10
    ERR_MATH_DIV_ZERO      equ 0x11
    ERR_MATH_INVALID_OPERAND equ 0x12
    ERR_FP_EXCEPTION       equ 0x0C
    ERR_FP_OVERFLOW        equ 0x0D
    ERR_FP_UNDERFLOW       equ 0x0E
    ERR_FP_INVALID         equ 0x0F

    ; Block types and validation
    EXPECTED_BLOCK        equ 0x424C4B00   ; "BLK\0" in ASCII
    EXPECTED_HEADER       db 'WFL_HEADER', 0

    ; Error messages (if needed)
    err_msg_buffer        db 256 dup(0)
    important_memory_location dd 0x0

section .bss
    line_number      resd 1  ; Store the current line number
    error_code       resd 1  ; Store the current error code

section .text
global REPORT_ERROR, CHECK_HEADER, CHECK_BLOCK_ORDER
global ERROR_OUT_OF_BOUNDS, CHECK_TYPES, DIVISION_CHECK
global VALIDATE_OPERANDS, VALIDATE_CONDITION
global CHECK_STRING_OVERFLOW, VALIDATE_STRING_OPERATION
global close_error, attribute_error, error_command_not_found

; Validation routines
VALIDATE_OPERANDS:
    ; Simple operand validation
    test rdi, rdi        ; Check if first operand is null
    jz .invalid
    test rsi, rsi        ; Check if second operand is null
    jz .invalid
    xor rax, rax         ; Return success
    ret
.invalid:
    mov rax, 1           ; Return error
    ret

VALIDATE_CONDITION:
    ; Simple condition validation
    cmp rdi, 0           ; Check if condition is negative
    jl .invalid
    xor rax, rax         ; Return success
    ret
.invalid:
    mov rax, 1           ; Return error
    ret

CHECK_STRING_OVERFLOW:
    ; String overflow check
    mov rcx, rdi         ; Load string length
    cmp rcx, 1024        ; Max string length
    ja .overflow
    xor rax, rax         ; Return success
    ret
.overflow:
    mov rax, 1           ; Return error
    ret

VALIDATE_STRING_OPERATION:
    ; Validate string operation
    test rdi, rdi        ; Check if string pointer is null
    jz .invalid
    xor rax, rax         ; Return success
    ret
.invalid:
    mov rax, 1           ; Return error
    ret

; Main error reporting routine
REPORT_ERROR:
    ; Save registers
    push rbp
    mov rbp, rsp
    push rbx
    push r12

    ; Store error code
    mov [error_code], edi

    ; Here you would implement your error reporting logic
    ; For example, printing error message, logging, etc.
    
    ; Restore registers
    pop r12
    pop rbx
    pop rbp
    ret

; Error check routines
CHECK_HEADER:
    ; Check if header matches expected
    mov rsi, EXPECTED_HEADER
    mov rdi, [rax]       ; Load header from memory
    mov rcx, 10          ; Length of "WFL_HEADER\0"
    repe cmpsb
    jne .header_error
    xor rax, rax         ; Return success
    ret
.header_error:
    mov rdi, ERR_HEADER_MISSING
    call REPORT_ERROR
    mov rax, 1           ; Return error
    ret

CHECK_BLOCK_ORDER:
    ; Validate block order
    cmp dword [rbx], EXPECTED_BLOCK
    jne .block_error
    xor rax, rax         ; Return success
    ret
.block_error:
    mov rdi, ERR_BLOCK_ORDER
    call REPORT_ERROR
    mov rax, 1           ; Return error
    ret

close_error:
    mov rdi, ERR_CLOSE
    jmp REPORT_ERROR

attribute_error:
    mov rdi, ERR_ATTRIBUTE
    jmp REPORT_ERROR

error_command_not_found:
    mov rdi, ERR_UNRECOGNIZED
    jmp REPORT_ERROR