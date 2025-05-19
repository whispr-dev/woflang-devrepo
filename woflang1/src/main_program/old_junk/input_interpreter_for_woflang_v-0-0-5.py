import re
import matplotlib.pyplot as plt

def interpret_command(command, variables):
    tokens = parse_tokens(command)
    print(f"Processing command: {command}")
    print(f"Tokens: {tokens}")

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

    if tokens[1] == '←':
        if '(' in tokens:
            var_name = tokens[0]
            expression = command.split('←', 1)[1].strip()
            variables[var_name] = evaluate_expression(expression, variables, operations)
        elif len(tokens) >= 4 and tokens[2] in operations:
            var_name = tokens[0]
            op = tokens[2]
            operand1 = get_value(tokens[3], variables)
            operand2 = get_value(tokens[4], variables)
            variables[var_name] = operations[op](operand1, operand2)
        else:
            var_name = tokens[0]
            value = tokens[2]
            variables[var_name] = get_value(value, variables)
    elif tokens[0] == 'IF':
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

    print(f"Variables: {variables}")
    return variables

def get_value(token, variables):
    """
    Returns the value of the token if it's a number or a variable.
    """
    try:
        return float(token)
    except ValueError:
        return variables.get(token, 0)

def evaluate_expression(expression, variables, operations):
    """
    Evaluates a mathematical expression using variables and operations defined.
    Handles parentheses and operator precedence.
    """
    # Replace variables with their values
    for var in variables:
        expression = re.sub(rf'\b{var}\b', str(variables[var]), expression)

    # Replace operations with Python equivalents
    expression = expression.replace('➕', '+').replace('➖', '-').replace('✖', '*').replace('➗', '/')

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
    pattern = r"(\b\w+_\w+\b|\b\w+\b|[➕➖✖➗∧∨⊕¬↑↓()←]|-?\d+\.?\d*)"
    tokens = re.findall(pattern, command)
    return tokens

# Store the history of variables for visualization
variables_history = []

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
    if command:
        variables = interpret_command(command, variables)
        variables_history.append(variables.copy())  # Save a copy of the current state

# Print the full history to debug
print("Full variables history:")
for index, vars in enumerate(variables_history):
    print(f"Step {index}: {vars}")

# Format data for plotting
formatted_data = {}
for step_index, step_vars in enumerate(variables_history):
    for var_name, var_value in step_vars.items():
        if isinstance(var_value, (int, float)):  # Check if the value is a number
            if var_name not in formatted_data:
                formatted_data[var_name] = []
            formatted_data[var_name].append((step_index, var_value))

# Plot the formatted data with Matplotlib
plt.figure(figsize=(10, 6))

for var_name, data_points in formatted_data.items():
    if data_points:
        # Unzip the data points for plotting
        x_vals, y_vals = zip(*data_points)
        plt.plot(x_vals, y_vals, label=var_name)

plt.title("Variable Changes Over Time")
plt.xlabel("Command Index")
plt.ylabel("Variable Value")
plt.legend()
plt.show()
