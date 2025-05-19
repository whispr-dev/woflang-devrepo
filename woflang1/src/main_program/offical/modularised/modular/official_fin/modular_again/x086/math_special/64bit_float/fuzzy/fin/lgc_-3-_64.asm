; `lgc64.asm` Logic Module in optmised x86 assembly 64-bit float fuzzy

section .data
align 32
; Floating-point constants or buffers defined as `dq`.
some_logic_constant dq 2.7182818284590452353602874713527
fuzzy_100 dq 100.0      ; Double-precision float constant representing 100
zero dq 0.0             ; Double-precision float representing 0
one dq 1.0              ; Double-precision float representing 1
fuzzy_50 dq 50.0        ; Double-precision float representing 50
output dq 0.0           ; Variable to store the output result
vector1 dq 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0   ; Aligned array
vector2 dq 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0, 0.0   ; Aligned array

section .text

global AND_ROUTINE, OR_ROUTINE, XOR_ROUTINE, NOT_ROUTINE, NAND_ROUTINE, NOR_ROUTINE
global IF_ROUTINE, THEN_ROUTINE, ELSE_ROUTINE, IMPLY_ROUTINE, NIMPLY_ROUTINE
global NULL_ROUTINE, INHIBITION_ROUTINE, BUFFER_ROUTINE, INHIBITION_XY_ROUTINE
global EQUIVALENCE_ROUTINE, IMPLICATION_ROUTINE, IDENTITY_ROUTINE, LOGIC_HANDLER
global ADD_LOGIC_ERR_ROUTINE, CMP_ROUTINE, VECTOR_AND_ROUTINE

; Convert binary to fuzzy logic (0 or 1 to 0 or 100)
BINARY_TO_FUZZY:
    ucomisd xmm0, [zero]
    cmove xmm0, [fuzzy_100]  ; Conditional move to set xmm0 to 100 if xmm0 is not zero
    ret

; Convert fuzzy logic to binary (0-100 to 0 or 1)
FUZZY_TO_BINARY:
    movsd xmm1, [fuzzy_50]
    ucomisd xmm0, xmm1
    cmovae xmm0, [one]       ; Conditional move to set xmm0 to 1 if xmm0 >= 50
    cmovb xmm0, [zero]       ; Conditional move to set xmm0 to 0 if xmm0 < 50
    ret

CMP_ROUTINE:
    mov rcx, 2               ; Process 8 elements per iteration (vector length divided by 4)
    mov rsi, vector1         ; Pointer to vector1
    mov rdi, vector2         ; Pointer to vector2
    mov rdx, result_vector   ; Pointer to result vector

.loop:
    prefetcht0 [rsi + 64]    ; Prefetch next 8 doubles from vector1
    prefetcht0 [rdi + 64]    ; Prefetch next 8 doubles from vector2

    vmovapd ymm0, [rsi]      ; Load 4 doubles from vector1
    vmovapd ymm1, [rdi]      ; Load 4 doubles from vector2
    vsubpd ymm0, ymm0, ymm1  ; Compute x1 - x2 for each element

    vcmppd ymm2, ymm0, [zero], _CMP_LE_OQ ; Compare each element to zero (less or equal)
    vandnpd ymm0, ymm2, ymm0 ; Zero out elements where x1 - x2 <= 0

    vmovapd [rdx], ymm0      ; Store result in result_vector

    vmovapd ymm0, [rsi + 32] ; Load next 4 doubles from vector1
    vmovapd ymm1, [rdi + 32] ; Load next 4 doubles from vector2
    vsubpd ymm0, ymm0, ymm1  ; Compute x1 - x2 for next set of elements

    vcmppd ymm2, ymm0, [zero], _CMP_LE_OQ ; Compare each element to zero (less or equal)
    vandnpd ymm0, ymm2, ymm0 ; Zero out elements where x1 - x2 <= 0

    vmovapd [rdx + 32], ymm0 ; Store result in result_vector

    add rsi, 64              ; Move pointers to next 8 elements (64 bytes for 8 doubles)
    add rdi, 64
    add rdx, 64
    dec rcx                  ; Processed 8 elements, decrement loop counter
    jnz .loop

    ret

