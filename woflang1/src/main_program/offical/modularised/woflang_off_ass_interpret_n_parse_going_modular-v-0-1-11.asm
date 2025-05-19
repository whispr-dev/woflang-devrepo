; v.0.1.7 i'm all about structs n objs!:

; main.asm
INCLUDE math.asm
INCLUDE logic.asm
INCLUDE string.asm
INCLUDE err.asm

MAIN_EXECUTION:
  ; The main loop that handles commands and dispatches them to the right module
  JMP MAIN_LOOP
 with your main program code...



; In main.asm
EXTERN ADD_LOGIC_ROUTINE

; Call the addition routine from the logic module
CALL ADD_ROUTINE


; Initialize Registers and Memory
MOV R50, 0   ; Initialize R50 (General purpose register)
MOV R51, 0   ; Initialize R51 (General purpose register)
MOV R52, 0   ; Initialize R52 (General purpose register)
MOV R53, 0   ; Initialize R53 (General purpose register)
MOV R54, 0   ; Initialize R54 (General purpose register)
MOV R55, 0   ; Initialize R55 (General purpose register)
MOV R56, 0   ; Initialize R56 (General purpose register)
MOV R57, 0   ; Initialize R57 (General purpose register)
MOV R58, 0   ; Initialize R58 (General purpose register)
MOV R59, 0   ; Initialize R59 (General purpose register)
MOV R60, 0   ; Initialize R60 (General purpose register)
MOV R61, 0   ; Initialize R61 (General purpose register)
MOV R62, 0   ; Initialize R62 (General purpose register)
MOV R63, 0   ; Initialize R63 (General purpose register)
MOV R64, 0   ; Initialize R64 (General purpose register)
MOV R65, 0   ; Initialize R65 (General purpose register)
MOV R66, 0   ; Initialize R66 (General purpose register)
MOV R67, 0   ; Initialize R67 (General purpose register)
MOV R68, 0   ; Initialize R68 (General purpose register)
MOV R69, 0   ; Initialize R69 (General purpose register)
MOV R70, 0   ; Initialize R60 (General purpose register)
MOV R71, 0   ; Initialize R71 (General purpose register)
MOV R72, 0   ; Initialize R72 (General purpose register)
MOV R73, 0   ; Initialize R73 (General purpose register)
MOV R74, 0   ; Initialize R74 (General purpose register)
MOV R75, 0   ; Initialize R75 (General purpose register)
MOV R76, 0   ; Initialize R76 (General purpose register)
MOV R77, 0   ; Initialize R77 (General purpose register)
MOV R78, 0   ; Initialize R78 (General purpose register)
MOV R79, 0   ; Initialize R79 (General purpose register)
MOV R80, 0   ; Initialize R80 (General purpose register)
MOV R81, 0   ; Initialize R81 (General purpose register)
MOV R82, 0   ; Initialize R82 (General purpose register)
MOV R83, 0   ; Initialize R43 (General purpose register)
MOV R44, 0   ; Initialize R44 (General purpose register)
MOV R45, 0   ; Initialize R45 (General purpose register)
MOV R46, 0   ; Initialize R46 (General purpose register)
MOV R47, 0   ; Initialize R47 (General purpose register)
MOV R48, 0   ; Initialize R48 (General purpose register)
MOV R49, 0   ; Initialize R49 (General purpose register)
MOV R90, 0   ; Initialize R90 (General purpose register)
MOV R91, 0   ; Initialize R91 (General purpose register)
MOV R92, 0   ; Initialize R92 (General purpose register)
MOV R93, 0   ; Initialize R93 (General purpose register)
MOV R94, 0   ; Initialize R94 (General purpose register)
MOV R95, 0   ; Initialize R95 (General purpose register)
MOV R96, 0   ; Initialize R96 (General purpose register)
MOV R97, 0   ; Initialize R97 (General purpose register)
MOV R98, 0   ; Initialize R98 (General purpose register)
MOV R99, 0   ; Initialize R99 (General purpose register)
MOV R90, 0   ; Initialize R100 (General purpose register)
MOV R91, 0   ; Initialize R101 (General purpose register)
MOV R92, 0   ; Initialize R102 (General purpose register)
MOV R93, 0   ; Initialize R103 (General purpose register)
MOV R94, 0   ; Initialize R104 (General purpose register)
MOV R95, 0   ; Initialize R105 (General purpose register)
MOV R96, 0   ; Initialize R106 (General purpose register)
MOV R97, 0   ; Initialize R107 (General purpose register)
MOV R98, 0   ; Initialize R108 (General purpose register)
MOV R99, 0   ; Initialize R109 (General purpose register)
MOV R100, 0   ; Initialize R110 (General purpose register)
MOV R101, 0   ; Initialize R111 (General purpose register)
MOV R100, 0   ; Initialize R112 (General purpose register)
MOV R103, 0   ; Initialize R113 (General purpose register)
MOV R104, 0   ; Initialize R114 (General purpose register)
MOV R105, 0   ; Initialize R115 (General purpose register)
MOV R106, 0   ; Initialize R116 (General purpose register)
MOV R107, 0   ; Initialize R117 (General purpose register)
MOV R108, 0   ; Initialize R118 (General purpose register)
MOV R109, 0   ; Initialize R119 (General purpose register)
MOV R110, 0   ; Initialize R120 (General purpose register)
MOV R111, 0   ; Initialize R121 (General purpose register)
MOV R112, 0   ; Initialize R122 (General purpose register)
MOV R113, 0   ; Initialize R123 (General purpose register)
MOV R114, 0   ; Initialize R124 (General purpose register)
MOV R115, 0   ; Initialize R125 (General purpose register)
MOV R116, 0   ; Initialize R126 (General purpose register)
MOV R117, 0   ; Initialize R127 (General purpose register)
MOV R118, 0   ; Initialize R128 (General purpose register)
MOV R119, 0   ; Initialize R129 (General purpose register)
MOV R120, 0   ; Initialize R130 (General purpose register)
MOV R121, 0   ; Initialize R131 (General purpose register)
MOV R122, 0   ; Initialize R132 (General purpose register)
MOV R123, 0   ; Initialize R133 (General purpose register)
MOV R124, 0    ; Initialize R134 (General purpose register)
MOV R125, 0    ; Initialize R135 (General purpose register)
MOV R126, 0    ; Initialize R136 (General purpose register)
MOV R127, MEM[150]; Start address of the command string in memory
MOV R128, 0    ; Initialize R137 (General purpose register)
MOV R129, 0    ; Initialize R138 (General purpose register)
MOV R130, 0    ; Initialize R139 (General purpose register)
MOV R131, 0    ; Initialize R140 (General purpose register)
MOV R132, 0    ; Initialize R141 (General purpose register)
MOV R133, 0    ; Initialize R142 (General purpose register)



