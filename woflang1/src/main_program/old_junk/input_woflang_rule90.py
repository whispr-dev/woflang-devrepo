import re
import matplotlib.pyplot as plt
import matplotlib.animation as animation

def interpret_command(command, variables):
    tokens = parse_tokens(command)
    print(f"Processing command: {command}")
    print(f"Tokens: {tokens}")

    operations = {
        '➕': lambda x, y: x + y,
        '➖': lambda x, y: x - y,
        '✖': lambda x, y: x * y,
        '➗': lambda x, y: x / y if y != 0 else float('inf'),
        '⊕': lambda x, y: 1 if (x != y) else 0  # Correct XOR logic for Rule 90
    }

    if len(tokens) == 0:
        return variables

    if tokens[1] == '←':
        var_name = tokens[0]
        if len(tokens) == 3:  # Simple assignment like `a ← 1`
            value = get_value(tokens[2], variables)
            variables[var_name] = value  # Ensure the assignment is made to the dictionary
        elif len(tokens) > 3:  # Operations like `a ← b ⊕ c`
            operand1 = get_value(tokens[2], variables)
            op = tokens[3]
            operand2 = get_value(tokens[4], variables)
            variables[var_name] = operations[op](operand1, operand2)

    print(f"Variables after command: {variables}")  # Print variables after command to debug
    return variables

def get_value(token, variables):
    try:
        return float(token)
    except ValueError:
        return variables.get(token, 0)

def evaluate_expression(expression, variables, operations):
    for var in variables:
        expression = re.sub(rf'\b{var}\b', str(variables[var]), expression)
    expression = expression.replace('➕', '+').replace('➖', '-').replace('✖', '*').replace('➗', '/').replace('⊕', '^')
    try:
        result = eval(expression)
    except ZeroDivisionError:
        result = float('inf')
    except Exception as e:
        print(f"Error evaluating expression '{expression}': {e}")
        result = None
    return result

def parse_tokens(command):
    pattern = r"(\b\w+_\w+\b|\b\w+\b|[➕➖✖➗⊕()←]|-?\d+\.?\d*)"
    tokens = re.findall(pattern, command)
    return tokens

# Store the history of variables for visualization
variables_history = []

# Initial grid setup for Rule 90
initial_grid = [
    "cell_0 ← 0", "cell_1 ← 0", "cell_2 ← 0", "cell_3 ← 0", "cell_4 ← 0",
    "cell_5 ← 1", "cell_6 ← 0", "cell_7 ← 0", "cell_8 ← 0", "cell_9 ← 0", "cell_10 ← 0"
]

variables = {}
commands = initial_grid

for command in commands:
    command = command.strip()
    if command:
        variables = interpret_command(command, variables)
        variables_history.append(variables.copy())

# Function to update cells according to Rule 90
def rule90_update_commands():
    return [
        "next_cell_0 ← cell_1 ⊕ cell_0",
        "next_cell_1 ← cell_2 ⊕ cell_0",
        "next_cell_2 ← cell_3 ⊕ cell_1",
        "next_cell_3 ← cell_4 ⊕ cell_2",
        "next_cell_4 ← cell_5 ⊕ cell_3",
        "next_cell_5 ← cell_6 ⊕ cell_4",
        "next_cell_6 ← cell_7 ⊕ cell_5",
        "next_cell_7 ← cell_8 ⊕ cell_6",
        "next_cell_8 ← cell_9 ⊕ cell_7",
        "next_cell_9 ← cell_10 ⊕ cell_8",
        "next_cell_10 ← cell_10 ⊕ cell_9",
        "cell_0 ← next_cell_0", "cell_1 ← next_cell_1", "cell_2 ← next_cell_2",
        "cell_3 ← next_cell_3", "cell_4 ← next_cell_4", "cell_5 ← next_cell_5",
        "cell_6 ← next_cell_6", "cell_7 ← next_cell_7", "cell_8 ← next_cell_8",
        "cell_9 ← next_cell_9", "cell_10 ← next_cell_10"
    ]

# Set up Matplotlib for real-time animation
fig, ax = plt.subplots()
line, = ax.plot(range(11), [variables.get(f'cell_{i}', 0) for i in range(11)], 'bo')

def update(frame):
    global variables
    commands = rule90_update_commands()
    for command in commands:
        variables = interpret_command(command, variables)
    y_vals = [variables.get(f'cell_{i}', 0) for i in range(11)]
    line.set_ydata(y_vals)
    line.set_xdata(range(len(y_vals)))
    variables_history.append(variables.copy())
    ax.set_ylim(-1, 2)
    ax.set_xlim(-0.5, 10.5)
    return line,

ani = animation.FuncAnimation(fig, update, frames=range(50), blit=False, interval=500, repeat=False)

plt.title("Rule 90 Cellular Automaton in Real-Time with Woflang")
plt.xlabel("Cell Index")
plt.ylabel("State (0 or 1)")
plt.show()
