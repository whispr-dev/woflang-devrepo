WofLang Advanced User Guide
Introduction
WofLang is a revolutionary programming language designed to streamline mathematical and logical operations through the use of single Unicode characters. This design philosophy allows complex equations to be represented concisely, increasing both readability and efficiency for mathematically intensive applications.
This advanced guide will walk you through the core concepts, advanced features, and best practices for developing with WofLang. Whether you're implementing complex fuzzy logic systems, performing matrix operations, or developing multi-threaded applications, this guide will help you leverage the full power of WofLang.
Table of Contents

Language Philosophy and Design
Core Concepts
Using Fuzzy Logic
Mathematical Operations
Command Reference
Error Handling System
Multi-threading Support
Plugin System
String Handling and Parsing
Memory Management
Performance Optimization
Appendix: Unicode Character Reference

Language Philosophy and Design
WofLang is built on the premise that mathematical notation should be concise yet expressive. By mapping complex operations to single Unicode characters, WofLang allows developers to write dense, readable code for computationally intensive applications.
Key design principles include:

Mathematical Expressiveness: Prioritizing mathematical notation and operations
Fuzzy Logic Integration: First-class support for fuzzy logical operations
Error Resilience: Comprehensive error checking and recovery mechanisms
Modularity: Plugin-based architecture for extending functionality
Performance: Optimized for computational efficiency, with SIMD-like operations

Core Concepts
Command Structure
WofLang commands are primarily represented by Unicode characters mapped to specific operations. The basic syntax follows:
[operation] [operand1] [operand2] ... [operandN]
For example, the addition operation (represented by + or its Unicode equivalent) might be used as:
+ 5 3
Which would result in 8.
Value Representation
In WofLang, values typically range from 0 to 100, representing a fuzzy logic percentage. For example:

0 represents false, zero, or 0%
100 represents true, maximum, or 100%
Values between 0 and 100 represent fuzzy degrees of truth

This approach allows for more nuanced logical operations beyond simple binary logic.
Data Types
WofLang includes support for:

Numeric values: Primarily represented as doubles for maximum precision
Vectors: For SIMD-like operations
Matrices: For linear algebra operations
Strings: For text processing and program parsing

Using Fuzzy Logic
Fuzzy logic is a core concept in WofLang, allowing for more nuanced logical operations than traditional binary logic. Instead of values being strictly true (1) or false (0), they exist on a spectrum from 0 to 100.
Basic Fuzzy Operations

AND: Returns the minimum of two values
OR: Returns the maximum of two values
NOT: Inverts a value (100 - value)
XOR: Returns the absolute difference between values

Fuzzy Operation Examples
// Fuzzy AND - returns the minimum value
AND 70 30  // Result: 30

// Fuzzy OR - returns the maximum value
OR 70 30   // Result: 70

// Fuzzy NOT - returns the inverse (100 - value)
NOT 70     // Result: 30

// Fuzzy XOR - returns the absolute difference
XOR 70 30  // Result: 40
Advanced Fuzzy Logic
WofLang also supports more complex fuzzy operations:

NAND: NOT of AND (100 - min(a, b))
NOR: NOT of OR (100 - max(a, b))
IMPLY: Fuzzy implication (min(100, 100 - a + b))
NIMPLY: NOT of IMPLY (max(0, b - a))
EQUIV: Fuzzy equivalence
INHIBIT: Fuzzy inhibition (min(a, 100 - b))

Mathematical Operations
WofLang offers a comprehensive suite of mathematical operations, from basic arithmetic to advanced matrix operations and vector calculus.
Basic Operations

ADD: Addition (clamped to a maximum of 100)
SUB: Subtraction (clamped to a minimum of 0)
MUL: Multiplication (normalized by dividing by 100)
DIV: Division (normalized by multiplying by 100)
CMP: Comparison

Vector and Matrix Operations

