section .data
    ERR_HEADER_MISSING   equ 0x01
    ERR_BLOCK_ORDER      equ 0x02
    ERR_UNRECOGNIZED     equ 0x03
    ERR_TYPE_MISMATCH    equ 0x04
    ERR_RUNTIME          equ 0x05
    ERR_OUT_OF_BOUNDS    equ 0xFF05
    ERR_SOCKET_CREATION  equ 0x06
    ERR_BIND             equ 0x07
    ERR_LISTEN           equ 0x08
    ERR_ACCEPT           equ 0x09
    ERR_CLOSE            equ 0x0A
    ERR_ATTRIBUTE        equ 0x0B
    ERR_RUNTIME_DIV_ZERO   equ 0x01  ; Error code for division by zero
    ERR_RUNTIME_NULL_PTR   equ 0x02  ; Error code for null pointer dereference
    ERR_RUNTIME_OVF        equ 0x03  ; Error code for arithmetic overflow
    ERR_RUNTIME            equ 0x05  ; General runtime error
    ERR_MEM_INVALID_ADDRESS equ 0x40  ; Error code for invalid memory address access
    ERR_MEM_INVALID_OP      equ 0x41  ; Error code for invalid memory operation
    ERR_STRING_NULL_PTR      equ 0x30  ; Error code for null pointer access
    ERR_STRING_OVERFLOW      equ 0x31  ; Error code for string overflow
    ERR_STRING_INVALID_OP    equ 0x32  ; Error code for invalid string operation
    ERR_LOGIC_UNDEFINED_OP   equ 0x20  ; Error code for undefined boolean operation
    ERR_LOGIC_INVALID_COND   equ 0x21  ; Error code for invalid conditional statement
    ERR_LOGIC_INCONSISTENT   equ 0x22  ; Error code for inconsistent logic branching
    ERR_MATH_OVERFLOW      equ 0x10  ; Error code for arithmetic overflow
    ERR_MATH_DIV_ZERO      equ 0x11  ; Error code for division by zero
    ERR_MATH_INVALID_OPERAND equ 0x12  ; Error code for invalid operands
    ERR_FP_EXCEPTION  equ 0x0C   ; Error code for general floating-point exception
    ERR_FP_OVERFLOW   equ 0x0D   ; Error code for floating-point overflow
    ERR_FP_UNDERFLOW  equ 0x0E   ; Error code for floating-point underflow
    ERR_FP_INVALID    equ 0x0F   ; Error code for invalid floating-point operation (e.g., NaN)

section .bss
    line_number resd 1           ; Store the current line number
    error_code resd 1            ; Store the current error code

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
global ADD_RUNTIME_ERR_ROUTINE
global ADD_MEMCUNRECOG_ERR_ROUTINE
global ADD_STRING_ERR_ROUTINE
global ADD_LOGIC_ERR_ROUTINE
global ADD_MATH_ERR_ROUTINE
global REPORT_ERROR, CHECK_FP_ERROR

_start:
    ; Initialize Registers and Memory
    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx
    mov dword [line_number], 1   ; Initialize line number to 1
    mov dword [error_code], 0    ; Initialize error code to 0

    ; ... Rest of your main program logic ...

    ; Example call to check header
    call CHECK_HEADER

    ; Example error reporting
    mov eax, ERR_UNRECOGNIZED
    call REPORT_ERROR

    ; Continue program execution
    ; ...

REPORT_ERROR:
    ; Print error type and line number (implementation depends on your environment)
    mov eax, 4                  ; syscall number for sys_write
    mov ebx, 1                  ; file descriptor 1 (stdout)
    mov ecx, error_message      ; pointer to the error message
    mov edx, error_length       ; length of the error message
    int 0x80                    ; make syscall

    mov eax, 1                  ; syscall number for sys_exit
    mov ebx, 1                  ; exit code
    int 0x80                    ; make syscall
    ret

CHECK_HEADER:
    ; Check if header matches expected
    cmp dword [eax], EXPECTED_HEADER
    jne ERROR_HEADER_MISSING
    ; Continue program logic if no error
    ret

ERROR_HEADER_MISSING:
    mov dword [error_code], ERR_HEADER_MISSING
    call REPORT_ERROR
    ret

CHECK_BLOCK_ORDER:
    ; Check if block order is correct
    cmp dword [ebx], EXPECTED_BLOCK
    jne ERROR_BLOCK_ORDER
    ret

ERROR_BLOCK_ORDER:
    mov dword [error_code], ERR_BLOCK_ORDER
    call REPORT_ERROR
    ret

ERROR_OUT_OF_BOUNDS:
    mov dword [error_code], ERR_OUT_OF_BOUNDS
    call REPORT_ERROR
    ret

PARSE_COMMAND:
    ; Parse the command and jump to the correct handler
    cmp eax, 'KNOWN_COMMAND'
    je VALID_COMMAND
    mov dword [error_code], ERR_UNRECOGNIZED
    call REPORT_ERROR
    ret

