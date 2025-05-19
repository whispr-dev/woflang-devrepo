; `err64.asm` optimised universal error handler for woflang x086 64bit float fuzzy

section .data
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
    ERR_CLOSE               equ 0x0A
    ERR_ATTRIBUTE           equ 0x0B
    ERR_RUNTIME_DIV_ZERO    equ 0x11  ; Consolidated error codes to avoid overlap
    ERR_RUNTIME_NULL_PTR    equ 0x12
    ERR_RUNTIME_OVF         equ 0x13
    ERR_MEM_INVALID_ADDRESS equ 0x40
    ERR_MEM_INVALID_OP      equ 0x41
    ERR_STRING_NULL_PTR     equ 0x30
    ERR_STRING_OVERFLOW     equ 0x31
    ERR_STRING_INVALID_OP   equ 0x32
    ERR_LOGIC_UNDEFINED_OP  equ 0x20
    ERR_LOGIC_INVALID_COND  equ 0x21
    ERR_LOGIC_INCONSISTENT  equ 0x22
    ERR_MATH_OVERFLOW       equ 0x10
    ERR_MATH_DIV_ZERO       equ 0x11
    ERR_MATH_INVALID_OPERAND equ 0x12
    ERR_FP_EXCEPTION        equ 0x0C
    ERR_FP_OVERFLOW         equ 0x0D
    ERR_FP_UNDERFLOW        equ 0x0E
    ERR_FP_INVALID          equ 0x0F

    ; Expected header or initial state values for checks
    EXPECTED_HEADER db 'EXPECTED_HEADER_TEXT'  ; Placeholder for actual header text
    important_memory_location dd 0x0           ; Placeholder memory location

section .bss
    line_number resd 1  ; Store the current line number
    error_code resd 1   ; Store the current error code

section .text

global _start
global REPORT_ERROR
global CHECK_HEADER
global CHECK_BLOCK_ORDER
global ERROR_OUT_OF_BOUNDS
global PARSE_COMMAND
global CHECK_TYPES
global DIVISION_CHECK
global ADD_RUNTIME_ERR_ROUTINE
global ADD_MATH_ERR_ROUTINE
global ADD_LOGIC_ERR_ROUTINE
global ADD_STRING_ERR_ROUTINE
global ADD_MEMCUNRECOG_ERR_ROUTINE
global ADD_OVLDFUNC_ERR_ROUTINE
global socket_error
global bind_error
global listen_error
global accept_error
global close_error
global attribute_error
global error_command_not_found
global REPORT_ERROR, CHECK_FP_ERROR

_start:
    ; Initialize Registers and Memory
    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx
    mov dword [line_number], 1  ; Initialize line number to 1
    mov dword [error_code], 0   ; Initialize error code to 0

    ; Initialize essential memory locations to expected defaults
    mov eax, expected_value
    mov [important_memory_location], eax

    ; Check if the memory setup is correct
    cmp dword [important_memory_location], expected_value
    jne ERROR_UNINITIALIZED_MEMORY

    ; Example call to check header - validate program header
    call CHECK_HEADER

    ; Continue with main program execution if no errors are found
    mov eax, 0  ; Reset register to a known state before main execution
    mov ebx, 0  ; Clear other registers

    ; Main program logic goes here...
    ; ...

ERROR_UNINITIALIZED_MEMORY:
    mov dword [error_code], ERR_MEM_INVALID_ADDRESS
    jmp REPORT_ERROR

CHECK_HEADER:
    ; Check if header matches expected
    cmp dword [eax], EXPECTED_HEADER
    jne ERROR_HEADER_MISSING
    ret

ERROR_HEADER_MISSING:
    mov dword [error_code], ERR_HEADER_MISSING
    jmp REPORT_ERROR

CHECK_BLOCK_ORDER:
    ; Check if block order is correct
    cmp dword [ebx], EXPECTED_BLOCK
    jne ERROR_BLOCK_ORDER
    ret

ERROR_BLOCK_ORDER:
    mov dword [error_code], ERR_BLOCK_ORDER
    jmp REPORT_ERROR

ERROR_OUT_OF_BOUNDS:
    mov dword [error_code], ERR_OUT_OF_BOUNDS
    jmp REPORT_ERROR

PARSE_COMMAND:
    ; Parse the command and jump to the correct handler
    cmp eax, 'KNOWN_COMMAND'
    je VALID_COMMAND
    mov dword [error_code], ERR_UNRECOGNIZED
    jmp REPORT_ERROR

VALID_COMMAND:
    ; Continue processing the valid command
    ret

CHECK_TYPES:
    ; Compare types of operands
    cmp dword [ebx], [ecx]
    je VALID_TYPES
    mov dword [error_code], ERR_TYPE_MISMATCH
    jmp REPORT_ERROR

VALID_TYPES:
    ; Continue with arithmetic operation
    ret

DIVISION_CHECK:
    ; Check if divisor is zero
    test ecx, ecx
    jnz VALID_DIVISION
    mov dword [error_code], ERR_RUNTIME_DIV_ZERO
    jmp REPORT_ERROR

VALID_DIVISION:
    ; Continue with division operation
    ret

ADD_RUNTIME_ERR_ROUTINE:
    ; Check for various runtime errors
    test ecx, ecx             ; Check if divisor (ecx) is zero
    jz DIV_ZERO_ERROR         ; Jump to error handler if divisor is zero

    ; Example: Check for arithmetic overflow (if previously set)
    jo ARITH_OVERFLOW_ERROR   ; Jump to overflow handler if overflow flag is set

    ; Continue execution if no errors are found
    ret