VECTADD: Vector addition
VECTSUB: Vector subtraction
DOTPROD: Dot product of vectors
MTRXDET: Matrix determinant
MTRXINV: Matrix inversion
3X3DET: 3x3 matrix determinant
MTRXAND: Elementwise AND operation on matrices

Type Conversion

BIN2FUZ: Converts binary values (0 or 1) to fuzzy values (0 or 100)
FUZ2BIN: Converts fuzzy values to binary (threshold at 50)

Command Reference
WofLang commands are identified by numeric codes and can be executed directly or through their Unicode representations. Below is a reference of core commands:
Command CodeNameDescriptionSymbol0x01ADDAddition+0x02SUBSubtraction-0x03MULMultiplication×0x04DIVDivision÷0x05GTGreater Than>0x06LTLess Than<0x07EQEquals=0x08DNEDoes Not Equal≠0x09GTEGreater Than or Equal≥0x0ALTELess Than or Equal≤0x0BANDLogical AND∧0x0CORLogical OR∨0x0DXORExclusive OR⊕0x0ENOTLogical NOT¬0x0FNANDLogical NAND⊼0x10NORLogical NOR⊽0x18EQUIVLogical Equivalence≡0x19IDIdentity≃
Control Flow Commands
Command CodeNameDescription0x11IFConditional execution0x12THENExecute if condition is true0x13ELSEExecute if condition is false0x14WHILELoop while condition is true0x15FORLoop for specified iterations0x26BREAKExit current loop0x27ENDEnd block0x28EXITExit program0x2ADONESignal completion
Error Handling System
WofLang features a comprehensive error handling system defined in err_chk.h and err_chk.cpp. This system enables robust error detection, reporting, and recovery.
Error Codes
Error codes in WofLang are hexadecimal values that identify specific types of errors:
Error CodeNameDescription0x01ERR_HEADER_MISSINGHeader missing from file0x02ERR_BLOCK_ORDERBlock order incorrect0x03ERR_UNRECOGNIZEDUnrecognized command0x04ERR_TYPE_MISMATCHType mismatch0x05ERR_RUNTIMERuntime error0x11ERR_RUNTIME_DIV_ZERODivision by zero0x12ERR_RUNTIME_NULL_PTRNull pointer reference0x13ERR_RUNTIME_OVFArithmetic overflow
Error Checking Functions
WofLang provides various functions for checking potential error conditions:
cpp// Check if a header is valid
void checkHeader(const std::string& header);

// Check if block order is correct
void checkBlockOrder(int blockOrder);

// Check if a value is within bounds (0-100)
void checkBounds(double value);

// Check for division by zero
void checkDivision(double divisor);

// Check for type mismatches
void checkTypes(double a, double b);

// Check for mathematical errors
void checkMathErrors(double value);

// Check for floating-point errors
void checkFpErrors(double value);
Best Practices for Error Handling

Check inputs: Always validate inputs before performing operations
Use appropriate error checking functions: Choose the right checker for each operation
Handle errors gracefully: Provide meaningful error messages
Implement recovery mechanisms: When possible, recover from errors rather than exiting
Log errors: Maintain error logs for debugging purposes

Multi-threading Support
WofLang includes built-in support for multi-threaded programming through the utilities defined in utils.cpp. This allows for concurrent execution of tasks, improving performance for computationally intensive operations.
Thread Management
cpp// Create a new thread
void createThread(const std::function<void()>& task);

// Join all threads
void joinAllThreads();
Synchronization Primitives
WofLang provides standard synchronization primitives:

Mutex: For exclusive access to shared resources
Condition Variables: For thread signaling and coordination
Atomic Variables: For lock-free operations

Example: Multi-threaded Processing
// Create threads for processing
createThread(process_task1);
createThread(process_task2);

// Wait for all threads to complete
joinAllThreads();
Best Practices for Multi-threading

Avoid race conditions: Use mutexes to protect shared resources
Minimize lock contention: Keep critical sections small
Use atomic operations: When possible, use atomic operations instead of locks
Avoid deadlocks: Acquire locks in a consistent order
Scale appropriately: Don't create more threads than your system can handle efficiently

