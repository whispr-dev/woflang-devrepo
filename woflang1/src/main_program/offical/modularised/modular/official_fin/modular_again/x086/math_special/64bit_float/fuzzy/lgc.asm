; `lgc.asm` Logic Module in x86 assembly 64bit float

section .data
; If there are any floating-point constants or buffers, they should be defined as `dq`.
; Example floating-point constant
some_logic_constant dq 2.7182818284590452353602874713527
fuzzy_100 dq 100.0      ; Define a double-precision float constant representing 100
zero dq 0.0               ; Define a double-precision float representing 0
one dq 1.0                ; Define a double-precision float representing 1
fuzzy_50 dq 50.0          ; Define a double-precision float representing 50
fuzzy_zero dq 0.0            ; Constant for zero, used for comparison
output dq 0.0                ; Variable to store the output result
align 32
vector1 dq 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0   ; Aligned array
vector2 dq 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0, 0.0   ; Aligned array
zero dq 0.0

section .text

global AND_ROUTINE
global OR_ROUTINE
global XOR_ROUTINE
global NOT_ROUTINE
global NAND_ROUTINE
global NOR_ROUTINE
global IF_ROUTINE
global THEN_ROUTINE
global ELSE_ROUTINE
global IMPLY_ROUTINE
gobal  NIMPLY_ROUTINE
global NULL_ROUTINE
global INHIBITION_ROUTINE
global BUFFER_ROUTINE
global INHIBITION_XY_ROUTINE
global EQUIVALENCE_ROUTINE
global NOT_ROUTINE
global IMPLICATION_ROUTINE
global NAND_ROUTINE
global IDENTITY_ROUTINE
global LOGIC_HANDLER
global ADD_LOGIC_ERR_ROUTINE
global CMP_ROUTINE
global VECTOR_AND_ROUTINE

; Convert binary to fuzzy logic (0 or 1 to 0 or 100)
BINARY_TO_FUZZY:
    ; Input: xmm0 = binary operand (0.0 or 1.0)
    ; Output: xmm0 = fuzzy operand (0.0 or 100.0)
    ucomisd xmm0, [zero]
    jne .is_one               ; If xmm0 is not zero, it's one
    jmp .is_zero

.is_one:
    movsd xmm0, [fuzzy_100]   ; Set xmm0 to 100
    ret

.is_zero:
    movsd xmm0, [zero]        ; Set xmm0 to 0
    ret

; Convert fuzzy logic to binary (0-100 to 0 or 1)
FUZZY_TO_BINARY:
    ; Input: xmm0 = fuzzy operand (0-100)
    ; Output: xmm0 = binary operand (0.0 or 1.0)
    movsd xmm1, [fuzzy_50]    ; Load 50 into xmm1
    ucomisd xmm0, xmm1        ; Compare xmm0 to 50
    jae .is_one               ; If xmm0 >= 50, consider it 1 (true)
    movsd xmm0, [zero]        ; Set xmm0 to 0 (false)
    ret

.is_one:
    movsd xmm0, [one]         ; Set xmm0 to 1 (true)
    ret

;  Modify comparisons to work with double-precision

; CMP_ROUTINE:
    ; Input: xmm0 = x1 (input 1), xmm1 = x2 (input 2)
    ; Output: xmm0 = max(0, x1 - x2)
    ; Step 1: Compute the difference (x1 - x2)
;     subsd xmm0, xmm1              ; xmm0 = x1 - x2
    ; Step 2: Check if the difference is positive
    ; Compare xmm0 with zero to check if it's greater than zero
;     movsd xmm2, [fuzzy_zero]      ; Load 0.0 into xmm2 for comparison
;     ucomisd xmm0, xmm2            ; Compare xmm0 (x1 - x2) with 0.0
    ; Step 3: Conditional check to set output only if positive
;     jbe .negative_difference      ; Jump if xmm0 <= 0 (less or equal)
    ; Positive difference, so keep xmm0 as it is
;     jmp .set_output
;     jp .error_routine     ; Jump to error handling if unordered (NaN involved)