VECTOR_AND_OPTIMIZED:
    mov rcx, 2                ; Process 8 elements per iteration
    mov rsi, vector1          ; Pointer to vector1
    mov rdi, vector2          ; Pointer to vector2
    mov rdx, result_vector    ; Pointer to result vector

.loop:
    prefetcht0 [rsi + 64]     ; Prefetch next 8 doubles from vector1
    prefetcht0 [rdi + 64]     ; Prefetch next 8 doubles from vector2

    vmovapd ymm0, [rsi]       ; Load 4 doubles from vector1
    vmovapd ymm1, [rdi]       ; Load 4 doubles from vector2
    vminpd ymm0, ymm0, ymm1   ; Compute element-wise min (AND operation)
    vmovapd [rdx], ymm0       ; Store result in result_vector

    vmovapd ymm2, [rsi + 32]  ; Load next 4 doubles from vector1
    vmovapd ymm3, [rdi + 32]  ; Load next 4 doubles from vector2
    vminpd ymm2, ymm2, ymm3   ; Compute element-wise min (AND operation)
    vmovapd [rdx + 32], ymm2  ; Store result in result_vector

    add rsi, 64               ; Move pointers to next 8 elements (64 bytes for 8 doubles)
    add rdi, 64
    add rdx, 64
    dec rcx                   ; Processed 8 elements, decrement loop counter
    jnz .loop

    ret

; Fuzzy OR Routine
OR_ROUTINE:
    vmaxpd xmm0, xmm0, xmm1  ; Perform fuzzy OR using maximum value
    ret

XOR_ROUTINE:
    xorpd xmm0, xmm0          ; Initialize xmm0 to 0 for the max operation

.loop_over_rules:
    mov rax, rdx              ; rdx points to rule array
    movapd xmm1, [rax]        ; Load first input for this rule
    add rax, 8                ; Move to the next input in the rule

    mov rcx, rsi              ; rcx points to input array
.loop_over_inputs:
    movapd xmm2, [rcx]        ; Load next input
    minsd xmm1, xmm2          ; Calculate the min for the current rule
    add rcx, 8                ; Move to the next input
    dec rdi
    jnz .loop_over_inputs     ; Continue if there are more inputs

    maxsd xmm0, xmm1          ; Max of the current min and the overall max
    add rdx, 8                ; Move to the next rule
    dec rdi
    jnz .loop_over_rules      ; Continue if there are more rules

    ret

NOT_ROUTINE:
    movsd xmm1, [fuzzy_100]   ; Load 100 into xmm1
    subsd xmm1, xmm0          ; Subtract xmm0 from 100
    movapd xmm0, xmm1         ; Store the result back into xmm0
    ret

NAND_ROUTINE:
    vminpd xmm0, xmm0, xmm1   ; Perform fuzzy AND
    movsd xmm2, [fuzzy_100]   ; Load 100.0 into xmm2
    vsubpd xmm2, xmm2, xmm0   ; xmm2 = 100 - min(A, B)
    movapd xmm0, xmm2         ; Move result back to xmm0
    ret

NOR_ROUTINE:
    vmaxpd xmm0, xmm0, xmm1   ; Perform fuzzy OR
    movsd xmm2, [fuzzy_100]   ; Load 100.0 into xmm2
    vsubpd xmm2, xmm2, xmm0   ; xmm2 = 100 - max(A, B)
    movapd xmm0, xmm2         ; Move result back to xmm0
    ret

IF_ROUTINE:
    ucomisd xmm0, xmm1        ; Compare xmm0 and xmm1
    jp .if_false              ; Jump if parity (unordered)
    je .if_false              ; Jump if equal (zero flag set)
    movapd xmm0, xmm1         ; If true, move true result into xmm0
    jmp .end_if
