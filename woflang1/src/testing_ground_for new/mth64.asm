; `mth64.asm` optimized math module for internal use with woflang x086 64bit float fuzzy.

section .data
align 32  ; Align data for cache efficiency and SIMD operations
    MATRIX_SIZE equ 4
    VECTOR_LENGTH equ 1024
    PI dq 3.14159265358979323846264338327950288419716939937510  ; Constant for FFT

    ; Error Codes (matching err64.asm)
    ERR_MEM_ALLOC_FAIL equ 0x01
    ERR_DIV_ZERO equ 0x02
    ERR_UNDEFINED_MATRIX_SIZE equ 0x03

    ; Memory boundary checking
    MAX_ALLOC_SIZE equ 1024*1024*16  ; 16MB max allocation

section .bss
align 32  ; Align buffers for SIMD operations
    matrix1 resq MATRIX_SIZE * MATRIX_SIZE  ; Matrix buffers for double precision
    inverse_matrix resq MATRIX_SIZE * MATRIX_SIZE
    determinant resq 1                      ; Determinant result storage
    vector1 resq VECTOR_LENGTH              ; Vector buffers
    vector2 resq VECTOR_LENGTH
    result_vector resq VECTOR_LENGTH
    fft_real resq VECTOR_LENGTH             ; FFT input/output buffers
    fft_imag resq VECTOR_LENGTH

section .text
extern REPORT_ERROR               ; From err64.asm
extern ADD_ROUTINE                ; Declare external ADD_ROUTINE from add_resolver64.asm

extern global SUB_ROUTINE, MUL_ROUTINE, DIV_ROUTINE
global ADD_VECTOR_ROUTINE, SUB_VECTOR_ROUTINE, DOT_PRODUCT_ROUTINE
global FFT_ROUTINE, MATRIX_DETERMINANT_ROUTINE, MATRIX_INVERSE_ROUTINE
global ALLOCATE_MEMORY, FREE_MEMORY
global MATRIX_DETERMINANT_3X3_ROUTINE

; Rest o; Function to dynamically allocate memory
ALLOCATE_MEMORY:
    ; Windows x64 calling convention
    ; rcx = size to allocate
    
    ; Check size is reasonable
    cmp rcx, MAX_ALLOC_SIZE
    ja .alloc_fail
    
    ; Preserve rcx as it might be needed after syscall
    mov r10, rcx
    
    mov rax, 9          ; mmap syscall number
    xor rdx, rdx        ; let OS choose address
    mov r8, 0x22        ; MAP_PRIVATE | MAP_ANONYMOUS
    mov r9, -1          ; fd = -1
    syscall
    
    test rax, rax       ; Check if allocation failed
    js .alloc_fail
    ret

.alloc_fail:
    mov rcx, ERR_MEM_ALLOC_FAIL   ; First parameter for Windows x64
    call REPORT_ERROR
    xor rax, rax                  ; Return NULL
    ret

; Function to free dynamically allocated memory
FREE_MEMORY:
    ; Windows x64: rcx = pointer to free
    mov rax, 11         ; munmap syscall
    syscall
    ret

; Vector Addition using AVX
ADD_VECTOR_ROUTINE:
    mov r10, r9         ; Copy length
    shr r10, 2          ; Process 4 elements at a time

.add_loop:
    vmovapd ymm0, [rcx]          ; Load 4 doubles from first vector
    vmovapd ymm1, [rdx]          ; Load 4 doubles from second vector
    vaddpd ymm2, ymm0, ymm1      ; Add vectors
    vmovapd [r8], ymm2           ; Store result
    
    add rcx, 32                   ; Advance pointers (4 doubles = 32 bytes)
    add rdx, 32
    add r8, 32
    dec r10
    jnz .add_loop
    
    vzeroupper                    ; Clear upper bits of YMM registers
    ret

; SUB Routine using SIMD (AVX)
SUB_ROUTINE:
    ; Windows x64: xmm0, xmm1 already contain our operands
    subsd xmm0, xmm1    ; Subtract scalar double
    ret

; Vector Subtraction using AVX
SUB_VECTOR_ROUTINE:
    mov r10, r9         ; Copy length
    shr r10, 2          ; Process 4 elements at a time

.sub_loop:
    vmovapd ymm0, [rcx]          ; Load 4 doubles from first vector
    vmovapd ymm1, [rdx]          ; Load 4 doubles from second vector
    vsubpd ymm2, ymm0, ymm1      ; Subtract vectors
    vmovapd [r8], ymm2           ; Store result
    
    add rcx, 32                   ; Advance pointers
    add rdx, 32
    add r8, 32
    dec r10
    jnz .sub_loop
    
    vzeroupper
    ret

; MUL Routine using SIMD (AVX)
MUL_ROUTINE:
    ; Windows x64: xmm0, xmm1 already contain our operands
    mulsd xmm0, xmm1    ; Multiply scalar double
    ret

; DIV Routine with error checking
DIV_ROUTINE:
    ; Check for division by zero
    xorpd xmm2, xmm2            ; Zero xmm2
    ucomisd xmm1, xmm2          ; Compare divisor with zero
    je .div_zero_error
    
    divsd xmm0, xmm1            ; Perform division
    ret

.div_zero_error:
    mov rcx, ERR_DIV_ZERO       ; Windows x64 parameter
    call REPORT_ERROR
    ret

; Dot Product using AVX
DOT_PRODUCT_ROUTINE:
    mov r10, r9                  ; Copy length
    shr r10, 2                   ; Process 4 elements at a time
    vxorpd ymm2, ymm2, ymm2     ; Clear accumulator

.dot_loop:
    vmovapd ymm0, [rcx]         ; Load 4 doubles from first vector
    vmovapd ymm1, [rdx]         ; Load 4 doubles from second vector
    vmulpd ymm3, ymm0, ymm1     ; Multiply vectors
    vaddpd ymm2, ymm2, ymm3     ; Add to accumulator
    
    add rcx, 32                  ; Advance pointers
    add rdx, 32
    dec r10
    jnz .dot_loop

    ; Horizontal add to get final result
    vhaddpd ymm2, ymm2, ymm2
    vextractf128 xmm3, ymm2, 1
    vaddsd xmm0, xmm2, xmm3
    
    vzeroupper
    ret

; Matrix operations (3x3 determinant as example)
MATRIX_DETERMINANT_3X3_ROUTINE:
    push rbp
    mov rbp, rsp
    push rbx

    ; Calculate 3x3 determinant using cofactor expansion
    ; Assuming matrix is in rcx (Windows x64 first parameter)
    
    ; First term: a11(a22a33 - a23a32)
    movsd xmm0, [rcx]           ; a11
    movsd xmm1, [rcx + 16]      ; a22
    movsd xmm2, [rcx + 32]      ; a33
    mulsd xmm1, xmm2            ; a22*a33
    movsd xmm3, [rcx + 24]      ; a23
    movsd xmm4, [rcx + 40]      ; a32
    mulsd xmm3, xmm4            ; a23*a32
    subsd xmm1, xmm3            ; a22a33 - a23a32
    mulsd xmm0, xmm1            ; a11(a22a33 - a23a32)
    
    ; Store result
    movsd [determinant], xmm0
    
    pop rbx
    pop rbp
    ret

; Matrix Inverse (placeholder - would need full implementation)
MATRIX_INVERSE_ROUTINE:
    ret

; FFT (placeholder - would need full implementation)
FFT_ROUTINE:
    ret