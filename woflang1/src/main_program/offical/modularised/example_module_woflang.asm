; Module Header
MODULE_NAME      DB 'MathModule', 0x00
MODULE_VERSION   DB 'v1.0.0', 0x00
MODULE_INIT_FUNC EQU 0x0040  ; Address of module initialization function

; Function Table
FUNC_ADD         EQU 0x0050  ; Address of the ADD function
FUNC_SUBTRACT    EQU 0x0060  ; Address of the SUBTRACT function
; Add more functions as needed...