; Initialize Registers and Memory
MOV R134, 0    ; Initialize R50 (General purpose register)
MOV R135, 0    ; Initialize R51 (General purpose register)
MOV R136, 0    ; Initialize R52 (General purpose register)
MOV R137, MEM[160]; R3: Start address of the command string in memory
MOV R138, 0    ; Initialize R54 (General purpose register)
MOV R139, 0    ; Initialize R55 (General purpose register)
MOV R140, 0    ; Initialize R56 (General purpose register)
MOV R141, 0    ; Initialize R57 (General purpose register)
MOV R142, 0    ; Initialize R58 (General purpose register)
MOV R143, 0    ; Initialize R59 (General purpose register)



ALLOCATE_MEMORY:
    ; Input: R1 = size of memory to allocate
    ; Output: R0 = address of allocated memory block (or 0 if allocation failed)

    ; Check free list for available block of sufficient size
    MOV R2, FREE_LIST_HEAD ; R2 points to the head of the free list
ALLOCATE_LOOP:
    CMP R2, 0              ; If R2 is 0, end of free list
    JE ALLOCATE_FAIL       ; No suitable block found, allocation failed
    MOV R3, [R2]           ; Load size of current free block
    CMP R3, R1             ; Compare free block size with requested size
    JGE ALLOCATE_FOUND     ; Found a block of sufficient size

    ; Move to the next block in the free list
    MOV R2, [R2 + 4]       ; Assume next free block pointer is at R2+4
    JMP ALLOCATE_LOOP

ALLOCATE_FOUND:
    ; Found a suitable block, remove it from the free list
    MOV R4, [R2 + 4]       ; Load next free block pointer
    MOV FREE_LIST_HEAD, R4 ; Update free list head

    ; Return the address of the allocated block
    MOV R0, R2
    RET

