; mth.asm math module for internal eprma use with woflang.

section .data
MATRIX_SIZE equ 4  ; Example for a variable matrix size, dynamically set later
VECTOR_LENGTH equ 1024  ; Example length of vectors
PI dq 3.14159265358979323846  ; Constant for FFT

; Change from single to double precision
PI dq 3.14159265358979323846264338327950288419716939937510


; Error Codes
ERR_MEM_ALLOC_FAIL equ 0x01
ERR_DIV_ZERO equ 0x02
ERR_UNDEFINED_MATRIX_SIZE equ 0x03

section .bss
matrix1 resd MATRIX_SIZE * MATRIX_SIZE  ; Matrix buffers
inverse_matrix resd MATRIX_SIZE * MATRIX_SIZE
determinant resd 1                      ; Determinant result storage
vector1 resd VECTOR_LENGTH              ; Vector buffers
vector2 resd VECTOR_LENGTH
result_vector resd VECTOR_LENGTH
fft_real resd VECTOR_LENGTH             ; FFT input/output buffers
fft_imag resd VECTOR_LENGTH

section .text
global ADD_ROUTINE
global SUB_ROUTINE
global MUL_ROUTINE
global DIV_ROUTINE
global ADD_VECTOR_ROUTINE
global SUB_VECTOR_ROUTINE
global DOT_PRODUCT_ROUTINE
global FFT_ROUTINE
global MATRIX_DETERMINANT_ROUTINE
global MATRIX_INVERSE_ROUTINE
global ALLOCATE_MEMORY
global FREE_MEMORY
global REPORT_ERROR
global MATRIX_DETERMINANT_3X3_ROUTINE

; Function to dynamically allocate memory
ALLOCATE_MEMORY:
    ; Inputs: eax = number of bytes to allocate
    ; Output: eax = pointer to allocated memory (or 0 on failure)
    ; Using mmap syscall (Linux)
    mov rdi, 0                    ; addr = NULL (system chooses address)
    mov rsi, rax                  ; size in rsi (already set in eax)
    mov rdx, 3                    ; prot = PROT_READ | PROT_WRITE
    mov r10, 0x22                 ; flags = MAP_PRIVATE | MAP_ANONYMOUS
    xor r8, r8                    ; fd = -1 (not backed by any file)
    xor r9, r9                    ; offset = 0
    mov eax, 9                    ; syscall number for mmap
    syscall
    test rax, rax                 ; Check if allocation failed
    js .alloc_fail
    ret

.alloc_fail:
    mov eax, ERR_MEM_ALLOC_FAIL   ; Set error code
    call REPORT_ERROR
    ret

; Function to free dynamically allocated memory
FREE_MEMORY:
    ; Inputs: eax = pointer to memory to free
    ; Output: None
    ; Using munmap syscall (Linux)
    mov edi, eax                  ; Move pointer to edi
    mov eax, 11                   ; syscall number for munmap
    mov esi, 0                    ; size to free (assumed size known elsewhere)
    syscall
    ret

; ADD Routine using SIMD (AVX)
ADD_ROUTINE:
    ; Input: xmm0 = first operand, xmm1 = second operand
    ; Output: xmm0 = result (xmm0 + xmm1)
    addsd xmm0, xmm1        ; Perform addition on double-precision floats
    ret

.add_loop:
    vmovaps ymm0, [rsi]           ; Load 8 floats from vector1
    vmovaps ymm1, [rdi]           ; Load 8 floats from vector2
    vaddps ymm0, ymm0, ymm1       ; Add vectors
    vmovaps [rdx], ymm0           ; Store result
    add rsi, 32                   ; Move pointers to next 8 elements (32 bytes)
    add rdi, 32
    add rdx, 32
    dec r8
    jnz .add_loop
    vzeroupper                    ; Clear upper bits of YMM registers
    ret

; SUB Routine using SIMD (AVX)
SUB_ROUTINE:
    ; Input: xmm0 = first operand, xmm1 = second operand
    ; Output: xmm0 = result (xmm0 - xmm1)
    subsd xmm0, xmm1        ; Perform subtraction on double-precision floats
    ret

.sub_loop:
    vmovaps ymm0, [rsi]           ; Load 8 floats from vector1
    vmovaps ymm1, [rdi]           ; Load 8 floats from vector2
    vsubps ymm0, ymm0, ymm1       ; Subtract vectors
    vmovaps [rdx], ymm0           ; Store result
    add rsi, 32                   ; Move pointers to next 8 elements (32 bytes)
    add rdi, 32
    add rdx, 32
    dec r8
    jnz .sub_loop
    vzeroupper                    ; Clear upper bits of YMM registers
    ret

; MUL Routine using SIMD (AVX)
MUL_ROUTINE:
    ; Inputs: rsi = pointer to vector1, rdi = pointer to vector2, rdx = pointer to result vector, rcx = length
    mov r8, rcx                   ; r8 = length (number of elements)
    shr r8, 3                     ; Divide length by 8 to process 8 elements at a time

