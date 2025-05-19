; woflang_official_assembly_interpreter-v-0-0-2.asm see .md

; Assume we read each line and parse it, placing values into memory/registers
; Register definitions for storing Woflang variables
; Initialize registers

MOV R0, 0   ; R0: θ
MOV R1, 0   ; R1: 齊
MOV R2, 0   ; R2: m
MOV R3, 0   ; R3: n

MOV R4, 0   ; R4: b
MOV R5, 0   ; R5: v
MOV R6, 0   ; R6: c
MOV R7, 0   ; R7:x

MOV R8, 0   ; R8: z
MOV R1, 0   ; R9: l
MOV R2, 0   ; R10: k
MOV R3, 0   ; R11: v

MOV R4, 0   ; R12: h
MOV R5, 0   ; R13: g 
MOV R6, 0   ; R14: d
MOV R7, 0   ; R15: s

MOV R8, 0   ; R16: a
MOV R1, 0   ; R17: p
MOV R2, 0   ; R18: o
MOV R3, 0   ; R19: i

MOV R4, 0   ; R20: u
MOV R5, 0   ; R21: y
MOV R6, 0   ; R22:t
MOV R7, 0   ; R23:r

MOV R8, 0   ; R24: e
MOV R1, 0   ; R25: w
MOV R2, 0   ; R26: q
MOV R3, 0   ; R27: 9

MOV R4, 0   ; R29: 8
MOV R5, 0   ; R30: 7
MOV R6, 0   ; R31:6 
MOV R7, 0   ; R32:5

MOV R8, 0   ; R33: 4 
MOV R1, 0   ; R34: 3 
MOV R2, 0   ; R35: 2
MOV R3, 0   ; R36 1

MOV R4, 0   ; R37: ⻔
MOV R5, 0   ; R38: 艮  
MOV R6, 0   ; R39: 読
MOV R7, 0   ; R40:字

MOV R8, 0   ; R41: ⺢
MOV R1, 0   ; R42: 道
MOV R2, 0   ; R43: 非
MOV R3, 0   ; R44: 巡

MOV R4, 0   ; R45: ⺣
MOV R5, 0   ; R46: 工
MOV R6, 0   ; R47: ⺘
MOV R7, 0   ; R48: ⺆

MOV R8, 0   ; R49: ⺙
MOV R1, 0   ; R50: ⻤
MOV R2, 0   ; R51: 待
MOV R3, 0   ; R52: ⽓

MOV R4, 0   ; R53: ⽪
MOV R5, 0   ; R54: ⺨
MOV R6, 0   ; R55: ⺒
MOV R7, 0   ; R56: 眠

MOV R8, 0   ; R57: ⽰
MOV R1, 0   ; R58: 支
MOV R2, 0   ; R59: 押
MOV R3, 0   ; R60: 卩

MOV R4, 0   ; R61: 釆
MOV R5, 0   ; R62: 響
MOV R6, 0   ; R63: 終 
MOV R7, 0   ; R64: 比

MOV R8, 0   ; R65: 辵
MOV R1, 0   ; R66: 己
MOV R2, 0   ; R67: 氏/谷
MOV R3, 0   ; R68: 出

MOV R4, 0   ; R69: 止
MOV R5, 0   ; R70: 入
MOV R6, 0   ; R71: 又
MOV R7, 0   ; R72: 自

MOV R8, 0   ; R73: 舛   
MOV R1, 0   ; R74: 至
MOV R2, 0   ; R75: 老
MOV R3, 0   ; R76: 夊

MOV R4, 0   ; R77: 走
MOV R5, 0   ; R78: 丨
MOV R6, 0   ; R79: 卜
MOV R7, 0   ; R80: 小

MOV R8, 0   ; R81: 大
MOV R1, 0   ; R82: 門
MOV R2, 0   ; R83: 另
MOV R3, 0   ; R84: 则 

MOV R4, 0   ; R85: 若
MOV R5, 0   ; R86: 无‍或
MOV R6, 0   ; R87: ‍无‍而
MOV R7, 0   ; R88: 无

MOV R8, 0   ; R89: ⊕ 
MOV R1, 0   ; R90: Z
MOV R2, 0   ; R91: 而
MOV R3, 0   ; R92: Z

MOV R4, 0   ; R93: 丶
MOV R5, 0   ; R94: 隶