VALID_COMMAND:
    ; Continue processing the valid command
    ret

CHECK_TYPES:
    ; Compare types of operands
    cmp dword [ebx], [ecx]
    je VALID_TYPES
    mov dword [error_code], ERR_TYPE_MISMATCH
    call REPORT_ERROR
    ret

VALID_TYPES:
    ; Continue with arithmetic operation
    ret

DIVISION_CHECK:
    ; Check if divisor is zero
    cmp ecx, 0
    jne VALID_DIVISION
    mov dword [error_code], ERR_RUNTIME
    call REPORT_ERROR
    ret

VALID_DIVISION:
    ; Continue with division operation
    ret

; Error Handling Functions
ADD_RUNTIME_ERR_ROUTINE:
    ; Here you can implement checks for various runtime errors

    ; Example: Check for division by zero
    cmp ecx, 0           ; Check if divisor (ecx) is zero
    je DIV_ZERO_ERROR    ; Jump to error handler if divisor is zero

    ; Example: Check for arithmetic overflow
    ; (assuming the previous operation could overflow eax)
    jo ARITH_OVERFLOW_ERROR  ; Jump to overflow handler if overflow flag is set

    ; Continue execution if no errors are found
    ret

DIV_ZERO_ERROR:
    mov dword [error_code], ERR_RUNTIME_DIV_ZERO
    call REPORT_ERROR    ; Call the error reporting routine
    ret

ARITH_OVERFLOW_ERROR:
    mov dword [error_code], ERR_RUNTIME_OVF
    call REPORT_ERROR    ; Call the error reporting routine
    ret

NULL_POINTER_ERROR:
    mov dword [error_code], ERR_RUNTIME_NULL_PTR
    call REPORT_ERROR    ; Call the error reporting routine
    ret

GENERAL_RUNTIME_ERROR:
    mov dword [error_code], ERR_RUNTIME
    call REPORT_ERROR    ; General error handler
    ret


; Routine to check for floating-point errors
CHECK_FP_ERROR:
    ; Use the `ucomisd` instruction to check for NaN or other FP exceptions
    ; Input: XMM0 is typically used in the preceding floating-point operation

    movaps xmm1, xmm0       ; Copy the result for comparison
    ucomisd xmm1, xmm1      ; Compare with itself to check for NaN
    jp .fp_invalid          ; Jump if the result is unordered (NaN)

    ; Additional checks could be added here for overflow/underflow if needed

    ret

.fp_invalid:
    mov eax, ERR_FP_INVALID
    call REPORT_ERROR
    ret

REPORT_ERROR:
    ; Error handling logic
    ; This routine should print or handle the error based on error codes, including FP errors
    cmp eax, ERR_FP_EXCEPTION
    je .handle_fp_exception
    cmp eax, ERR_FP_OVERFLOW
    je .handle_fp_overflow
    cmp eax, ERR_FP_UNDERFLOW
    je .handle_fp_underflow
    cmp eax, ERR_FP_INVALID
    je .handle_fp_invalid
    ; Continue with existing error handling...

.handle_fp_exception:
    ; Handle general floating-point exception
    ; Print message or take appropriate action
    ret

.handle_fp_overflow:
    ; Handle floating-point overflow
    ret

.handle_fp_underflow:
    ; Handle floating-point underflow
    ret

.handle_fp_invalid:
    ; Handle invalid floating-point operation (NaN, etc.)
    ret

REPORT_ERROR:
    ; Example error reporting function to handle errors (prints to console, logs, etc.)
    ; Code here depends on the specific environment (Linux syscall, Windows API, etc.)
    ; Here, a simple exit strategy is shown

    ; Print the error message based on error_code
    ; Example: Printing error to console
    mov eax, 4            ; syscall number for sys_write
    mov ebx, 1            ; file descriptor 1 (stdout)
    mov ecx, error_message  ; pointer to the error message
    mov edx, error_length ; length of the error message
    int 0x80              ; make syscall

    ; Exit the program after reporting error
    mov eax, 1            ; syscall number for sys_exit
    mov ebx, 1            ; exit code
    int 0x80              ; make syscall

    ret

ADD_MATH_ERR_ROUTINE:
    ; Code to handle math errors
    ; Check for different types of math errors

    ; Check for arithmetic overflow
    jo MATH_OVERFLOW_ERROR  ; Jump if overflow flag is set

    ; Check for division by zero
    cmp ecx, 0              ; Assuming divisor is in ecx
    je DIV_ZERO_MATH_ERROR  ; Jump if ecx is zero

    ; Check for invalid operands (example scenario)
    ; (Assume a function to validate operand types)
    call VALIDATE_OPERANDS
    jnz INVALID_OPERAND_ERROR ; Jump if operands are invalid

    ret

MATH_OVERFLOW_ERROR:
    mov dword [error_code], ERR_MATH_OVERFLOW
    call REPORT_ERROR
    ret