ALLOCATE_FAIL:
    ; No suitable block found, return 0 to indicate failure
    MOV R0, 0
    RET


FREE_MEMORY:
    ; Input: R1 = address of memory block to free

    ; Add block to the free list
    MOV [R1 + 4], FREE_LIST_HEAD ; Point freed block to current head of free list
    MOV FREE_LIST_HEAD, R1       ; Update free list head to point to freed block
    RET


; Mark Phase
MARK_PHASE:
    ; Start with the root references (e.g., global variables, stack variables)
    MOV R1, ROOT_REF_LIST   ; R1 points to the start of the root reference list
MARK_LOOP:
    CMP R1, 0               ; End of root reference list
    JE SWEEP_PHASE          ; Jump to sweep phase if no more roots
    MOV R2, [R1]            ; Load the next root reference
    CALL MARK_OBJECT        ; Mark the object reachable from this reference
    ADD R1, 4               ; Move to the next root reference (assuming 4-byte addresses)
    JMP MARK_LOOP

MARK_OBJECT:
    ; R2 is the object address to mark
    CMP [R2], 1             ; Check if object is already marked
    JE RETURN               ; If marked, return
    MOV [R2], 1             ; Mark the object (e.g., set the first byte to 1)
    
    ; Assume object references are stored after the first byte
    MOV R3, R2 + 1          ; Start scanning references
MARK_CHILDREN_LOOP:
    CMP [R3], 0             ; End of references for this object
    JE RETURN
    MOV R4, [R3]            ; Load the next reference
    CALL MARK_OBJECT        ; Recursively mark referenced objects
    ADD R3, 4               ; Move to the next reference
    JMP MARK_CHILDREN_LOOP

RETURN:
    RET

; Sweep Phase
SWEEP_PHASE:
    MOV R1, HEAP_START      ; R1 points to the start of the heap
SWEEP_LOOP:
    CMP R1, HEAP_END        ; End of heap
    JE END_GC               ; Jump to end of garbage collection
    CMP [R1], 1             ; Check if object is marked
    JNE FREE_BLOCK          ; If not marked, free it

    ; Unmark the object for the next GC cycle
    MOV [R1], 0             ; Clear the mark
    ADD R1, [R1 + 4]        ; Move to the next object (assuming size is at R1+4)
    JMP SWEEP_LOOP

FREE_BLOCK:
    CALL FREE_MEMORY        ; Free the memory block
    ADD R1, [R1 + 4]        ; Move to the next object
    JMP SWEEP_LOOP

END_GC:
    RET


; Allocate Command
ALLOCATE_COMMAND:
    ; Input: R1 = size of memory to allocate
    CALL ALLOCATE_MEMORY
    ; Output: R0 = address of allocated memory block
    RET

; Free Command
FREE_COMMAND:
    ; Input: R1 = address of memory block to free
    CALL FREE_MEMORY
    RET



STRUCT Point
    x: INTEGER
    y: INTEGER
ENDSTRUCT


; Pseudo-code to parse STRUCT definition
PARSE_STRUCT:
    CMP R0, 'STRUCT'       ; Check if it's a STRUCT keyword
    JNE NEXT_PARSE         ; If not, continue to other parse logic

    ; Parse the structure name
    READ_STRUCTURE_NAME
    STORE_STRUCT_METADATA  ; Store structure type in a metadata table

    ; Parse the fields
    READ_FIELD_NAME
    READ_FIELD_TYPE
    STORE_FIELD_METADATA

    ; Continue until 'ENDSTRUCT' is found
    JMP PARSE_NEXT

NEXT_PARSE:
    ; Continue with the next parsing rule
    JMP PARSE_LOOP


; Allocate memory for a structure instance
ALLOC_STRUCT_INSTANCE:
    LOAD R1, STRUCT_SIZE_TABLE[R0]  ; Get the size of the struct
    CALL MALLOC, R1                 ; Allocate memory and get the base address
    MOV R2, STRUCT_INSTANCE_TABLE   ; Store the base address in an instance table
    RET


; Example: Accessing a field
ACCESS_FIELD:
    LOAD R1, STRUCT_INSTANCE_TABLE[R0] ; Base address of the struct instance
    LOAD R2, STRUCT_FIELD_OFFSET[R1, FIELD_INDEX] ; Offset of the field
    ADD R3, R1, R2                     ; Calculate field address
    LOAD R4, [R3]                      ; Load the field value
    RET

