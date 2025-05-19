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
num_cells = 11  # Number of cells
num_rows = 30   # Number of rows (generations) to display
variables = {}

# Initialize cells in Woflang
initial_commands = [
    f"cell_{i} ← 0" for i in range(num_cells)
]
initial_commands[num_cells // 2] = f"cell_{num_cells // 2} ← 1"  # Middle cell is '1'

# Interpret initial commands to set initial state
for command in initial_commands:
    interpret_command(command, variables)

# Initialize grid to store multiple rows of the automaton
grid = np.zeros((num_rows, num_cells))
grid[0, :] = [variables[f'cell_{i}'] for i in range(num_cells)]

# Plot setup
fig, ax = plt.subplots()
im = ax.imshow(grid, cmap='binary', interpolation='none')
ax.set_title("Rule 90 Cellular Automaton with Woflang")
plt.xlabel("Cell Index")
plt.ylabel("Generation")

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
    global variables, grid

    # Generate Rule 90 commands and interpret them
    rule90_commands = generate_rule90_commands(variables, num_cells)
    for command in rule90_commands:
        interpret_command(command, variables)

    # Shift the next generation to current cells and update the grid
    for i in range(num_cells):
        variables[f'cell_{i}'] = variables[f'next_cell_{i}']
        grid[frame % num_rows, i] = variables[f'cell_{i}']  # Update grid with the new state

    im.set_data(grid)
    return [im]

# Animation loop using FuncAnimation
from matplotlib.animation import FuncAnimation
ani = FuncAnimation(fig, update_plot, frames=num_rows, interval=500, blit=True, repeat=True)
plt.show()