CMP_ROUTINE:
    mov rcx, vector_length    ; rcx = length of vector (assumed to be a multiple of 4)
    mov rsi, vector1          ; rsi = pointer to vector1
    mov rdi, vector2          ; rdi = pointer to vector2
    mov rdx, result_vector    ; rdx = pointer to result vector

.loop:
    vmovapd ymm0, [rsi]       ; Load 4 doubles from vector1
    vmovapd ymm1, [rdi]       ; Load 4 doubles from vector2
    vsubpd ymm0, ymm0, ymm1   ; Compute x1 - x2 for each element

    ; Perform comparison and set to zero if result is negative or zero
    vcmppd ymm2, ymm0, [fuzzy_zero], _CMP_LE_OQ ; Compare each element to zero (less or equal)
    vandnpd ymm0, ymm2, ymm0  ; Zero out elements where x1 - x2 <= 0

    vmovapd [rdx], ymm0       ; Store result in result_vector

    add rsi, 32               ; Move to next 4 elements (32 bytes for 4 doubles)
    add rdi, 32
    add rdx, 32
    sub rcx, 4                ; Processed 4 elements, decrement by 4
    jnz .loop

    ret

.negative_difference:
    ; If negative or zero, set xmm0 to 0 (ignoring the negative result)
    movapd xmm0, xmm2             ; xmm0 = 0.0 (fuzzy zero)

.set_output:
    ; Store the result in the output variable if needed
    movsd [output], xmm0          ; Store the result in memory

    ret                           ; Return from the routine

; CMP_ROUTINE:
;     movsd xmm0, [rdi]     ; Load first double-precision float
;     movsd xmm1, [rsi]     ; Load second double-precision float
;     comisd xmm0, xmm1     ; Compare double-precision floats in xmm0 and xmm1
;     jp .error_routine     ; Jump to error handling if unordered (NaN involved)
;     je .equal             ; Jump if equal
;     jb .less              ; Jump if below
;     ja .greater           ; Jump if above

    ret
.error_routine:
    mov eax, ERR_FP_INVALID       ; Error code for invalid floating-point operation
    call REPORT_ERROR
    ret

; .equal:
;     ; Handle equal case
;     ret

; .less:
;     ; Handle less-than case
;     ret

; .greater:
;     ; Handle greater-than case
;     ret

; Vector AND Routine with Prefetching
VECTOR_AND_OPTIMIZED:
    mov rcx, 8                 ; rcx = length of vector (multiple of 4)
    mov rsi, vector1           ; rsi = pointer to vector1
    mov rdi, vector2           ; rdi = pointer to vector2
    mov rdx, result_vector     ; rdx = pointer to result vector

.loop:
    prefetcht0 [rsi + 64]      ; Prefetch next 8 doubles from vector1
    prefetcht0 [rdi + 64]      ; Prefetch next 8 doubles from vector2

    vmovapd ymm0, [rsi]        ; Load 4 doubles from vector1
    vmovapd ymm1, [rdi]        ; Load 4 doubles from vector2
    vminpd ymm0, ymm0, ymm1    ; Compute element-wise min (AND operation)
    vmovapd [rdx], ymm0        ; Store result in result_vector

    vmovapd ymm2, [rsi + 32]   ; Load next 4 doubles from vector1
    vmovapd ymm3, [rdi + 32]   ; Load next 4 doubles from vector2
    vminpd ymm2, ymm2, ymm3    ; Compute element-wise min (AND operation)
    vmovapd [rdx + 32], ymm2   ; Store result in result_vector

    add rsi, 64                ; Move pointers to next 8 elements (64 bytes for 8 doubles)
    add rdi, 64
    add rdx, 64
    sub rcx, 2                 ; Processed 8 elements, decrement by 2
    jnz .loop

    ret

; Fuzzy OR Routine
OR_ROUTINE:
    ; Input: xmm0 = first operand (0-100), xmm1 = second operand (0-100)
    ; Output: xmm0 = result (max(xmm0, xmm1))
    maxsd xmm0, xmm1        ; Perform fuzzy OR using maximum value
    ret

