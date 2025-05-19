; `lgc64.asm` Logic Module in optimised x86 assembly 64-bit float fuzzy

section .data
align 32
; Floating-point constants
some_logic_constant dq 2.7182818284590452353602874713527
fuzzy_100 dq 100.0      ; Double-precision float constant representing 100
zero dq 0.0             ; Double-precision float representing 0
one dq 1.0              ; Double-precision float representing 1
fuzzy_50 dq 50.0        ; Double-precision float representing 50
output dq 0.0           ; Variable to store the output result
abs_mask dq 0x7FFFFFFFFFFFFFFF  ; Mask for absolute value (clear sign bit)

; Vector data
vector1 dq 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0   ; Aligned array
vector2 dq 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0, 0.0   ; Aligned array

section .bss
align 32
result_vector resq 8    ; Space for 8 double-precision results

section .text
extern REPORT_ERROR     ; From err64.asm

; Define comparison constants for AVX
_CMP_LE_OQ equ 2       ; Less than or equal (ordered, quiet)
_CMP_LT_OQ equ 1       ; Less than (ordered, quiet)
_CMP_EQ_OQ equ 0       ; Equal (ordered, quiet)

extern AND_ROUTINE

extern OR_ROUTINE, XOR_ROUTINE, NOT_ROUTINE, NAND_ROUTINE, NOR_ROUTINE
extern IF_ROUTINE, THEN_ROUTINE, ELSE_ROUTINE, IMPLY_ROUTINE, NIMPLY_ROUTINE
extern NULL_ROUTINE, INHIBITION_ROUTINE, BUFFER_ROUTINE, INHIBITION_XY_ROUTINE
extern EQUIVALENCE_ROUTINE, IMPLICATION_ROUTINE, IDENTITY_ROUTINE, LOGIC_HANDLER
extern ADD_LOGIC_ERR_ROUTINE, CMP_ROUTINE, VECTOR_AND_ROUTINE

; Convert binary to fuzzy logic (0 or 1 to 0 or 100)
BINARY_TO_FUZZY:
    movsd xmm1, [zero]
    ucomisd xmm0, xmm1
    jz .return_zero
    movsd xmm0, [fuzzy_100]
.return_zero:
    ret

; Convert fuzzy logic to binary (0-100 to 0 or 1)
FUZZY_TO_BINARY:
    movsd xmm1, [fuzzy_50]
    ucomisd xmm0, xmm1
    jae .return_one
    movsd xmm0, [zero]
    ret
.return_one:
    movsd xmm0, [one]
    ret

; Vector operations use Windows x64 calling convention:
; rcx = first vector pointer
; rdx = second vector pointer
; r8 = result vector pointer
; r9 = length (elements)

CMP_ROUTINE:
    push rbp
    mov rbp, rsp
    push rbx

    mov r10, r9                  ; Save length
    shr r10, 2                   ; Process 4 elements at a time

.loop:
    prefetcht0 [rcx + 64]        ; Prefetch next elements
    prefetcht0 [rdx + 64]        ; Prefetch next elements

    vmovapd ymm0, [rcx]          ; Load 4 doubles from first vector
    vmovapd ymm1, [rdx]          ; Load 4 doubles from second vector
    vsubpd ymm0, ymm0, ymm1      ; Compute difference

    ; Compare with zero and mask results
    vxorpd ymm3, ymm3, ymm3      ; Zero register for comparison
    vcmppd ymm2, ymm0, ymm3, _CMP_LE_OQ
    vandnpd ymm0, ymm2, ymm0     ; Zero out negative differences

    vmovapd [r8], ymm0           ; Store result

    add rcx, 32                  ; Move to next 4 elements
    add rdx, 32
    add r8, 32
    dec r10
    jnz .loop

    vzeroupper
    pop rbx
    pop rbp
    ret

VECTOR_AND_ROUTINE:
    push rbp
    mov rbp, rsp

    mov r10, r9                  ; Save length
    shr r10, 2                   ; Process 4 elements at a time

.loop:
    prefetcht0 [rcx + 64]        ; Prefetch next elements
    prefetcht0 [rdx + 64]        ; Prefetch next elements

    vmovapd ymm0, [rcx]          ; Load 4 doubles from first vector
    vmovapd ymm1, [rdx]          ; Load 4 doubles from second vector
    vminpd ymm0, ymm0, ymm1      ; Compute element-wise minimum (AND)
    vmovapd [r8], ymm0           ; Store result

    add rcx, 32                  ; Move to next 4 elements
    add rdx, 32
    add r8, 32
    dec r10
    jnz .loop

    vzeroupper
    pop rbp
    ret

