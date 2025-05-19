; endless notes blah blah...

; Example Arithmetic Operation Routines (Addition, Subtraction, etc.) ADDITION: ADD R14, R15, [R3 + R13 + 1] ; Add the next operand to the result JMP
; MATH_LOOP ; Continue math loop

; SUBTRACTION: SUB R14, R15, [R3 + R13 + 1] ; Subtract the next operand from the result JMP MATH_LOOP ; Continue math loop

; MULTIPLICATION: MUL R14, R15, [R3 + R13 + 1] ; Multiply the result by the next operand JMP MATH_LOOP ; Continue math loop

; DIVISION: DIV R14, R15, [R3 + R13 + 1] ; Divide the result by the next operand JMP MATH_LOOP ; Continue math loop

; Continue adding more routines for logic operations (AND_OP, OR_OP, etc.) and string operations as needed ; Add more error handling, checks, and advanced
; functionalities

; End of Program HALT ; Stop execution

; Explanation:

; 1. **Dedicated Handlers for Math, Logic, and Strings**:
;  - **Math Handler `(`MATH_HANDLER`)`**: Handles math expressions, using specialized routines for addition, subtraction, multiplication, and division.
;  - **Logic Handler `(`LOGIC_HANDLER`)`**: Handles logic operations like `AND`, `OR`, `NOT`, etc., efficiently processing logic expressions.
;  - **String Handler `(`STRING_HANDLER`)`**: Manages string manipulations, such as concatenation and comparisons, with dedicated logic.
;
; 2. **Routing Based on Expression Type**:
;  - During parsing `(`PARSE_LOOP`)`, the program detects the type of expression and routes the operation to the appropriate handler (Math, Logic, or 
; String).
;  - The code checks for numbers, operators, and characters to determine the type of operation required.
;
; 3.**Organized Code Flow**:
; - Rearranged the flow of the program to ensure that each section (parsing, handlers, main loop) is clearly defined and separated.
;
; 4. **Corrected Potential Syntax Issues**:
; - Fixed several incorrect syntax and potential errors in handling different operations.
;
; 5. **Improved Error Handling**:
; - Ensured that each error-handling routine has a consistent halt or jump to another logic block.

; **By organizing your code and ensuring proper flow, syntax, and structure, you can greatly improve the readability, maintainability, and functionality 
; of your assembly language program.**