.mul_loop:
    vmovaps ymm0, [rsi]           ; Load 8 floats from vector1
    vmovaps ymm1, [rdi]           ; Load 8 floats from vector2
    vmulps ymm0, ymm0, ymm1       ; Multiply vectors
    vmovaps [rdx], ymm0           ; Store result
    add rsi, 32                   ; Move pointers to next 8 elements (32 bytes)
    add rdi, 32
    add rdx, 32
    dec r8
    jnz .mul_loop
    vzeroupper                    ; Clear upper bits of YMM registers
    ret

; DIV Routine using SIMD (AVX) with error handling
DIV_ROUTINE:
    ; Inputs: rsi = pointer to vector1, rdi = pointer to vector2, rdx = pointer to result vector, rcx = length
    mov r8, rcx                   ; r8 = length (number of elements)
    shr r8, 3                     ; Divide length by 8 to process 8 elements at a time

.div_loop:
    vmovaps ymm0, [rsi]           ; Load 8 floats from vector1
    vmovaps ymm1, [rdi]           ; Load 8 floats from vector2
    vcmpeqps ymm2, ymm1, ymm1     ; Compare divisor to itself (check for zero)
    vblendvps ymm3, ymm1, ymm0, ymm2  ; Blend zero elements from divisor into a safe value
    vdivps ymm0, ymm0, ymm3       ; Divide vectors
    vmovaps [rdx], ymm0           ; Store result
    add rsi, 32                   ; Move pointers to next 8 elements (32 bytes)
    add rdi, 32
    add rdx, 32
    dec r8
    jnz .div_loop
    vzeroupper                    ; Clear upper bits of YMM registers
    ret

; Vector Addition Routine using SIMD (AVX)
; Input: esi = pointer to vector1, edi = pointer to vector2, ebx = pointer to result vector
ADD_VECTOR_ROUTINE:
    mov ecx, VECTOR_LENGTH
    xor eax, eax             ; Index

.vector_add_loop:
    vmovupd xmm0, [esi + eax * 8] ; Load double-precision elements from vector1
    vaddpd xmm0, xmm0, [edi + eax * 8] ; Add corresponding double-precision elements from vector2
    vmovupd [ebx + eax * 8], xmm0 ; Store result in result_vector
    add eax, 4              ; Move to next set of elements
    loop .vector_add_loop    ; Repeat for all elements
;  call ADD_ROUTINE              ; Reuse SIMD ADD routine

    ret

; Vector Subtraction Routine using SIMD (AVX)
SUB_VECTOR_ROUTINE:
    call SUB_ROUTINE              ; Reuse SIMD SUB routine
    ret

; Dot Product Routine using SIMD (AVX)
DOT_PRODUCT_ROUTINE:
    ; Inputs: rsi = pointer to vector1, rdi = pointer to vector2, rcx = length
    ; Output: xmm0 = dot product result
    mov r8, rcx                   ; r8 = length (number of elements)
    shr r8, 3                     ; Divide length by 8 to process 8 elements at a time
    vxorps ymm0, ymm0, ymm0       ; Clear ymm0 for accumulation

.dot_product_loop:
    vmovaps ymm1, [rsi]           ; Load 8 floats from vector1
    vmovaps ymm2, [rdi]           ; Load 8 floats from vector2
    vmulps ymm1, ymm1, ymm2       ; Multiply vectors
    vaddps ymm0, ymm0, ymm1       ; Accumulate result
    add rsi, 32                   ; Move pointers to next 8 elements (32 bytes)
    add rdi, 32
    dec r8
    jnz .dot_product_loop

    vhaddps ymm0, ymm0, ymm0      ; Horizontal add to sum all elements
    vhaddps ymm0, ymm0, ymm0
    vhaddps ymm0, ymm0, ymm0
    vmovss xmm0, xmm0, xmm0       ; Move result to lower part of xmm0
    vzeroupper                    ; Clear upper bits of YMM registers
    ret



; 3x3 Matrix Determinant Routine
MATRIX_DETERMINANT_3X3_ROUTINE:
    ; Calculate the determinant of a 3x3 matrix
    ; |a b c|
    ; |d e f|
    ; |g h i|
    ; Matrix stored in row-major order in memory pointed to by ESI

    mov esi, matrix1         ; ESI points to the start of the matrix
    mov eax, [esi]           ; eax = a
    imul eax, [esi + 8*4]    ; eax = a * (e * i - f * h)
    imul edx, [esi + 4*4]    ; edx = e * i
    mov ecx, [esi + 5*4]     ; ecx = f
    imul ecx, [esi + 7*4]    ; ecx = f * h
    sub edx, ecx             ; edx = (e * i - f * h)
    imul eax, edx            ; eax = a * (e * i - f * h)

    mov ebx, [esi + 1*4]     ; ebx = b
    imul ebx, [esi + 6*4]    ; ebx = b * (f * g - d * i)
    mov edx, [esi + 5*4]     ; edx = f
    imul edx, [esi + 6*4]    ; edx = f * g
    mov ecx, [esi + 3*4]     ; ecx = d
    imul ecx, [esi + 8*4]    ; ecx = d * i
    sub edx, ecx             ; edx = (f * g - d * i)
    imul ebx, edx            ; ebx = b * (f * g - d * i)

    sub eax, ebx             ; eax = a * (e * i - f * h) - b * (f * g - d * i)

    mov ecx, [esi + 2*4]     ; ecx = c
    imul ecx, [esi + 3*4]    ; ecx = c * (d * h - e * g)
    mov edx, [esi + 3*4]     ; edx = d
    imul edx, [esi + 7*4]    ; edx = d * h
    mov ebx, [esi + 4*4]     ; ebx = e
    imul ebx, [esi + 6*4]    ; ebx = e * g
    sub edx, ebx             ; edx = (d * h - e * g)
    imul ecx, edx            ; ecx = c * (d * h - e * g)

    add eax, ecx             ; eax = determinant of the matrix
    mov [determinant], eax   ; Store the determinant

    ret

