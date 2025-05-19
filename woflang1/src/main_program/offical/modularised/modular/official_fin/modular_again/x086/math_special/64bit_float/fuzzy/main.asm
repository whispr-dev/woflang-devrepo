; `lgc.asm` logic module for woflang x086 assembly 64bit float

section .data
    CREATE_THREAD_CMD db 'CREATE_THREAD'
    JOIN_THREAD_CMD   db 'JOIN_THREAD'
    LOCK_CMD          db 'LOCK'
    UNLOCK_CMD        db 'UNLOCK'
    TCB_BASE_ADDR     dd 0x1000        ; Base address for Thread Control Blocks (TCBs)
    TCB_SIZE          dd 64            ; Size of each TCB
    MAX_THREADS       dd 4             ; Maximum number of threads
    CURRENT_THREAD_ID dd 0             ; ID of the current running thread
    ; Convert any single-precision floating-point constants to double-precision.
    float_constant dq 3.14159265358979323846264338327950288419716939937510
    ; For example, if you have a buffer for floating-point operations:
    buffer dq 0.0, 0.0, 0.0, 0.0  ; Change to double-precision (dq)
    MODULE_TABLE_BASE dd 0x2000  ; Base address for module function table
    MODULE_COUNT      dd 0        ; Number of loaded modules

section .bss
    command resb 100  ; Space for the command string

section .text
global _start, MAIN_ROUTINE, INITIALIZATION


_start:
    ; Initialize registers
    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx
    xor esi, esi
    xor edi, edi
    mov ebp, esp     ; Base pointer setup

    ; Initialize line number tracking
    mov dword [current_line], 1

main_execution_loop:
    ; Read commands and execute corresponding routines
    ; This would typically be a call to some I/O routine to get a command into `command`
    call read_command
    call parse_command
    jmp execute_command

parse_command:
    ; Check command strings and set up for the appropriate function call
    ; Use 'scasb' and other string instructions to parse input commands
    ; Assume the command is loaded in `esi`

    lea esi, [command]
    lodsb                ; Load the first byte into AL

    cmp al, 'ADD'
    je call_mth_add
    cmp al, 'AND'
    je call_lgc_and
    cmp al, 'CONCAT'
    je call_str_concat
    cmp al, 'PRINT'
    je call_str_print
    ; Check for plugin commands
    call check_module_command
    jnz execute_module_command
    ; Threading Commands
    lea esi, [create_thread_cmd]
    repe cmpsb
    je create_thread_routine
    lea esi, [join_thread_cmd]
    repe cmpsb
    je join_thread_routine
    lea esi, [lock_cmd]
    repe cmpsb
    je lock_mutex
    lea esi, [unlock_cmd]
    repe cmpsb
    je unlock_mutex
    ; Continue for other commands ...

    ret

execute_command:
    ; Implement the appropriate logic to call functions based on parsed command
    ; Placeholder for now
    ret

create_thread_routine:
    ; Input: ESI = address of function to run, EDX = stack size
    ; Output: EAX = thread ID (or -1 if failed)

    ; Find a free TCB slot
    mov ebx, TCB_BASE_ADDR
    xor ecx, ecx  ; Start with the first thread slot
find_free_tcb:
    cmp dword [ebx + ecx * TCB_SIZE + 0x003C], 3  ; Check if thread state is terminated
    je create_thread_init
    inc ecx
    cmp ecx, MAX_THREADS
    jge thread_creation_failed
    jmp find_free_tcb

create_thread_init:
    ; Initialize TCB for the new thread
    mov [ebx + ecx * TCB_SIZE + 0x0000], ecx  ; Thread ID
    mov [ebx + ecx * TCB_SIZE + 0x0004], edx  ; Stack Pointer (SP)
    mov [ebx + ecx * TCB_SIZE + 0x003C], 1    ; Set state to Ready

    ; Initialize stack and registers (EAX-EDX, ESI, EDI to 0)
    xor eax, eax
    mov edi, [ebx + ecx * TCB_SIZE + 0x0004]  ; SP
    mov [edi], eax
    ; Continue initializing more stack frames/registers as needed

    ; Set the entry point for the thread function
    mov [ebx + ecx * TCB_SIZE + 0x0008], esi  ; Base Pointer (BP)

    mov eax, ecx  ; Return the thread ID
    ret

thread_creation_failed:
    mov eax, -1  ; Indicate failure
    ret

join_thread_routine:
    ; Input: EAX = thread ID to join
    ; Wait until the specified thread is terminated

    mov ebx, TCB_BASE_ADDR
    mul ecx, eax, TCB_SIZE  ; Calculate TCB address for thread ID