; Example: Modifying a field
MODIFY_FIELD:
    LOAD R1, STRUCT_INSTANCE_TABLE[R0] ; Base address of the struct instance
    LOAD R2, STRUCT_FIELD_OFFSET[R1, FIELD_INDEX] ; Offset of the field
    ADD R3, R1, R2                     ; Calculate field address
    STORE [R3], R4                     ; Store the new value in the field
    RET



PATTERN_MATCH_ROUTINE:
    ; Check if it's a MATCH keyword
    CMP R0, 'MATCH'
    JNE CONTINUE_MAIN_LOGIC

    ; Read the value to be matched
    READ_VALUE_TO_MATCH

    ; Start loop over patterns
PATTERN_LOOP:
    READ_NEXT_PATTERN
    CMP R2, 'END_MATCH'
    JE NO_MATCH_DEFAULT

    CMP_PATTERN R1, R2
    JE EXECUTE_PATTERN

    JMP PATTERN_LOOP

NO_MATCH_DEFAULT:
    EXECUTE_DEFAULT
    JMP END_PATTERN_MATCH

EXECUTE_PATTERN:
    ; Execute associated action
    EXECUTE_ACTION
    JMP END_PATTERN_MATCH

END_PATTERN_MATCH:
    ; Continue program execution
    JMP MAIN_EXECUTION



CLASS Car
    speed: INTEGER
    accelerate: FUNCTION
ENDCLASS


PARSE_CLASS:
    CMP R0, 'CLASS'         ; Check if it's a CLASS keyword
    JNE NEXT_PARSE          ; If not, continue to other parse logic

    ; Parse the class name and fields
    READ_CLASS_NAME
    STORE_CLASS_METADATA

    ; Parse the methods
    READ_METHOD_NAME
    STORE_METHOD_METADATA

    ; Continue until 'ENDCLASS' is found
    JMP PARSE_NEXT


ALLOC_OBJECT_INSTANCE:
    LOAD R1, CLASS_SIZE_TABLE[R0]   ; Get the size of the class
    CALL MALLOC, R1                 ; Allocate memory and get the base address
    MOV R2, OBJECT_INSTANCE_TABLE   ; Store the base address in an instance table
    RET


INVOKE_METHOD:
    LOAD R1, OBJECT_INSTANCE_TABLE[R0] ; Base address of the object instance
    LOAD R2, METHOD_OFFSET[R1, METHOD_INDEX] ; Offset of the method
    CALL [R2]                           ; Invoke the method
    RET


; Example uusage of structs n objs:
; 
; STRUCT Point
;     x: INTEGER
;     y: INTEGER
; ENDSTRUCT
; 
; CLASS Car
;     speed: INTEGER
;     accelerate: FUNCTION
; ENDCLASS
; 
; ; Instantiate and use a struct
; NEW Point myPoint
; SET myPoint.x 10
; SET myPoint.y 20
; 
; ; Instantiate and use an object
; NEW Car myCar
; CALL myCar.accelerate


; In main.asm
EXTERN ADD_FUNCOVLD_STRING_ROUTINE
 
; Call the addition routine from the string module
CALL ADD_FUNCOVLD_STRING_ROUTINE

RET


CALL_FUNCTION:
    ; Read the function name
    READ_FUNCTION_NAME      ; Read function name into R1
    MOV R2, FUNCTION_TABLE[R1] ; Load function entry from FUNCTION_TABLE

    ; Check if the function exists
    CMP R2, 0
    JEQ ERROR_UNDEFINED_FUNCTION

    ; Read the argument types from the stack or memory
    PARSE_ARGUMENT_TYPES

    ; Check the function signatures for a match
    MATCH_FUNCTION_SIGNATURE
    JEQ EXECUTE_FUNCTION    ; If matched, jump to execute function

    ; If no matching signature found, error
    ERROR_NO_MATCHING_SIGNATURE
    JMP NEXT_COMMAND

EXECUTE_FUNCTION:
    ; Set up stack and registers for function call
    CALL FUNCTION_ADDRESS   ; Jump to function address
    RET                     ; Return after function execution



; In err.asm
EXTERN ADD_OVLDFUNC_ERR_ROUTINE

; Call the addition routine form the string module
CALL ADD_OVLDFUNC_ERR_ROUTINE:
  ; Code here...