; Fuzzy XOR Routine (Scalar 64-bit Floating Point)
; XOR_ROUTINE BASED ON GPT MATH:
;     ; Input: xmm0 = first operand (a), xmm1 = second operand (b)
;     ; Output: xmm0 = result (fuzzy XOR operation)
; 
;    ; Load constants
;     movsd xmm2, [fuzzy_100]   ; Load 100 into xmm2
; 
;     ; Calculate (100 - xmm1) -> xmm3
;     movapd xmm3, xmm2         ; xmm3 = 100.0
;     subsd xmm3, xmm1          ; xmm3 = 100 - xmm1
; 
;     ; Calculate xmm0 * (100 - xmm1) -> xmm4
;     movapd xmm4, xmm0         ; xmm4 = xmm0
;     mulsd xmm4, xmm3          ; xmm4 = xmm0 * (100 - xmm1)
; 
;     ; Calculate (100 - xmm0) -> xmm3
;     movapd xmm3, xmm2         ; xmm3 = 100.0
;     subsd xmm3, xmm0          ; xmm3 = 100 - xmm0
; 
;     ; Calculate xmm1 * (100 - xmm0) -> xmm5
;     movapd xmm5, xmm1         ; xmm5 = xmm1
;     mulsd xmm5, xmm3          ; xmm5 = xmm1 * (100 - xmm0)
; 
;     ; Add the two results: xmm4 + xmm5
;     addsd xmm4, xmm5          ; xmm4 = (xmm0 * (100 - xmm1)) + (xmm1 * (100 - xmm0))
; 
;     ; Divide by 100 to get the final result
;     divsd xmm4, xmm2          ; xmm4 = xmm4 / 100.0
; 
;     ; Move result back to xmm0
;     movapd xmm0, xmm4         ; Result is now in xmm0
; 
;     ret

; Fuzzy XOR Routine using min and max for fuzzy rule-based evaluation
; This code assumes inputs are stored in a register array or similar structure

XOR_ROUTINE:    ; based on my notes - look to find otu more...
    ; Input: rdi = number of rules (r), rsi = pointer to input array, rdx = pointer to rule array
    ; Output: xmm0 = analogue XOR result on a 0-100 scale

    ; Initialize xmm0 to 0 for the max operation
    xorpd xmm0, xmm0

.loop_over_rules:
    ; Assuming rdi holds the count of rules and we loop through them
    ; Load initial min value for this rule (e.g., from rule array)
    mov rax, rdx             ; rdx points to rule array
    movapd xmm1, [rax]       ; Load first input for this rule
    add rax, 8               ; Move to the next input in the rule

    ; Loop over each input for this rule to calculate the min
    mov rcx, rsi             ; rcx points to input array
.loop_over_inputs:
    movapd xmm2, [rcx]       ; Load next input
    minsd xmm1, xmm2         ; Calculate the min for the current rule
    add rcx, 8               ; Move to the next input
    dec rdi
    jnz .loop_over_inputs    ; Continue if there are more inputs

    ; Calculate the max across all rules
    maxsd xmm0, xmm1         ; Max of the current min and the overall max
    add rdx, 8               ; Move to the next rule
    dec rdi
    jnz .loop_over_rules     ; Continue if there are more rules

    ret

; Fuzzy NOT Routine (Scalar 64-bit Floating Point)
NOT_ROUTINE:
    ; Input: xmm0 = operand (0-100)
    ; Output: xmm0 = result (100 - xmm0)
    movsd xmm1, [fuzzy_100] ; Load 100 into xmm1
    subsd xmm1, xmm0        ; Subtract xmm0 from 100
    movsd xmm0, xmm1        ; Store the result back into xmm0
    ret

; NAND Routine
; NAND_ROUTINE:
;    ; Input: edx = first operand, ecx = second operand
;     ; Output: eax = result (NOT (edx AND ecx))
;     mov eax, edx        ; Load first operand into eax
;     and eax, ecx        ; Perform AND operation
;     not eax             ; Perform NOT on the result
;     ret

