
import re
import matplotlib.pyplot as plt

def interpret_command(command, variables):
    tokens = parse_tokens(command)
    print(f"Processing command: {command}")
    print(f"Tokens: {tokens}")

    operations = {
        '齊': lambda x, y: x + y,
        '隶': lambda x, y: x - y,
        '丶': lambda x, y: x * y,
        '丿': lambda x, y: x / y if y != 0 else float('inf'),
        '而': lambda x, y: min(x, y),  # Analog AND
        '或': lambda x, y: max(x, y),  # Analog OR
        '⊕': lambda x, y: abs(x - y),  # Analog XOR (Rule 90)
        '无': lambda x: -x,             # Analog NOT
        '无‍而': lambda x, y: -(min(x, y)), # Analog NAND
        '无‍或': lambda x, y: -(max(x, y)), # Analog NOR
    }

    if len(tokens) == 0:
        return variables

    if tokens[1] == '門':
        var_name = tokens[0]
        if len(tokens) == 3:
            # Simple assignment
            value = tokens[2]
            variables[var_name] = get_value(value, variables)
        elif len(tokens) == 5 and tokens[3] in operations:
            # Operation assignment
            op = tokens[3]
            operand1 = get_value(tokens[2], variables)
            operand2 = get_value(tokens[4], variables)
            # Check if operands are not None before performing operation
            if operand1 is not None and operand2 is not None:
                variables[var_name] = operations[op](operand1, operand2)
            else:
                variables[var_name] = None
        elif '(' in tokens:
            # Complex expression
            expression = command.split('門', 1)[1].strip()
            variables[var_name] = evaluate_expression(expression, variables, operations)
    elif tokens[0] == '若':
        condition_var = get_value(tokens[1], variables)
        condition_operator = tokens[2]
        condition_value = get_value(tokens[3], variables)
        then_index = tokens.index('则')
        else_index = tokens.index('另')

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
        return variables.get(token, None)

def evaluate_expression(expression, variables, operations):
    """
    Evaluates a mathematical expression using variables and operations defined.
    Handles parentheses and operator precedence.
    """
    # Replace variables with their values
    for var in variables:
        expression = re.sub(rf'\b{var}\b', str(variables[var]), expression)

    # Replace operations with Python equivalents
    expression = expression.replace('齊', '+').replace('隶', '-').replace('丶', '*').replace('丿', '/')

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
    # Correct the regex to handle decimal numbers and other tokens properly
    pattern = r"(\b\w+_\w+\b|\b\w+\b|[齊隶丶丿而或⊕无无‍而无‍或()門]|-?\d+\.\d+|-?\d+)"
    tokens = re.findall(pattern, command)
    tokens = [token for token in tokens if token.strip()]
    return tokens

# Read commands from the file 'input.wfl'
filename = 'input.wfl'  # Ensure 'input.wfl' exists in the same directory or provide the full path if it's in a different location

try:
    with open(filename, 'r', encoding='utf-8') as file:
        commands = file.readlines()
except FileNotFoundError:
    print(f"Error: The file '{filename}' was not found. Please check the file name and its location.")
    exit()

variables = {}
variables_history = []  # Initialize the history of variables

for command in commands:
    command = command.strip()
    if command:
        variables = interpret_command(command, variables)
        variables_history.append(variables.copy())  # Save a copy of the current state

# Additional code to handle the interpreted commands (if needed)

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