RET

; Example code for overload function
; 
; FUNCTION add(a: INTEGER, b: INTEGER)
;     RETURN a + b
; ENDFUNCTION
; 
; FUNCTION add(a: FLOAT, b: FLOAT)
;     RETURN a + b
; ENDFUNCTION
; 
; FUNCTION add(a: STRING, b: STRING)
;     RETURN CONCAT(a, b)
; ENDFUNCTION
; 
; add(5, 10)        ; Calls the integer add function
; add(5.0, 10.0)    ; Calls the float add function
; add("Hello, ", "world!") ; Calls the string add function 



; Define constants
ARRAY_START_ADDRESS EQU 200  ; Starting memory address for arrays

; Routine to declare an array
DECLARE_ARRAY:
    MOV R1, ARRAY_START_ADDRESS  ; Base address for arrays
    MOV R2, [R0]                 ; R0 contains the size of the array to be declared
    MOV [R1], R2                 ; Store the size at the base address
    ADD R1, 1                    ; Move to the first element address

    ; Initialize array elements to 0
    MOV R3, 0                    ; Initialize index
    DECLARE_ARRAY_LOOP:
        CMP R3, R2               ; Check if we've initialized all elements
        JGE END_DECLARE_ARRAY
        MOV [R1 + R3], 0         ; Initialize the current element to 0
        ADD R3, 1                ; Move to the next element
        JMP DECLARE_ARRAY_LOOP

    END_DECLARE_ARRAY:
        RET


; Initialize Variables for Math, Logic, and String Processing
MOV R144, 0   ; Start index of the expression
MOV R145, 0   ; Length of the expression
MOV R146, 0   ; Type of expression (integer, float, logic, string)


; Pattern Identifiers (Types)
INTEGER EQU 1
FLOAT EQU 2
STRING EQU 3
COMMAND EQU 4
SYMBOL EQU 5
MATH_OP EQU 6   ; Identifier for math operations
LOGIC_OP EQU 7  ; Identifier for logic operations
STRING_OP EQU 8 ; Identifier for string operations


; In main.asm
EXTERN ADD_PARSE_STRING_ROUTINE

; Call the addition routine from the string module
CALL ADD_PARSE_STRING_ROUTINE

RET


; Routine to access an array element
ACCESS_ARRAY_ELEMENT:
    MOV R1, ARRAY_START_ADDRESS   ; Base address of the array
    MOV R2, [R0]                  ; R0 contains the index to access
    CMP R2, [R1]                  ; Check if the index is within bounds
    JGE ERROR_OUT_OF_BOUNDS
    ADD R1, R2                    ; Calculate the address of the element
    MOV R3, [R1 + 1]              ; R3 will hold the accessed element (R1 + 1 because R1 holds the length)
    RET

ERROR_OUT_OF_BOUNDS:
    MOV R3, -1                    ; Error code for out of bounds
    RET


; In main.asm
EXTERN ADD_INTFLOAT_MATH_ROUTINE

; Call the addition routine from the math module
CALL ADD_INTFLOAT_ROUTINE

RET


; In main.asm
EXTERN ADD_TOKEN_MATH_ROUTINE

; Call the addition routine from the math module
CALL ADD_TOKEN_ROUTINE

IS_MATH_OP:
    MOV R56, MATH_OP        ; Set token type to MATH_OP
    ADD R51, 50              ; Increment token length
    ; Process math expression if identified
    CMP R51, 49              ; Check if it's part of a math expression
    JG PROCESS_MATH_EXPRESSION
    JMP NEXT_CHAR

RET


; In main.asm
EXTERN ADD_LOGIC_MATH_ROUTINE

; Call the addition routine from the math module
CALL ADD__LOGIC_MATH_ROUTINE


RET


PARSE_END:
    ; Parsing is complete, reset variables for next token
    MOV R1, R49             ; Set start position for the next token
    MOV R51, 49              ; Reset token length
    MOV R56, 49              ; Reset token type
    JMP NEXT_COMMAND       ; Jump to handle the next command or end

NEXT_COMMAND:
    ; Handle the next command or complete program logic
    HALT                   ; Stop execution for this example



; Memory and constants setup
MOV MEM[161], 49  ; Initialize additional memory locations as needed


