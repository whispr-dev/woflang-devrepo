# this versions from hereon [i.e. v0.1.1] use analog logic!

print("Script started")

import re
import matplotlib.pyplot as plt


def interpret_command(command, variables):
    tokens = parse_tokens(command)
    print(f"Processing command: {command}")
    print(f"Tokens: {tokens}")

    # Debugging after token parsing
    if len(tokens) < 3:
        print(f"Skipping invalid command: {tokens}")
        return variables

    operations = {
        '齊': lambda x, y: min(max(x + y, 0), 100),
        '隶': lambda x, y: min(max(x - y, 0), 100),
        '丶': lambda x, y: min(max(x * y / 100, 0), 100),
        '丿': lambda x, y: min(max((x / y) if y != 0 else 0, 0), 100),
        '而': lambda x, y: min(x, y),
        '或': lambda x, y: max(x, y),
        '⊕': lambda x, y: abs(x - y),
        '无': lambda x: 100 - x,
        '无‍而': lambda x, y: 100 - min(x, y),
        '无‍或': lambda x, y: 100 - max(x, y),
    }

    if tokens[1] == '門':
        var_name = tokens[0]
        if len(tokens) == 3:
            value = get_value(tokens[2], variables)
            variables[var_name] = value
        elif len(tokens) >= 4 and tokens[3] in operations:
            op = tokens[3]
            operand1 = get_value(tokens[2], variables)
            operand2 = get_value(tokens[4], variables)
            if operand1 is not None and operand2 is not None:
                variables[var_name] = operations[op](operand1, operand2)
            else:
                print(f"Skipping operation due to None values: {tokens}")
                variables[var_name] = None
    # Further conditional command handling

    return variables

def get_value(token, variables):
    try:
        return float(token)
    except ValueError:
        return variables.get(token, None)

def normalize_value(value):
    """Ensure the value is within the 0 to 1 range."""
    if value is None:
        return None
    return min(max(value, 0), 1)

def evaluate_expression(expression, variables, operations):
    for var in variables:
        expression = re.sub(rf'\b{var}\b', str(variables[var]), expression)
    try:
        return eval(expression)
    except Exception as e:
        print(f"Error evaluating expression '{expression}': {e}")
        return None

def evaluate_condition(var, operator, value):
    if var is None or value is None:
        return False
    if operator == '大':
        return var > value
    elif operator == '小':
        return var < value
    elif operator == '卜':
        return var == value
    elif operator == '丨':
        return var != value
    elif operator == '走':
        return var >= value
    elif operator == '夊':
        return var <= value
    return False

def parse_tokens(command):
    # Adjust the regex to correctly capture floating-point numbers with more precision
    pattern = r"(\b\w+_\w+\b|\b\w+\b|[齊隶丶丿而或⊕无无‍而无‍或()門]|-?\d+\.\d*|-?\d+)"
    return [token for token in re.findall(pattern, command) if token.strip()]

filename = 'input.wfl'

try:
    with open(filename, 'r', encoding='utf-8') as file:
        commands = [line.strip() for line in file.readlines() if line.strip()]
except FileNotFoundError:
    print(f"Error: The file '{filename}' was not found.")
    exit()

variables = {}
variables_history = []

print("Debugging Variable Assignment:")
for var, value in variables.items():
    print(f"{var} = {value}")

for command in commands:
    print(f"Processing command: {command}")
    variables = interpret_command(command, variables)
    variables_history.append(variables.copy())

print("Debugging Variable States:")
for step_index, step_vars in enumerate(variables_history):
    print(f"Step {step_index}: {step_vars}")

print("Full variables history:")
for index, vars in enumerate(variables_history):
    print(f"Step {index}: {vars}")

formatted_data = {}
for step_index, step_vars in enumerate(variables_history):
    for var_name, var_value in step_vars.items():
        if isinstance(var_value, (int, float)):
            formatted_data.setdefault(var_name, []).append((step_index, var_value))

plt.figure(figsize=(10, 6))
for var_name, data_points in formatted_data.items():
    x_vals, y_vals = zip(*data_points)
    plt.plot(x_vals, y_vals, label=var_name)

plt.title("Variable Changes Over Time")
plt.xlabel("Command Index")
plt.ylabel("Variable Value")
plt.legend()
plt.show()

print("Script completed")
