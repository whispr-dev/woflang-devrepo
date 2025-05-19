import re

def interpret_command(command, variables):
    # Split the command by spaces while keeping subscripts together
    tokens = parse_tokens(command)

    # Print tokens for debugging
    print(f"Processing command: {command}")
    print(f"Tokens: {tokens}")

    # Basic operation mapping with Unicode symbols
    operations = {
        '➕': lambda x, y: x + y,
        '➖': lambda x, y: x - y,
        '✖': lambda x, y: x * y,
        '➗': lambda x, y: x / y if y != 0 else float('inf'),
        '∧': lambda x, y: min(x, y),  # Analog AND
        '∨': lambda x, y: max(x, y),  # Analog OR
        '⊕': lambda x, y: abs(x - y),  # Analog XOR
        '¬': lambda x: -x,             # Analog NOT
        '↑': lambda x, y: -(min(x, y)), # Analog NAND
        '↓': lambda x, y: -(max(x, y)), # Analog NOR
    }

    if len(tokens) == 0:
        return variables

    # Command execution
    if tokens[1] == '←':  # Ensure we have a complete check here
        if '(' in tokens:  # Check if there is an expression to evaluate
            var_name = tokens[0]
            expression = command.split('←', 1)[1].strip()
            variables[var_name] = evaluate_expression(expression, variables, operations)
        elif len(tokens) >= 5 and tokens[2] in operations:
            var_name = tokens[0]
            op = tokens[2]
            operand1 = get_value(tokens[3], variables)
            operand2 = get_value(tokens[4], variables)
            variables[var_name] = operations[op](operand1, operand2)
        else:
            # Simple assignment, check if it's a variable or a number
            var_name = tokens[0]
            value = tokens[2]
            variables[var_name] = get_value(value, variables)
    elif tokens[0] == 'IF':
        # Correctly parse the IF condition
        condition_var = get_value(tokens[1], variables)
        condition_operator = tokens[2]
        condition_value = get_value(tokens[3], variables)
        then_index = tokens.index('THEN')
        else_index = tokens.index('ELSE')

        if evaluate_condition(condition_var, condition_operator, condition_value):
            true_assignment = tokens[then_index + 1:else_index]
            var_name = true_assignment[0]
            variables[var_name] = get_value(true_assignment[2], variables)
        else:
            false_assignment = tokens[else_index + 1:]
            var_name = false_assignment[0]
            variables[var_name] = get_value(false_assignment[2], variables)

    # Output the current state of variables for debugging
    print(f"Variables: {variables}")
    return variables

def get_value(token, variables):
    """
    Returns the value of the token if it's a number or a variable.
    """
    try:
        return float(token)
    except ValueError:
        return variables.get(token, 0)  # Default to 0 if the variable is not yet defined

def evaluate_expression(expression, variables, operations):
    """
    Evaluates a mathematical expression using variables and operations defined.
    Handles parentheses and operator precedence.
    """
    # Replace variable names in the expression with their current values
    for var in variables:
        expression = expression.replace(var, str(variables[var]))

    # Replace unicode operations with python equivalent
    expression = expression.replace('➕', '+').replace('➖', '-').replace('✖', '*').replace('➗', '/')

    # Safely evaluate the expression
    try:
        result = eval(expression)
    except ZeroDivisionError:
        result = float('inf')
    except Exception as e:
        print(f"Error evaluating expression '{expression}': {e}")
        result = None
    
    return result

def evaluate_condition(var, operator, value):
    if operator == '>':
        return var > value
    elif operator == '<':
        return var < value
    elif operator == '==':
        return var == value
    elif operator == '!=':
        return var != value
    elif operator == '>=':
        return var >= value
    elif operator == '<=':
        return var <= value
    else:
        return False

def parse_tokens(command):
    """
    Splits the command into tokens using regular expressions, recognizing multi-character symbols
    and operators, while treating underscores and subsequent characters as part of the variable name.
    """
    # Define a regular expression pattern for tokenizing the command
    pattern = r"(\b\w+_\w+\b|\b\w+\b|[➕➖✖➗∧∨⊕¬↑↓()←])"
    tokens = re.findall(pattern, command)
    return tokens

# Example Usage
commands = [
    "i_1 ← 20",
    "i_2 ← 10",
    "w_1 ← 0.5",
    "w_2 ← 1.0",
    "v_A ← (i_1 ✖ w_1) ➕ (i_2 ✖ w_2)",
    "theta_A ← 15",
    "v_A ← v_A ➖ theta_A",
    "IF v_A > 0 THEN a_A ← v_A ELSE a_A ← 0",
    "i_1_B ← -30",
    "i_2_B ← 40",
    "w_1_B ← -1.5",
    "w_2_B ← 0.75",
    "v_B ← (i_1_B ✖ w_1_B) ➕ (i_2_B ✖ w_2_B)",
    "theta_B ← 50",
    "v_B ← v_B ➖ theta_B",
    "IF v_B > 0 THEN a_B ← v_B ELSE a_B ← 0",
    "i_1_C ← a_A",
    "i_2_C ← a_B",
    "w_1_C ← 1.0",
    "w_2_C ← -0.5",
    "v_C ← (i_1_C ✖ w_1_C) ➕ (i_2_C ✖ w_2_C)",
    "theta_C ← -5",
    "v_C ← v_C ➖ theta_C",
    "IF v_C > 0 THEN a_C ← v_C ELSE a_C ← 0"
]

variables = {}
for command in commands:
    command = command.strip()
    if command:  # Check if the line is not empty
        variables = interpret_command(command, variables)
        print(f"Final Variables after command '{command}': {variables}")