.if_false:
    movapd xmm0, xmm2         ; If false, move false result into xmm0
.end_if:
    ret

IMPLICATION_ROUTINE:
    movsd xmm2, [fuzzy_100]   ; Load 100.0 into xmm2
    subsd xmm2, xmm0          ; xmm2 = 100 - A
    addsd xmm2, xmm1          ; xmm2 = 100 - A + B
    minsd xmm0, xmm2          ; xmm0 = min(100, 100 - A + B)
    ret

NIMPLY_ROUTINE:
    movapd xmm2, xmm1         ; Copy B into xmm2
    subsd xmm2, xmm0          ; Perform subtraction B - A
    movapd xmm0, xmm2         ; Move result back to xmm0
    ret

NULL_ROUTINE:
    xorpd xmm0, xmm0          ; Set xmm0 to 0.0
    ret

INHIBITION_ROUTINE:
    movsd xmm2, [fuzzy_100]   ; Load 100.0 into xmm2
    subsd xmm2, xmm1          ; xmm2 = 100 - B
    minsd xmm0, xmm2          ; xmm0 = min(A, 100 - B)
    ret

BUFFER_ROUTINE:
    ret                       ; No operation needed

INHIBITION_XY_ROUTINE:
    movsd xmm2, [fuzzy_100]   ; Load 100.0 into xmm2
    subsd xmm2, xmm0          ; xmm2 = 100 - A
    minsd xmm0, xmm1          ; xmm0 = min(100 - A, B)
    ret

EQUIVALENCE_ROUTINE:
    vminpd xmm2, xmm0, xmm1   ; xmm2 = min(A, B)
    movsd xmm4, [fuzzy_100]   ; Load 100.0 into xmm4
    vsubpd xmm4, xmm0         ; xmm4 = 100 - A
    movsd xmm5, [fuzzy_100]   ; Load 100.0 into xmm5
    vsubpd xmm5, xmm1         ; xmm5 = 100 - B
    vminpd xmm4, xmm4, xmm5   ; xmm4 = min(100 - A, 100 - B)
    vaddpd xmm0, xmm2, xmm4   ; xmm0 = min(A, B) + min(100 - A, 100 - B)
    ret

IDENTITY_ROUTINE:
    movsd xmm0, [fuzzy_100]   ; Load 100.0 into xmm0
    ret

LOGIC_HANDLER:
    cmp eax, '≈'
    je CMP_ROUTINE
    cmp eax, '⊕'
    je VECTOR_AND_OPTIMIZED_ROUTINE
    cmp eax, '∨'
    je OR_ROUTINE
    cmp eax, '⊕'
    je XOR_ROUTINE
    cmp eax, '¬''
    je NOT_ROUTINE
    cmp eax, '⊼'
    je NAND_ROUTINE
    cmp eax, '⊽'
    je NOR_ROUTINE
    cmp eax, '⇒'
    je IF_ROUTINE
    cmp eax, '⇔'
    je THEN_ROUTINE
    cmp eax, '∄'
    je ELSE_ROUTINE
    cmp eax, '⇒'
    je IMPLICATION_ROUTINE
    cmp eax, '⇏'
    je NIMPLY_ROUTINE
    cmp eax, '⊥'
    je NULL_ROUTINE
    cmp eax, '∤'
    je INHIBIT_XY_ROUTINE
    cmp eax, '↔'
    je BUFFER_ROUTINE
    cmp eax, '∄'
    je INHIBITION_ROUTINE
    cmp eax, '≡'
    je EQUIVALENCE_ROUTINE
    cmp eax, '&'
    je AND_ROUTINE
    cmp eax, '≃'
    je IDENTITY_ROUTINE
    ret

END_LOGIC_HANDLER:
    mov dword [MEM + 201], eax ; Store the result of logic operation
    ret

ADD_LOGIC_ERR_ROUTINE:
    ret