; Routine to modify an array element
MODIFY_ARRAY_ELEMENT:
    MOV R1, ARRAY_START_ADDRESS   ; Base address of the array
    MOV R2, [R0]                  ; R0 contains the index to modify
    CMP R2, [R1]                  ; Check if the index is within bounds
    JGE ERROR_OUT_OF_BOUNDS
    ADD R1, R2                    ; Calculate the address of the element
    MOV [R1 + 1], R3              ; Modify the element (R1 + 1 because R1 holds the length)
    RET


HEADER EQU 0x01
VAR EQU 0x02
FUNC EQU 0x03
MAIN EQU 0x04


; Routine to iterate over an array
ITERATE_ARRAY:
    MOV R1, ARRAY_START_ADDRESS   ; Base address of the array
    MOV R2, [R1]                  ; Load the array length
    MOV R3, 0                     ; Initialize index
    ITERATE_LOOP:
        CMP R3, R2                ; Check if we've reached the end of the array
        JGE END_ITERATE
        MOV R4, [R1 + R3 + 1]     ; Load the current element into R4 (R1 + 1 because R1 holds the length)
        ; Perform any operations on R4 here

        ADD R3, 1                 ; Move to the next element
        JMP ITERATE_LOOP

    END_ITERATE:
        RET


EXPECTED_HEADER DB 'WFL_HEADER'
VAR_BLOCK DB 'VAR'
FUNC_BLOCK DB 'FUNC'
MAIN_BLOCK DB 'MAIN'


; In main.asm
EXTERN ADD_PARARR_STRING_ROUTINE

; Call the addition routine from the math module
CALL ADD_PARARR_STRING_ROUTINE

RET


; In main.asm
EXTERN ADD_ARRMEM_ERR_ROUTINE

; Call the addition routine from the string module
CALL ADD_ARRMEM_ERR_ROUTINE

RET


what do with?

ERR_DUPLICATE_BLOCK EQU 0xFF01
ERR_UNRECOGNIZED_CMD EQU 0xFF02
ERR_MISSING_MAIN EQU 0xFF03
ERR_EOF EQU 0xFF04


; Start of Main Loop
; Main Loop: Read lines and check order
MAIN_LOOP:
    READ R49, R52             ; Read the current line into R0
    MOV R53, VAR_BLOCK
    CALL STRCMP             ; Check if line is VAR block
    JZ VAR_FOUND            ; If yes, jump to VAR_FOUND
    
    MOV R55, FUNC_BLOCK
    CALL STRCMP             ; Check if line is FUNC block
    JZ FUNC_FOUND           ; If yes, jump to FUNC_FOUND
    
    MOV R55, MAIN_BLOCK
    CALL STRCMP             ; Check if line is MAIN block
    JZ MAIN_FOUND           ; If yes, jump to MAIN_FOUND

    ; Check if reached end of the file without finding MAIN
    CMP R52, EOF
    JE CHECK_MISSING_MAIN   ; Jump to check for missing MAIN


; memory and constants unrecog


 ; In main.asm
EXTERN ADD_MEMCUNRECOG_ERR_ROUTINE

; Call the addition routine from the math module
CALL ADD_MEMCUNRECOG_ERR


    ; Otherwise, keep reading the next line
    ADD R52, 50
    JMP MAIN_LOOP


; In main.asm
EXTERN ADD_VAR_ERR_ROUTINE

; Call the addition routine from the math module
CALL ADD_VAR_ERR