DIV_ZERO_ERROR:
    mov dword [error_code], ERR_RUNTIME_DIV_ZERO
    jmp REPORT_ERROR

ARITH_OVERFLOW_ERROR:
    mov dword [error_code], ERR_RUNTIME_OVF
    jmp REPORT_ERROR

NULL_POINTER_ERROR:
    mov dword [error_code], ERR_RUNTIME_NULL_PTR
    jmp REPORT_ERROR

GENERAL_RUNTIME_ERROR:
    mov dword [error_code], ERR_RUNTIME
    jmp REPORT_ERROR

CHECK_FP_ERROR:
    ; Check for floating-point errors
    movaps xmm1, xmm0       ; Copy the result for comparison
    ucomisd xmm1, xmm1      ; Compare with itself to check for NaN
    jp .fp_invalid          ; Jump if unordered (NaN)

    ; Additional checks for overflow/underflow if needed

    ret

.fp_invalid:
    mov eax, ERR_FP_INVALID
    jmp REPORT_ERROR

ADD_MATH_ERR_ROUTINE:
    ; Handle math errors
    jo MATH_OVERFLOW_ERROR  ; Jump if overflow flag is set

    test ecx, ecx              ; Assuming divisor is in ecx
    jz DIV_ZERO_MATH_ERROR  ; Jump if ecx is zero

    call VALIDATE_OPERANDS
    jnz INVALID_OPERAND_ERROR ; Jump if operands are invalid

    ret

MATH_OVERFLOW_ERROR:
    mov dword [error_code], ERR_MATH_OVERFLOW
    jmp REPORT_ERROR

DIV_ZERO_MATH_ERROR:
    mov dword [error_code], ERR_MATH_DIV_ZERO
    jmp REPORT_ERROR

INVALID_OPERAND_ERROR:
    mov dword [error_code], ERR_MATH_INVALID_OPERAND
    jmp REPORT_ERROR

ADD_LOGIC_ERR_ROUTINE:
    ; Handle logic errors
    cmp edx, 0
    jl UNDEFINED_LOGIC_ERROR

    call VALIDATE_CONDITION
    jnz INVALID_COND_ERROR

    ret

UNDEFINED_LOGIC_ERROR:
    mov dword [error_code], ERR_LOGIC_UNDEFINED_OP
    jmp REPORT_ERROR

INVALID_COND_ERROR:
    mov dword [error_code], ERR_LOGIC_INVALID_COND
    jmp REPORT_ERROR

INCONSISTENT_LOGIC_ERROR:
    mov dword [error_code], ERR_LOGIC_INCONSISTENT
    jmp REPORT_ERROR

ADD_STRING_ERR_ROUTINE:
    ; Check for string-related errors
    test eax, eax              ; Assuming eax is pointer to string
    jz STRING_NULL_PTR_ERROR

    call CHECK_STRING_OVERFLOW
    jnz STRING_OVERFLOW_ERROR

    call VALIDATE_STRING_OPERATION
    jnz STRING_INVALID_OP_ERROR

    ret

STRING_NULL_PTR_ERROR:
    mov dword [error_code], ERR_STRING_NULL_PTR
    jmp REPORT_ERROR

STRING_OVERFLOW_ERROR:
    mov dword [error_code], ERR_STRING_OVERFLOW
    jmp REPORT_ERROR

STRING_INVALID_OP_ERROR:
    mov dword [error_code], ERR_STRING_INVALID_OP
    jmp REPORT_ERROR

ADD_MEMCUNRECOG_ERR_ROUTINE:
    ; Check for different types of memory errors

    cmp eax, MIN_MEMORY_ADDRESS
    jb INVALID_MEM_ADDRESS_ERROR
    cmp eax, MAX_MEMORY_ADDRESS
    ja INVALID_MEM_ADDRESS_ERROR

    cmp edx, MAX_VALID_MEM_OP
    ja INVALID_MEM_OP_ERROR

    ret

INVALID_MEM_ADDRESS_ERROR:
    mov dword [error_code], ERR_MEM_INVALID_ADDRESS
    jmp REPORT_ERROR

INVALID_MEM_OP_ERROR:
    mov dword [error_code], ERR_MEM_INVALID_OP
    jmp REPORT_ERROR

ADD_OVLDFUNC_ERR_ROUTINE:
    ; Handle overloaded function errors
    ret

ADD_UNRECOG:
    ; If the command is not recognized
    mov dword [error_code], ERR_UNRECOGNIZED
    jmp REPORT_ERROR

socket_error:
    mov dword [error_code], ERR_SOCKET_CREATION
    jmp REPORT_ERROR

bind_error:
    mov dword [error_code], ERR_BIND
    jmp REPORT_ERROR

listen_error:
    mov dword [error_code], ERR_LISTEN
    jmp REPORT_ERROR

accept_error:
    mov dword [error_code], ERR_ACCEPT
    jmp REPORT_ERROR

close_error:
    mov dword [error_code], ERR_CLOSE
    jmp REPORT_ERROR

attribute_error:
    mov dword [error_code], ERR_ATTRIBUTE
    jmp REPORT_ERROR

error_command_not_found:
    mov dword [error_code], ERR_UNRECOGNIZED
    jmp REPORT_ERROR