Plugin System
WofLang features a modular plugin system that allows extending functionality without modifying the core interpreter. This enables users to implement specialized mathematical functions or domain-specific operations.
Planned Plugin Modules

basicmath_plugin1: Basic arithmetic operations
logic_plugin1: Boolean logic operations
logic_plugin2: Fuzzy logic operations
advmath_plugin1: Advanced mathematical functions
advmath_plugin2: Additional advanced mathematical functions

Plugin Integration
Plugins are dynamically loaded at runtime and integrated with the main interpreter. Each plugin registers its commands with the interpreter, making them available to WofLang programs.
Creating Custom Plugins
To create a custom plugin:

Define the commands to be implemented
Implement the command functions
Create a registration function that adds commands to the interpreter
Compile as a shared library
Load the plugin using the plugin loader

String Handling and Parsing
WofLang provides comprehensive string handling and parsing capabilities through the string_parsing.h and string_parsing.cpp files. These functions are essential for processing textual data and parsing WofLang programs.
String Operations

concatenateStrings: Concatenate two strings
findSubstring: Find a substring within a string
replaceSubstring: Replace occurrences of a substring
toUpperCase: Convert a string to uppercase
toLowerCase: Convert a string to lowercase
splitString: Split a string based on a delimiter
trimString: Remove whitespace from the beginning and end of a string

String to Number Conversion
cpp// Convert a string to a double with error checking
double stringToDouble(const std::string& str);
Program Parsing
WofLang programs are parsed using functions that:

Read the program file
Identify sections (e.g., weights, network)
Parse operations
Execute commands based on the parsed operations

Memory Management
WofLang includes mechanisms for efficient memory management, ensuring optimal performance while preventing memory leaks and access violations.
Buffer Management
WofLang uses fixed-size buffers for SIMD-like operations, allowing for efficient vector processing.
cpp// Buffer for SIMD-like operations
std::vector<double> buffer(4, 0.0);
Best Practices for Memory Management

Use appropriate data structures: Choose data structures that match your memory access patterns
Avoid memory leaks: Ensure all allocated memory is properly freed
Minimize allocations: Reuse buffers when possible
Use SIMD operations: Leverage vector operations for better performance
Be aware of alignment: Ensure data is properly aligned for optimal performance

Performance Optimization
WofLang is designed with performance in mind, particularly for mathematical and logical operations.
Optimization Techniques

SIMD-like Operations: Vector operations for parallel processing
Efficient Algorithms: Optimized implementations of mathematical functions
Memory Locality: Data structures designed for cache-friendly access patterns
Multi-threading: Parallel execution for intensive computations
Compiler Optimizations: Code structured for effective compiler optimization

Measuring Performance
When optimizing WofLang programs, consider:

Execution Time: Measure how long operations take
Memory Usage: Monitor memory consumption
Cache Performance: Check for cache misses
Thread Utilization: Ensure efficient use of available cores

Appendix: Unicode Character Reference
WofLang uses Unicode characters to represent operations concisely. Below is a reference of commonly used characters:
CharacterUnicodeOperationCommand Code+U+002BAddition0x01-U+002DSubtraction0x02×U+00D7Multiplication0x03÷U+00F7Division0x04>U+003EGreater Than0x05<U+003CLess Than0x06=U+003DEquals0x07≠U+2260Does Not Equal0x08≥U+2265Greater Than or Equal0x09≤U+2264Less Than or Equal0x0A∧U+2227Logical AND0x0B∨U+2228Logical OR0x0C⊕U+2295Exclusive OR0x0D¬U+00ACLogical NOT0x0E⊼U+22BCLogical NAND0x0F⊽U+22BDLogical NOR0x10⇒U+21D2Implication0x43⇔U+21D4Equivalence0x49≡U+2261Identity0x4B

This Advanced User Guide for WofLang was created by RYO Modular/whispr.dev. For more information, visit ryo-modular.com or whispr.dev.