MAIN_EXECUTION:
    ; The logic of MAIN block begins here
    ; Parse and execute various functionalities and structures
    READ R0, R3             ; Read the current line into R0
    CALL PARSE_COMMAND      ; Parse the command and arguments

    ; ADD Functionality
    CMP R0, '齊'            ; Check if command is ADD (齊)
    JEQ ADD_ROUTINE

    ; SUBTRACT Functionality
    CMP R0, '隶'            ; Check if command is SUBTRACT (隶)
    JEQ SUB_ROUTINE

    ; MULTIPLY Functionality
    CMP R0, '丶'            ; Check if command is MULTIPLY (丶)
    JEQ MUL_ROUTINE

    ; DIVIDE Functionality
    CMP R0, '丿'            ; Check if command is DIVIDE (丿)
    JEQ DIV_ROUTINE

    ; MIN (AND) Functionality
    CMP R0, '而'            ; Check if command is MIN (AND) (而)
    JEQ AND_ROUTINE

    ; MAX (OR) Functionality
    CMP R0, '或'            ; Check if command is MAX (OR) (或)
    JEQ OR_ROUTINE

    ; XOR Functionality
    CMP R0, '⊕'             ; Check if command is XOR (⊕)
    JEQ XOR_ROUTINE

    ; NOT Functionality
    CMP R0, '无'            ; Check if command is NOT (无)
    JEQ NOT_ROUTINE

    ; NAND Functionality
    CMP R0, '无‍而'         ; Check if command is NAND (无‍而)
    JEQ NAND_ROUTINE

    ; NOR Functionality
    CMP R0, '无‍或'         ; Check if command is NOR (无‍或)
    JEQ NOR_ROUTINE

    ; IF Functionality
    CMP R0, '若'            ; Check if command is IF (若)
    JEQ IF_ROUTINE

    ; THEN Functionality
    CMP R0, '则'            ; Check if command is THEN (则)
    JEQ THEN_ROUTINE

    ; ELSE Functionality
    CMP R0, '另'            ; Check if command is ELSE (另)
    JEQ ELSE_ROUTINE

    ; Greater Than Functionality
    CMP R0, '大'            ; Check if command is Greater Than (大)
    JEQ GT_ROUTINE

    ; Less Than Functionality
    CMP R0, '小'            ; Check if command is Less Than (小)
    JEQ LT_ROUTINE

    ; Equals Functionality
    CMP R0, '卜'            ; Check if command is Equals (卜)
    JEQ EQ_ROUTINE

    ; Does Not Equal Functionality
    CMP R0, '丨'            ; Check if command is Does Not Equal (丨)
    JEQ DNE_ROUTINE

    ; Greater Than or Equal Functionality
    CMP R0, '走'            ; Check if command is Greater Than or Equal (走)
    JEQ GTE_ROUTINE

    ; Less Than or Equal Functionality
    CMP R0, '夊'            ; Check if command is Less Than or Equal (夊)
    JEQ LTE_ROUTINE

    ; While Loop Functionality
    CMP R0, '老'            ; Check if command is WHILE (老)
    JEQ WHILE_ROUTINE

    ; For Loop Functionality
    CMP R0, '至'            ; Check if command is FOR (至)
    JEQ FOR_ROUTINE

    ; Except Functionality
    CMP R0, '舛'            ; Check if command is EXCEPT (舛)
    JEQ EXCEPT_ROUTINE

    ; Break Functionality
    CMP R0, '止'            ; Check if command is BREAK (止)
    JEQ BREAK_ROUTINE

    ; String Functionality
    CMP R0, '己'            ; Check if command is STRING (己)
    JEQ STR_ROUTINE

    ; Count Functionality
    CMP R0, '支'            ; Check if command is COUNT (支)
    JEQ COUNT_ROUTINE

    ; Boolean Functionality
    CMP R0, '比'            ; Check if command is BOOLEAN (比)
    JEQ BOOL_ROUTINE

    ; End Functionality
    CMP R0, '終'            ; Check if command is END (終)
    JEQ END_ROUTINE

    ; Echo Functionality
    CMP R0, '響'            ; Check if command is ECHO (響)
    JEQ ECHO_ROUTINE

    ; Done Functionality
    CMP R0, '釆'            ; Check if command is DONE (釆)
    JEQ DONE_ROUTINE

    ; Exit Functionality
    CMP R0, '卩'            ; Check if command is EXIT (卩)
    JEQ EXIT_ROUTINE

    ; Prompt Functionality
    CMP R0, '押'            ; Check if command is PROMPT (押)
    JEQ PROMPT_ROUTINE

    ; Input Functionality
    CMP R0, '⽰'            ; Check if command is INPUT (⽰)
    JEQ INPUT_ROUTINE

    ; Sleep Functionality
    CMP R0, '眠'            ; Check if command is SLEEP (眠)
    JEQ SLEEP_ROUTINE

    ; HTTP Functionality
    CMP R0, '⺒'            ; Check if command is HTTP (⺒)
    JEQ HTTP_ROUTINE

    ; Proxy Functionality
    CMP R0, '⺨'            ; Check if command is PROXY (⺨)
    JEQ PROXY_ROUTINE

    ; User Agent Functionality
    CMP R0, '⽪'            ; Check if command is USER_AGENT (⽪)
    JEQ USER_AGENT_ROUTINE

    ; Server Functionality
    CMP R0, '⽓'            ; Check if command is SERVER (⽓)
    JEQ SERVER_ROUTINE

    ; Wait Functionality
    CMP R0, '待'            ; Check if command is WAIT (待)
    JEQ WAIT_ROUTINE

    ; Null Functionality
    CMP R0, '⻤'            ; Check if command is NULL (⻤)
    JEQ NULL_ROUTINE

    ; Print Functionality
    CMP R0, '⺙'            ; Check if command is PRINT (⺙)
    JEQ PRINT_ROUTINE

    ; System Call Functionality
    CMP R0, '⺆'            ; Check if command is SYS_CALL (⺆)
    JEQ SYS_CALL_ROUTINE

    ; Function Call Functionality
    CMP R0, '⺘'            ; Check if command is FUNCTION (⺘)
    JEQ FUNCTION_ROUTINE

    ; Move Functionality
    CMP R0, '工'            ; Check if command is MOVE (工)
    JEQ MOVE_ROUTINE

    ; Attribute Functionality
    CMP R0, '⺣'            ; Check if command is ATTRIBUTE (⺣)
    JEQ ATTRIBUTE_ROUTINE

    ; Path Functionality
    CMP R0, '道'            ; Check if command is PATH (道)
    JEQ PATH_ROUTINE

    ; Type Functionality
    CMP R0, '⺢'            ; Check if command is TYPE (⺢)
    JEQ TYPE_ROUTINE

    ; Character Functionality
    CMP R0, '字'            ; Check if command is CHAR (字)
    JEQ CHAR_ROUTINE

    ; Read Functionality
    CMP R0, '読'            ; Check if command is READ (読)
    JEQ READ_ROUTINE

    ; Continue reading the next command
    ADD R3, 1
    JMP MAIN_EXECUTION