; General Matrix Determinant Calculation Routine (Using Recursion)

; Matrix Determinant Routine with error handling
MATRIX_DETERMINANT_ROUTINE:
    ; Inputs: eax = pointer to matrix, ecx = matrix size
    ; Output: eax = determinant
    ; Error handling: Check if matrix size is valid (non-zero)
    test ecx, ecx
    jz .error_matrix_size

    ; Determinant calculation logic here

    ret

.error_matrix_size:
    mov eax, ERR_UNDEFINED_MATRIX_SIZE
    call REPORT_ERROR
    ret

; Matrix Inversion Routine using Gaussian Elimination with error handling
MATRIX_INVERSE_ROUTINE:
    push rbp
    mov rbp, rsp
    push rbx
    push rsi
    push rdi

    ; Check if matrix is invertible (non-zero determinant)
    ; Perform Gaussian elimination logic

    pop rdi
    pop rsi
    pop rbx
    pop rbp
    ret

    ; Inputs: eax = pointer to matrix, ecx = matrix size
    ; Output: eax = determinant
    push ebp
    mov ebp, esp
    push ebx
    push esi
    push edi

    cmp ecx, 2               ; Base case for 2x2 matrix
    je .base_case_2x2

    mov esi, eax             ; esi = matrix pointer
    mov edx, 0               ; edx = determinant accumulator

    xor edi, edi             ; edi = current row (starts at 0)
.det_loop:
    cmp edi, ecx             ; Check if all rows have been processed
    jge .det_done

    ; Calculate the minor matrix for the current element
    mov eax, esi
    add eax, edi
    call MATRIX_CALC_MINOR   ; Compute minor for element (0, edi)

    ; Calculate the determinant recursively
    mov eax, [ebp-4]         ; Load minor determinant
    imul eax, [esi + edi*4]  ; Multiply by the matrix element
    test edi, 1              ; Check if this term should be negated
    jz .no_negate
    neg eax
.no_negate:
    add edx, eax             ; Add/subtract to determinant accumulator

    inc edi
    jmp .det_loop

.det_done:
    mov eax, edx             ; Move determinant to eax
    jmp .det_finish

.base_case_2x2:
    mov esi, [eax]           ; esi = a
    mov edi, [eax + 4]       ; edi = b
    mov ebx, [eax + 8]       ; ebx = c
    mov ecx, [eax + 12]      ; ecx = d
    imul esi, ecx            ; a * d
    imul edi, ebx            ; b * c
    sub esi, edi             ; (a * d) - (b * c)
    mov eax, esi             ; Result in eax

.det_finish:
    pop edi
    pop esi
    pop ebx
    pop ebp
    ret

; Helper Function to Calculate Minor Matrix (for MATRIX_DETERMINANT_ROUTINE)
MATRIX_CALC_MINOR:
    ; Inputs: eax = pointer to matrix, ecx = matrix size, edx = row to exclude, ebx = column to exclude
    ; Output: eax = pointer to minor matrix
    ; Allocate memory for the minor matrix
    dec ecx                  ; Size of minor matrix is one less than original
    mov eax, ecx
    imul eax, ecx
    shl eax, 2               ; Multiply by 4 (size of each element)
    call ALLOCATE_MEMORY     ; Allocate memory for minor matrix
    test eax, eax
    jz .minor_alloc_fail     ; If allocation fails, handle error

    ; Copy the remaining matrix elements to the minor matrix
    ; Exclude the specified row and column
    ; Implement logic to copy matrix elements here

    ret

.minor_alloc_fail:
    mov eax, ERR_MEM_ALLOC_FAIL
    call REPORT_ERROR
    ret

; Error reporting function
REPORT_ERROR:
    ; Error handling logic here
    ; Print error message and terminate program or handle error as needed
    ret

; FFT Routine using SIMD (AVX)
FFT_ROUTINE:
    ; FFT computation logic using SIMD
    ; Use vectorized butterfly operations for performance
    ; Add error handling if needed

    ret

; Error reporting function
REPORT_ERROR:
    ; Error handling logic here
    ; Print error message and terminate program or handle error as needed
    ret