NAND_ROUTINE:
    ; Input: xmm0 = A, xmm1 = B
    ; Output: xmm0 = 100 - min(A, B)
    minsd xmm0, xmm1        ; Perform fuzzy AND
    movsd xmm2, [fuzzy_100] ; Load 100.0 into xmm2
    subsd xmm2, xmm0        ; xmm2 = 100 - min(A, B)
    movapd xmm0, xmm2       ; Move result back to xmm0
    ret

; NOR Routine
; NOR_ROUTINE:
;     ; Input: edx = first operand, ecx = second operand
;     ; Output: eax = result (NOT (edx OR ecx))
;     mov eax, edx        ; Load first operand into eax
;     or eax, ecx         ; Perform OR operation
;     not eax             ; Perform NOT on the result
;     ret

NOR_ROUTINE:
    ; Input: xmm0 = A, xmm1 = B
    ; Output: xmm0 = 100 - max(A, B)
    maxsd xmm0, xmm1        ; Perform fuzzy OR
    movsd xmm2, [fuzzy_100] ; Load 100.0 into xmm2
    subsd xmm2, xmm0        ; xmm2 = 100 - max(A, B)
    movapd xmm0, xmm2       ; Move result back to xmm0
    ret

; IF Routine (Basic conditional check)
IF_ROUTINE:
    ; Input: xmm0 = condition, xmm1 = result if true, xmm2 = result if false
    ; Output: xmm0 = result based on condition
    ucomisd xmm0, xmm1       ; Compare xmm0 and xmm1
    jp .if_false             ; Jump if parity (unordered)
    je .if_false             ; Jump if equal (zero flag set)
    movapd xmm0, xmm1        ; If true, move true result into xmm0
    jmp .end_if
.if_false:
    movapd xmm0, xmm2        ; If false, move false result into xmm0
.end_if:
    ret

; THEN Routine (Placeholder)
THEN_ROUTINE:
    ; Logic for THEN operation would be here
    ret

; ELSE Routine (Placeholder)
ELSE_ROUTINE:
    ; Logic for ELSE operation would be here
    ret

; Fuzzy Imply Routine (Scalar 64-bit Floating Point)
; IMPLY_ROUTINE:
;     ; Input: xmm0 = A (first operand), xmm1 = B (second operand)
;     ; Output: xmm0 = result (A - B)
; 
;     subsd xmm0, xmm1          ; Perform subtraction A - B
;     ret                       ; Return with result in xmm0

IMPLICATION_ROUTINE:
    ; Input: xmm0 = A, xmm1 = B
    ; Output: xmm0 = min(100, 100 - A + B)
    movsd xmm2, [fuzzy_100] ; Load 100.0 into xmm2
    subsd xmm2, xmm0        ; xmm2 = 100 - A
    addsd xmm2, xmm1        ; xmm2 = 100 - A + B
    minsd xmm0, xmm2        ; xmm0 = min(100, 100 - A + B)
    ret

; Fuzzy Nimply Routine (Scalar 64-bit Floating Point)
NIMPLY_ROUTINE:
    ; Input: xmm0 = A (first operand), xmm1 = B (second operand)
    ; Output: xmm0 = result (B - A)

    movapd xmm2, xmm1         ; Copy B into xmm2
    subsd xmm2, xmm0          ; Perform subtraction B - A
    movapd xmm0, xmm2         ; Move result back to xmm0
    ret                       ; Return with result in xmm0

NULL_ROUTINE:
    ; Output: xmm0 = 0
    xorpd xmm0, xmm0        ; Set xmm0 to 0.0
    ret

INHIBITION_ROUTINE:
    ; Input: xmm0 = A, xmm1 = B
    ; Output: xmm0 = min(A, 100 - B)
    movsd xmm2, [fuzzy_100] ; Load 100.0 into xmm2
    subsd xmm2, xmm1        ; xmm2 = 100 - B
    minsd xmm0, xmm2        ; xmm0 = min(A, 100 - B)
    ret