; Memory setup for intermediate values and additional variables
MOV MEM[100], 0  ; Memory address 100 for intermediate results
MOV MEM[101], 0  ; Memory address 101 for intermediate results
MOV MEM[102], 0  ; Memory address 100 for intermediate results
MOV MEM[103], 0  ; Memory address 101 for intermediate results
MOV MEM[104], 0  ; Memory address 100 for intermediate results
MOV MEM[105], 0  ; Memory address 101 for intermediate results
MOV MEM[106], 0  ; Memory address 100 for intermediate results
MOV MEM[107], 0  ; Memory address 101 for intermediate results
MOV MEM[108], 0  ; Memory address 100 for intermediate results
MOV MEM[109], 0  ; Memory address 101 for intermediate results
MOV MEM[110], 0  ; Memory address 100 for intermediate results
MOV MEM[111], 0  ; Memory address 101 for intermediate results
MOV MEM[112], 0  ; Memory address 100 for intermediate results
MOV MEM[113], 0  ; Memory address 101 for intermediate results
; Continue to initialize additional memory addresses as needed


; Mapping Woflang variables to registers
; Memory setup for intermediate values and additional variables
; Continue to initialize additional memory addresses as needed

; Memory address definitions for storing intermediate results and additional variables
; Pseudocode for loading configuration - actual file I/O is simulated here
LOAD R0, 'input.wfl'      ; Load the input file path into R0
OPEN R0                                  ; Open the file specified in R0


READ MEM[100], R0         ; Read initial state into memory starting at address 100
READ MEM[101], R1         ; Read constant into R1
READ MEM[102], R2         ; Read variable into R2

; Initialize registers and memory for the loaded configuration
MOV R10, MEM[100]         ; Move the variable2 into R10 for further operations
MOV R11, MEM[101]         ; Move the constant into R11 for further operations
MOV R12, MEM[102]         ; Move the variable into R12 for further operations

; ... Continue initializing other registers as needed


; ...
; Arithmmetic
; ... Continue initializing other memory addresses as needed
; additon
; Example operation: 1 齊 θ -> 1 = 1 + θ
; Assuming 1 is in R0 and θ is in R1

ADD R0, R0, R1        ; R0 = R0 + R1 (1 = 1 + θ)

; subtraction
; Example operation: 1 隶 1 -> 1 = 1 - 1
; Assuming 1 is in R2 and 1 is in R5

SUB R2, R2, R5        ; R2 = R2 - R5 (1 = 1 - 1)

; multiply
; Example operation: 2 丶 θ -> 2 = 2_B * θ
; Assuming 2 is in R6 and θ is in R7

MUL R6, R6, R7        ; R6 = R6 * R7 (2 = 2 * θ)

; divide
; Example operation: 1 丿 2 -> 1 = 1/ 2
; Assuming 1 is in R5 and 2 is in R6

DIV R5, R5, R6        ; R5 = R5 / R6 (1 = 1 / 2)


; Conditionals
; Example conditional: 若 iB 大 18.4271902292 则 wB 38.1672696857 另 iA 67.0942191332

CMP R5, 18.4271902292 ; Compare iB (in R5) with 18.4271902292
JLE SKIP_BLOCK        ; If iB <= 18.4271902292, jump to SKIP_BLOCK

; If condition is met, execute the following instructions
MOV R2, 38.1672696857 ; Set wB to 38.1672696857 in R2
MOV R4, 67.0942191332 ; Set iA to 67.0942191332 in R4

SKIP_BLOCK:           ; Label to skip block

; Now use R0-R3 for operations involving iC, θ, wB, wC


; Loop Operation
; Example loop: 巡 Start Loop_End

LOOP_START:           ; Start of loop

; (Loop body goes here)

CMP R3, R12           ; Compare current index (in R3) with total rows (in R12)
JL LOOP_START         ; If R3 < R12, jump back to LOOP_START

LOOP_END:             ; End of loop


; Storing Results and Ending the PRogram
; Store final results to memory
MOV MEM[103], R0      ; Store iA (in R0) to memory address 103
MOV MEM[104], R1      ; Store θA (in R1) to memory address 104
MOV MEM[105], R2      ; Store wB (in R2) to memory address 105

; End program
HALT                  ; Stop execution


; iA 齊 θA

; Assuming iA is in R0 and θA is in R1
