def interpret_command(command, variables):
    # Split the command by spaces
    tokens = command.split()

    # Basic operation mapping with Unicode symbols
    operations = {
        '➕': lambda x, y: x + y,
        '➖': lambda x, y: x - y,
        '✖': lambda x, y: x * y,
        '➗': lambda x, y: x / y if y != 0 else 'Infinity',
        '∧': lambda x, y: min(x, y),  # Analog AND
        '∨': lambda x, y: max(x, y),  # Analog OR
        '⊕': lambda x, y: abs(x - y),  # Analog XOR
        '¬': lambda x: -x,             # Analog NOT
        '↑': lambda x, y: -(min(x, y)), # Analog NAND
        '↓': lambda x, y: -(max(x, y)), # Analog NOR
    }

    # Command execution
    if tokens[1] == '←':
        if tokens[2] in operations:
            var_name = tokens[0]
            op = tokens[2]
            operand1 = variables.get(tokens[3], float(tokens[3]))
            operand2 = variables.get(tokens[4], float(tokens[4]))
            variables[var_name] = operations[op](operand1, operand2)
        else:
            # Simple assignment
            var_name = tokens[0]
            variables[var_name] = float(tokens[2])
    
    # Output the current state of variables for debugging
    return variables

# Example Usage
commands = [
    "ι₁ ← 20",
    "ι₂ ← 10",
    "ω₁ ← 0.5",
    "ω₂ ← 1.0",
    "ν_A ← (ι₁ ✖ ω₁) ➕ (ι₂ ✖ ω₂)",
    "θ_A ← 15",
    "ν_A ← ν_A ➖ θ_A",
    "IF ν_A > 0 THEN α_A ← ν_A ELSE α_A ← 0"
]

variables = {}
for command in commands:
    variables = interpret_command(command, variables)
    print(variables)