wait_for_thread:
    cmp dword [ebx + ecx + 0x003C], 3  ; Check if thread state is terminated
    je thread_joined
    ; Wait for the thread to terminate (busy wait or implement sleep mechanism)
    jmp wait_for_thread

thread_joined:
    ret

context_switch_routine:
    ; Save current thread context
    mov eax, [CURRENT_THREAD_ID]
    mov ebx, TCB_BASE_ADDR
    mul ecx, eax, TCB_SIZE  ; Calculate TCB address for current thread
    ; Save SP and registers (EAX-EDX, ESI, EDI)
    mov [ebx + ecx + 0x0004], esp  ; Save SP
    mov [ebx + ecx + 0x0008], ebp  ; Save BP
    ; Save all general-purpose registers
    mov [ebx + ecx + 0x000C], eax
    mov [ebx + ecx + 0x0010], ebx
    mov [ebx + ecx + 0x0014], ecx
    mov [ebx + ecx + 0x0018], edx
    mov [ebx + ecx + 0x001C], esi
    mov [ebx + ecx + 0x0020], edi

    ; Find next runnable thread
    inc eax
    cmp eax, MAX_THREADS
    jge reset_thread_id
    mov [CURRENT_THREAD_ID], eax
    jmp check_next_thread

reset_thread_id:
    mov [CURRENT_THREAD_ID], 0

check_next_thread:
    ; Load the state of the new thread
    mov ecx, [CURRENT_THREAD_ID]
    mul ecx, ecx, TCB_SIZE
    cmp dword [ebx + ecx + 0x003C], 1  ; Check if thread state is Ready
    je load_thread_context

    ; If not ready, continue to the next thread
    inc dword [CURRENT_THREAD_ID]
    jmp check_next_thread

load_thread_context:
    ; Load new thread context
    mov esp, [ebx + ecx + 0x0004]  ; Load SP
    mov ebp, [ebx + ecx + 0x0008]  ; Load BP
    ; Load all general-purpose registers
    mov eax, [ebx + ecx + 0x000C]
    mov ebx, [ebx + ecx + 0x0010]
    mov ecx, [ebx + ecx + 0x0014]
    mov edx, [ebx + ecx + 0x0018]
    mov esi, [ebx + ecx + 0x001C]
    mov edi, [ebx + ecx + 0x0020]

    ret

lock_mutex:
    ; Input: ESI = address of mutex
    ; Try to acquire the mutex (spinlock)
    mov eax, dword [esi]
    cmp eax, 0
    je acquire_mutex
    ; Busy wait (spinlock)
    jmp lock_mutex

acquire_mutex:
    mov dword [esi], 1  ; Acquire mutex
    ret

unlock_mutex:
    ; Input: ESI = address of mutex
    mov dword [esi], 0  ; Release mutex
    ret

read_command:
    ; Input: None
    ; Output: EAX = Number of bytes read (0 indicates EOF or error)
    ;         Command buffer is filled with user input

    ; Prepare to read input
    mov eax, 3          ; Syscall number for sys_read
    mov ebx, 0          ; File descriptor 0 (stdin)
    lea ecx, [command]  ; Address of the buffer to store input
    mov edx, 100        ; Maximum number of bytes to read
    int 0x80            ; Make syscall

    ; Check for errors
    cmp eax, 0
    jl error_reading    ; If result is negative, an error occurred

    ret                 ; Return to caller

error_reading:
    mov eax, 1          ; Syscall number for sys_exit
    mov ebx, 1          ; Exit code 1 (indicates error)
    int 0x80            ; Make syscall to exit program

    ret

plugin_loader:
    ; Input: ESI = path to the module file
    ; Output: EAX = success (1) or failure (0)
    
    ; ... (load module logic)

    ; Open the module file
    mov eax, 5          ; syscall number for sys_open
    mov ebx, esi        ; filename in ESI
    mov ecx, 0          ; O_RDONLY mode
    int 0x80            ; syscall interrupt
    
    ; Check if file opened successfully
    cmp eax, 0
    jl plugin_load_fail
    
    mov ebx, eax        ; Store the file descriptor

    ; Register new commands from module
    mov esi, new_module_commands ; Start of new commands in module
    call register_commands       ; Update command table

    ; Success
    mov eax, 1
    ret

register_commands:
    ; Register new commands from the module
    ; Input: ESI = address of new command entries in module
    ; Output: None