BUFFER_ROUTINE:
    ; Input: xmm0 = A
    ; Output: xmm0 = A
    ret                     ; No operation needed

INHIBITION_XY_ROUTINE:
    ; Input: xmm0 = A, xmm1 = B
    ; Output: xmm0 = min(100 - A, B)
    movsd xmm2, [fuzzy_100] ; Load 100.0 into xmm2
    subsd xmm2, xmm0        ; xmm2 = 100 - A
    minsd xmm0, xmm1        ; xmm0 = min(100 - A, B)
    ret

EQUIVALENCE_ROUTINE:
    ; Input: xmm0 = A, xmm1 = B
    ; Output: xmm0 = min(A, B) + min(100 - A, 100 - B)
    minsd xmm2, xmm0        ; xmm2 = min(A, B)
    minsd xmm3, xmm1        ; xmm3 = min(A, B)

    movsd xmm4, [fuzzy_100] ; Load 100.0 into xmm4
    subsd xmm4, xmm0        ; xmm4 = 100 - A

    movsd xmm5, [fuzzy_100] ; Load 100.0 into xmm5
    subsd xmm5, xmm1        ; xmm5 = 100 - B

    minsd xmm4, xmm5        ; xmm4 = min(100 - A, 100 - B)
    addsd xmm0, xmm4        ; xmm0 = min(A, B) + min(100 - A, 100 - B)
    ret

IDENTITY_ROUTINE:
    ; Output: xmm0 = 100
    movsd xmm0, [fuzzy_100] ; Load 100.0 into xmm0
    ret

; Logic Handler Routine (Control flow for different logic operations)
LOGIC_HANDLER:
    ; This routine will handle the dispatching of logic operations
    ; Assumes R49 (now eax) contains the opcode or operation identifier
    cmp eax, '⽠'        ; Check if command is CMP
    je CMP_ROUTINE
    cmp eax, '而'          ; Check if command is MIN (AND)
    je AND_ROUTINE
    cmp eax, '或'          ; Check if command is MAX (OR)
    je OR_ROUTINE
    cmp eax, '⊕'           ; Check if command is XOR
    je XOR_ROUTINE
    cmp eax, '无'          ; Check if command is NOT
    je NOT_ROUTINE
    cmp eax, '无‍而'       ; Check if command is NAND
    je NAND_ROUTINE
    cmp eax, '无‍或'       ; Check if command is NOR
    je NOR_ROUTINE
    cmp eax, '若'          ; Check if command is IF
    je IF_ROUTINE
    cmp eax, '则'          ; Check if command is THEN
    je THEN_ROUTINE
    cmp eax, '?'           ; Check if command is ELSE
    je ELSE_ROUTINE
    cmp eax, '⽫',		; Check if command is  imply
    je IMPLY_ROUTINE
    cmp eax, '⽬',		; Check if command is  nimply
    je NIMPLY_ROUTINE
    cmp eax, '⽊',      ; Check if command is  null
    je NULL_ROUTINE
    cmp eax, '⽥',      ; Check if command is  inhibit_xy
    je INHIBIT_XY_ROUTINE
    cmp eax, '⽱',      ; Check if command is  buffer
    je BUFFER_ROUTINE
    cmp eax, '⽾',      ; Check if command is  inhibit
    je INHIB IT_ROUTINE
    cmp eax, '⽺',      ; Check if command is  equiv
    je EQUIV_ROUTINE
    cmp eax, '⽽',      ; Check if command is  and
    je AND_ROUTINE
    cmp eax, '⽲'      ; Check if command is  identity
    je IDENTITY_ROUTINE

    ret

END_LOGIC_HANDLER:
    ; Assume eax has the final result
    mov dword [MEM + 201], eax ; Store the result of logic operation
    ret                        ; Return to main execution

ADD_LOGIC_ERR_ROUTINE:
    ; Placeholder for error handling logic
    ; Implementation depends on your specific needs
    ret