MAIN_END:
    ; End of MAIN logic
    ; Proceed to the next section or EOF
    JMP END_OF_FILE


; Initialize Registers and Memory
MOV R49, 49    ; Initialize R49 (General purpose register)
MOV R50, 49    ; Initialize R50 (General purpose register)
...
MOV R93, 49   ; Initialize R93 (General purpose register)
MOV R94, 50   ; Initialize R94 to track line numbers, starting at line 1
MOV R95, 49   ; Initialize R95 for storing error codes


; In main.asm
EXTERN ADD_PARVAR_STRING_ROUTINE

; Call the addition routine from the string module
CALL ADD_PARVAR_STRING_ROUTINE


RET


 ; In main.asm
EXTERN ADD_UNRECOG_ERR_ROUTINE

; Call the addition routine from the math module
CALL ADD_UNRECOG_ERR

 
VALID_COMMAND:
    ; Continue processing the valid command...
    RET

; Data Type Checking (Example in Arithmetic)
CHECK_TYPES:
    CMP TYPE[R50], TYPE[R51]       ; Compare types of operands
    JEQ VALID_TYPES

    ; If types do not match, report error
    MOV R95, ERR_TYPE_MISMATCH
    JMP REPORT_ERROR

VALID_TYPES:
    ; Continue with arithmetic operation...
    RET


; In main.asm
EXTERN ADD_RUNTIME_ERR_ROUTINE

; Call the addition routine from the math module
CALL ADD_RUNTIME_ERR


VALID_DIVISION:
    ; Continue with division operation...
    RET

; Main Execution Loop
MAIN_EXECUTION:
    READ R49, R52                  ; Read the current line into R0
    ADD R94, 50                   ; Increment line number after reading a line



; In main.asm
EXTERN ADD_CMDHDL_STRING_ROUTINE

; Call the addition routine from the string module
CALL ADD_CMDHDL_STRING_ROUTINE


RET


    ; Continue main execution...
    JMP MAIN_LOOP

PROGRAM_END:
    ; End of program
    HALT



; for testing arrays:
; ; ; Sample commands for testing array functionality
; MOV R0, 5             ; Size of the array to declare
; CALL DECLARE_ARRAY
; 
; MOV R0, 2             ; Index to access
; CALL ACCESS_ARRAY_ELEMENT
; ; Check R3 for the result
; 
; MOV R0, 2             ; Index to modify
; MOV R3, 42            ; New value
; CALL MODIFY_ARRAY_ELEMENT
; 
; CALL ITERATE_ARRAY    ; Iterate over the array
