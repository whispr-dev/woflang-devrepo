def interpret_command(command):
    # Split the command by spaces
    tokens = command.split()
    
    # Initialize variable dictionary
    variables = {}

    # Basic operation mapping
    operations = {
        '➕': lambda x, y: x + y,
        '➖': lambda x, y: x - y,
        '✖': lambda x, y: x * y,
        '➗': lambda x, y: x / y if y != 0 else 'Infinity',
        '∧': lambda x, y: min(x, y),  # AND: Analog logical AND can be a minimum function
        '∨': lambda x, y: max(x, y),  # OR: Analog logical OR can be a maximum function
        '⊕': lambda x, y: abs(x - y),  # XOR: Analog XOR as absolute difference
        '¬': lambda x: -x,             # NOT: Analog negation
        '↑': lambda x, y: -(min(x, y)), # NAND: Analog NAND as negated minimum
        '↓': lambda x, y: -(max(x, y)), # NOR: Analog NOR as negated maximum
    }

    # Command execution
    if tokens[1] == '←':
        if tokens[2] in operations:
            var_name = tokens[0]
            op = tokens[2]
            operand1 = variables[tokens[3]] if tokens[3] in variables else float(tokens[3])
            operand2 = variables[tokens[4]] if tokens[4] in variables else float(tokens[4])
            variables[var_name] = operations[op](operand1, operand2)
        else:
            # Simple assignment
            var_name = tokens[0]
            variables[var_name] = float(tokens[2])
    
    # Output the current state of variables for debugging
    return variables

# Example Usage
commands = [
    "A ← 20",
    "B ← -30",
    "A ← A ➕ B",
    "C ← 40",
    "C ← C ✖ 2"
]

for command in commands:
    print(interpret_command(command))