register_command_loop:
    lodsb                       ; Load command byte
    test al, al                 ; Check for null terminator
    jz register_end             ; End of new commands

    ; Insert command into command_table
    mov edi, command_table      ; Destination for command_table
    lodsd                       ; Load the function pointer
    stosd                       ; Store command and function pointer

    jmp register_command_loop

register_end:
    ret

    ; Register functions from module
    add dword [MODULE_COUNT], 1 ; Increment module count
    
    mov eax, 1          ; Indicate success
    ret

plugin_load_fail:
    mov eax, 0          ; Indicate failure
    ret


MAIN_ROUTINE:
    ; Example Main Routine with Double-Precision Float Usage
    mov rax, buffer        ; Load buffer address
    movapd xmm0, [rax]     ; Load first double-precision float
    movapd xmm1, [rax+8]   ; Load second double-precision float
    addsd xmm0, xmm1       ; Add two double-precision floats
    movapd [rax], xmm0     ; Store result back in buffer

INITIALIZATION:
    ; Initialize any double-precision buffers or variables
    ; Use `movsd` or `movapd` as necessary for 64-bit float initialization
    mov rax, buffer
    movsd [rax], xmm0     ; Example of initializing buffer with xmm0 (double precision)
    ret

INIT_LOGIC_MODULE:
    ; Register functions in function table
    mov edi, MODULE_TABLE_BASE   ; Base address of function table
    add edi, [MODULE_COUNT]      ; Adjust by number of modules

    mov [edi], FUNC_MIN          ; Register LOGIC_MIN_FUNC
    add edi, 4                   ; Move to next slot
    mov [edi], FUNC_MAX          ; Register LOGIC_MAX_FUNC
    ; Continue registering all functions

    ret

    ; ... continue with other operations ...
    ret

CALL_FUNCTION:
    ; Input: EAX = function identifier, EBX = parameter type signatures
    ; Output: Executes the function with matching signature

    ; Initialize base address of the module function table
    mov ecx, MODULE_TABLE_BASE
    mov edx, [MODULE_COUNT]
    test edx, edx
    jz no_function_found ; Exit if no modules loaded

    ; If you have control flow or logic to manage based on floating-point operations:
    call LOGIC_HANDLER     ; Call logic handler updated for double-precision

find_function:
    cmp dword [ecx], eax      ; Compare function ID
    jne next_function
    cmp dword [ecx + 4], ebx  ; Compare parameter signature
    je execute_function
next_function:
    add ecx, 8                ; Move to the next function entry
    loop find_function

no_function_found:
    ; Handle case if function is not found
    ret

execute_function:
    call dword [ecx + 8]      ; Call the function pointer
    ret


ACCESS_FIELD:
    ; Input: EAX = struct base address, EBX = field offset
    ; Output: ECX = field value

    mov ecx, [eax + ebx]  ; Load the value of the field into ECX
    ret

MODIFY_FIELD:
    ; Input: EAX = struct base address, EBX = field offset, ECX = new value
    ; Output: None

    mov [eax + ebx], ecx  ; Store the new value into the field
    ret

CALL_FUNCTION:
    ; Input: EAX = function identifier, EBX = parameter type signatures
    ; Output: Executes the function with matching signature

    ; Find function in the function table by signature
    mov ecx, FUNCTION_TABLE
find_function:
    cmp dword [ecx], eax      ; Compare function ID
    jne next_function
    cmp dword [ecx + 4], ebx  ; Compare parameter signature
    je execute_function
next_function:
    add ecx, 8                ; Move to the next function entry
    jmp find_function

execute_function:
    call dword [ecx + 8]      ; Call the function pointer
    ret

ADD_DOUBLE:
    ; Ensure correct operation with SIMD for double-precision
    mov rax, [rsp + 8]       ; Assume first operand address on stack
    mov rbx, [rsp + 16]      ; Assume second operand address on stack
    movsd xmm0, [rax]        ; Load first operand
    movsd xmm1, [rbx]        ; Load second operand
    addsd xmm0, xmm1         ; Perform addition

    ; Check for floating-point exceptions
    ; Example: Test if result is NaN
    movaps xmm2, xmm0        ; Move result to another register for testing
    ucomisd xmm2, xmm2       ; Compare result with itself; NaN will not compare equal
    jp .error_routine        ; Jump if NaN (unordered comparison)

    ; Store result
    movsd [rax], xmm0        ; Store result back
    ret

.error_routine:
    mov eax, ERR_FP_EXCEPTION ; Error code for floating-point exception
    call REPORT_ERROR
    ret
