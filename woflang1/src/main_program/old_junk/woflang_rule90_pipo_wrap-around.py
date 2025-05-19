import matplotlib.pyplot as plt
import numpy as np
import re

# Woflang interpreter functions from your script
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
        '⊕': lambda x, y: abs(x - y),  # Analog XOR (Rule 90)
        '¬': lambda x: -x,             # Analog NOT
        '↑': lambda x, y: -(min(x, y)), # Analog NAND
        '↓': lambda x, y: -(max(x, y)), # Analog NOR
    }

    if len(tokens) == 0:
        return variables

    if tokens[1] == '←':
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
            variables[var_name] = operations[op](operand1, operand2)
        elif '(' in tokens:
            # Complex expression
            expression = command.split('←', 1)[1].strip()
            variables[var_name] = evaluate_expression(expression, variables, operations)

    print(f"Variables after command: {variables}")
    return variables

def get_value(token, variables):
    try:
        return float(token)
    except ValueError:
        return variables.get(token, 0)

def evaluate_expression(expression, variables, operations):
    for var in variables:
        expression = re.sub(rf'\b{var}\b', str(variables[var]), expression)
    expression = expression.replace('➕', '+').replace('➖', '-').replace('✖', '*').replace('➗', '/')
    try:
        result = eval(expression)
    except ZeroDivisionError:
        result = float('inf')
    except Exception as e:
        print(f"Error evaluating expression '{expression}': {e}")
        result = None
    return result

def parse_tokens(command):
    pattern = r"(\b\w+_\w+\b|\b\w+\b|[➕➖✖➗∧∨⊕¬↑↓()←]|-?\d+\.?\d*)"
    tokens = re.findall(pattern, command)
    return tokens

# Initial setup
num_cells = 11
variables = {}

# Initialize cells in Woflang
initial_commands = [
    f"cell_{i} ← 0" for i in range(num_cells)
]
initial_commands[num_cells // 2] = f"cell_{num_cells // 2} ← 1"  # Middle cell is '1'

# Interpret initial commands to set initial state
for command in initial_commands:
    interpret_command(command, variables)

# Plot setup
fig, ax = plt.subplots()
line, = ax.plot(range(num_cells), [variables[f'cell_{i}'] for i in range(num_cells)], 'bo')
ax.set_ylim(-1, 2)
ax.set_xlim(0, num_cells - 1)
plt.title("Rule 90 Cellular Automaton in Real-Time with Woflang")
plt.xlabel("Cell Index")
plt.ylabel("State (0 or 1)")

# Rule 90 commands in Woflang with wrap-around
def generate_rule90_commands(variables, num_cells):
    commands = []
    for i in range(num_cells):
        left_neighbor = f"cell_{(i - 1) % num_cells}"  # Wrap-around left neighbor
        right_neighbor = f"cell_{(i + 1) % num_cells}"  # Wrap-around right neighbor
        commands.append(f"next_cell_{i} ← {left_neighbor} ⊕ {right_neighbor}")
    return commands

# Update plot function
def update_plot(frame):
    global variables

    # Generate Rule 90 commands and interpret them
    rule90_commands = generate_rule90_commands(variables, num_cells)
    for command in rule90_commands:
        interpret_command(command, variables)

    # Shift the next generation to current cells
    for i in range(num_cells):
        variables[f'cell_{i}'] = variables[f'next_cell_{i}']
    
    # Update plot
    line.set_ydata([variables[f'cell_{i}'] for i in range(num_cells)])
    return line,

# Animation loop using FuncAnimation
from matplotlib.animation import FuncAnimation
ani = FuncAnimation(fig, update_plot, frames=100, interval=500, blit=True)
plt.show()