DIV_ZERO_MATH_ERROR:
    mov dword [error_code], ERR_MATH_DIV_ZERO
    call REPORT_ERROR
    ret

INVALID_OPERAND_ERROR:
    mov dword [error_code], ERR_MATH_INVALID_OPERAND
    call REPORT_ERROR
    ret

ADD_LOGIC_ERR_ROUTINE:
    ; Code to handle logic errors  

    ; Example: Check for undefined boolean operation
    ; (Assume that edx contains a result of some boolean operation)
    cmp edx, 0
    jl UNDEFINED_LOGIC_ERROR  ; Jump if boolean result is not 0 or 1

    ; Example: Check for invalid conditional (using a non-boolean)
    ; (Assume a function that verifies if a condition is boolean)
    call VALIDATE_CONDITION
    jnz INVALID_COND_ERROR    ; Jump if condition is invalid

    ; Example: Check for inconsistent logic branching
    ; (Placeholder for detecting unreachable code or infinite loop)
    ; Logic for this error would depend on specific use case

    ret

UNDEFINED_LOGIC_ERROR:
    mov dword [error_code], ERR_LOGIC_UNDEFINED_OP
    call REPORT_ERROR
    ret

INVALID_COND_ERROR:
    mov dword [error_code], ERR_LOGIC_INVALID_COND
    call REPORT_ERROR
    ret

INCONSISTENT_LOGIC_ERROR:
    mov dword [error_code], ERR_LOGIC_INCONSISTENT
    call REPORT_ERROR
    ret

ADD_STRING_ERR_ROUTINE:
    ; Code to handle string errors

ADD_STRING_ERR_ROUTINE:
    ; Check for string-related errors

    ; Check for null pointer access
    cmp eax, 0              ; Assuming eax is pointer to string
    je STRING_NULL_PTR_ERROR ; Jump if eax is null (zero)

    ; Check for string overflow (writing past end of buffer)
    ; (Assume esi is destination buffer pointer, edi is source pointer)
    call CHECK_STRING_OVERFLOW
    jnz STRING_OVERFLOW_ERROR ; Jump if overflow is detected

    ; Check for invalid string operation
    ; (Assume a function that validates string operation)
    call VALIDATE_STRING_OPERATION
    jnz STRING_INVALID_OP_ERROR ; Jump if operation is invalid

    ret

STRING_NULL_PTR_ERROR:
    mov dword [error_code], ERR_STRING_NULL_PTR
    call REPORT_ERROR
    ret

STRING_OVERFLOW_ERROR:
    mov dword [error_code], ERR_STRING_OVERFLOW
    call REPORT_ERROR
    ret

STRING_INVALID_OP_ERROR:
    mov dword [error_code], ERR_STRING_INVALID_OP
    call REPORT_ERROR
    ret

ADD_MEMCUNRECOG_ERR_ROUTINE:
    ; Code to handle unrecognized memory commands

    ; Check for different types of memory errors

    ; Example: Check if memory address is valid (assuming eax has the address)
    cmp eax, MIN_MEMORY_ADDRESS  ; Check if below minimum address
    jb INVALID_MEM_ADDRESS_ERROR ; Jump if below minimum address
    cmp eax, MAX_MEMORY_ADDRESS  ; Check if above maximum address
    ja INVALID_MEM_ADDRESS_ERROR ; Jump if above maximum address

    ; Example: Check for invalid memory operation (assuming edx has operation code)
    cmp edx, MAX_VALID_MEM_OP    ; Compare with maximum valid memory operation
    ja INVALID_MEM_OP_ERROR      ; Jump if beyond valid operation codes

    ret

INVALID_MEM_ADDRESS_ERROR:
    mov dword [error_code], ERR_MEM_INVALID_ADDRESS
    call REPORT_ERROR
    ret

INVALID_MEM_OP_ERROR:
    mov dword [error_code], ERR_MEM_INVALID_OP
    call REPORT_ERROR
    ret

ADD_OVLDFUNC_ERR_ROUTINE:
    ; Code to handle overloaded function errors
    ret

ADD_UNRECOG:
    ; If the command is not recognized
    mov dword [error_code], ERR_UNRECOGNIZED
    call REPORT_ERROR
    ret

; New Error Handling Routines
socket_error:
    mov dword [error_code], ERR_SOCKET_CREATION
    call REPORT_ERROR
    ret

bind_error:
    mov dword [error_code], ERR_BIND
    call REPORT_ERROR
    ret

listen_error:
    mov dword [error_code], ERR_LISTEN
    call REPORT_ERROR
    ret

accept_error:
    mov dword [error_code], ERR_ACCEPT
    call REPORT_ERROR
    ret

close_error:
    mov dword [error_code], ERR_CLOSE
    call REPORT_ERROR
    ret

attribute_error:
    mov dword [error_code], ERR_ATTRIBUTE
    call REPORT_ERROR
    ret

error_command_not_found:
    mov dword [error_code], ERR_UNRECOGNIZED
    call REPORT_ERROR
    ret
