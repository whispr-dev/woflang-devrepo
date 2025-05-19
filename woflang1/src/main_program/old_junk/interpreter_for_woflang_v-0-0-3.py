def interpret_command(command, variables):
    # Split the command by spaces while keeping subscripts together
    tokens = parse_tokens(command)

    # Basic operation mapping with Unicode symbols
    operations = {
        '+': lambda x, y: x + y,
        '-': lambda x, y: x - y,
        '*': lambda x, y: x * y,
        '/': lambda x, y: x / y if y != 0 else 'Infinity',
        '∧': lambda x, y: min(x, y),  # Analog AND
        'v': lambda x, y: max(x, y),  # Analog OR
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

def parse_tokens(command):
    """
    Splits the command into tokens, treating underscores and subsequent characters as part of the variable name.
    """
    tokens = []
    current_token = ""
    inside_subscript = False

    for char in command:
        if char == ' ' and not inside_subscript:
            if current_token:
                tokens.append(current_token)
                current_token = ""
        elif char == '_':
            current_token += char
            inside_subscript = True
        elif inside_subscript and char.isalnum():
            current_token += char
        else:
            if current_token:
                tokens.append(current_token)
            current_token = char
            inside_subscript = False

    if current_token:
        tokens.append(current_token)

    return tokens

# Example Usage
commands = [
''; Define inputs (i) and weights (w) for Neuron A (v_A)
i_1 ← 20
i_2 ← 10
w_1 ← 0.5
w_2 ← 1.0

; Weighted sum for Neuron A (v_A)
v_A ← (i_1 ✖ w_1) + (i_2 ✖ w_2)

; Threshold activation (a) for Neuron A (v_A)
theta_A ← 15
v_A ← v_A - theta_A
IF v_A > 0 THEN a_A ← v_A ELSE a_A ← 0

; Define inputs (i) and weights (w) for Neuron B (v_B)
i_1_B ← -30
i_2_B ← 40
w_1_B ← -1.5
w_2_B ← 0.75

; Weighted sum for Neuron B (v_B)
v_B ← (i_1_B ✖ w_1_B) + (i_2_B ✖ w_2_B)

; Threshold activation (a) for Neuron B (v_B)
theta_B ← 50
v_B ← v_B - theta_B
IF v_B > 0 THEN a_B ← v_B ELSE a_B ← 0

; Neuron C (v_C) receives input from Neuron A (v_A) and Neuron B (v_B)
i_1_C ← a_A
i_2_C ← a_B
w_1_C ← 1.0
w_2_C ← -0.5

; Weighted sum for Neuron C (v_C)
v_C ← (i_1_C ✖ w_1_C) + (i_2_C ✖ w_2_C)

; Threshold activation (σ) for Neuron C (v_C)
theta_C ← -5
v_C ← v_C ➖ theta_C
IF v_C > 0 THEN a_C ← v_C ELSE a_C ← 0'
]

variables = {}
for command in commands:
    variables = interpret_command(command, variables)
    print(variables)