; Scalar fuzzy logic operations use xmm0, xmm1 for inputs

OR_ROUTINE:
    vmaxsd xmm0, xmm0, xmm1     ; Fuzzy OR using maximum
    ret

XOR_ROUTINE:
    push rbp
    mov rbp, rsp
    
    ; Compute |a-b|
    vsubsd xmm2, xmm0, xmm1     ; a-b
    vandpd xmm0, xmm2, [abs_mask] ; Take absolute value
    
    pop rbp
    ret

NOT_ROUTINE:
    movsd xmm1, [fuzzy_100]     ; Load 100.0
    subsd xmm1, xmm0            ; 100 - input
    movapd xmm0, xmm1           ; Move to output register
    ret

NAND_ROUTINE:
    vminsd xmm0, xmm0, xmm1     ; Fuzzy AND
    movsd xmm2, [fuzzy_100]     ; Load 100.0
    vsubsd xmm0, xmm2, xmm0     ; NOT the result
    ret

NOR_ROUTINE:
    vmaxsd xmm0, xmm0, xmm1     ; Fuzzy OR
    movsd xmm2, [fuzzy_100]     ; Load 100.0
    vsubsd xmm0, xmm2, xmm0     ; NOT the result
    ret

IF_ROUTINE:
    ucomisd xmm0, xmm1          ; Compare condition
    jp .if_false                ; Jump if unordered
    je .if_false                ; Jump if equal
    movapd xmm0, xmm1           ; True result
    jmp .end_if
.if_false:
    movapd xmm0, xmm2           ; False result
.end_if:
    ret

IMPLICATION_ROUTINE:
    movsd xmm2, [fuzzy_100]     ; Load 100.0
    subsd xmm2, xmm0            ; 100 - A
    addsd xmm2, xmm1            ; (100 - A) + B
    minsd xmm0, xmm2            ; min(100, (100 - A) + B)
    ret

NIMPLY_ROUTINE:
    movapd xmm2, xmm0           ; Save A
    movapd xmm0, xmm1           ; Load B
    subsd xmm0, xmm2            ; B - A
    ret

NULL_ROUTINE:
    xorpd xmm0, xmm0            ; Set to 0.0
    ret

INHIBITION_ROUTINE:
    movsd xmm2, [fuzzy_100]     ; Load 100.0
    subsd xmm2, xmm1            ; 100 - B
    minsd xmm0, xmm2            ; min(A, 100 - B)
    ret

BUFFER_ROUTINE:
    ret                         ; No operation needed

INHIBITION_XY_ROUTINE:
    movsd xmm2, [fuzzy_100]     ; Load 100.0
    subsd xmm2, xmm0            ; 100 - A
    minsd xmm0, xmm1            ; min(100 - A, B)
    ret

EQUIVALENCE_ROUTINE:
    vminsd xmm2, xmm0, xmm1     ; min(A, B)
    movsd xmm3, [fuzzy_100]     ; Load 100.0
    vsubsd xmm4, xmm3, xmm0     ; 100 - A
    vsubsd xmm5, xmm3, xmm1     ; 100 - B
    vminsd xmm4, xmm4, xmm5     ; min(100 - A, 100 - B)
    vaddsd xmm0, xmm2, xmm4     ; Final result
    ret

IDENTITY_ROUTINE:
    movsd xmm0, [fuzzy_100]     ; Return 100.0
    ret

LOGIC_HANDLER:
    ; Command dispatch table
    push rbp
    mov rbp, rsp
    push rbx

    cmp rcx, '≈'                ; Compare commands
    je CMP_ROUTINE
    cmp rcx, '&'
    je VECTOR_AND_ROUTINE
    cmp rcx, '∨'
    je OR_ROUTINE
    cmp rcx, '⊕'
    je XOR_ROUTINE
    cmp rcx, '¬'
    je NOT_ROUTINE
    ; ... rest of command checks ...

    pop rbx
    pop rbp
    ret

END_LOGIC_HANDLER:
    ret

ADD_LOGIC_ERR_ROUTINE:
    ret