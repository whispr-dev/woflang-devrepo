# v0.1.5_2 version w/ rule90 ca and scrollling readout graphing

import re
import matplotlib.pyplot as plt
import random
import numpy as np
import time


# Define the get_value function here
def get_value(token, variables):
    try:
        return float(token)
    except ValueError:
        return variables.get(token, None)

def interpret_command(command, variables):
    tokens = parse_tokens(command)
    print(f"Processing command: {command}")
    print(f"Tokens: {tokens}")

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

    if len(tokens) < 3:
        print(f"Skipping invalid command: {tokens}")
        return variables

    if tokens[1] == '門':
        var_name = tokens[0]
        if len(tokens) == 3:
            value = get_value(tokens[2], variables)  # Use get_value here
            variables[var_name] = value
        elif len(tokens) >= 4 and tokens[3] in operations:
            op = tokens[3]
            operand1 = get_value(tokens[2], variables)  # Use get_value here
            operand2 = get_value(tokens[4], variables)  # Use get_value here
            if operand1 is not None and operand2 is not None:
                variables[var_name] = operations[op](operand1, operand2)
            else:
                print(f"Skipping operation due to None values: {tokens}")
                variables[var_name] = None
        else:
            print(f"Invalid operation or operand: {tokens}")
    else:
        print(f"Unsupported command structure: {tokens}")

    return variables

# Initialize Rule 90 automaton
def initialize_automaton(length):
    # Create an initial row with all zeros except for a single 1 in the middle
    initial_row = np.zeros(length, dtype=int)
    initial_row[length // 2] = 1
    return initial_row

# Generate the next row in Rule 90 automaton
def rule90_next_row(current_row):
    # Apply Rule 90: XOR of left and right neighbors
    next_row = np.zeros_like(current_row)
    for i in range(1, len(current_row) - 1):
        next_row[i] = current_row[i-1] ^ current_row[i+1]
    return next_row

# Plotting the automaton row-by-row (scrolling)
def plot_automaton_scrolling(num_rows, row_length):
    # Initialize plot
    plt.ion()  # Turn on interactive mode for dynamic plotting
    fig, ax = plt.subplots()  # Initialize ax here

    # Initialize the first row
    current_row = initialize_automaton(row_length)
    
    for _ in range(num_rows):
        ax.clear()  # This will work because ax is now defined in this scope
        ax.imshow([current_row], cmap='binary', aspect='auto')
        plt.title('Scrolling Rule 90 Cellular Automaton')
        plt.draw()
        plt.pause(0.1)  # Pause for a short period to create scrolling effect
        
        # Generate the next row
        current_row = rule90_next_row(current_row)

    plt.ioff()  # Turn off interactive mode
    plt.show()

if __name__ == "__main__":
    # Parameters for the automaton
    num_rows = 100  # Number of rows to generate/display
    row_length = 101  # Length of each row

def parse_tokens(command):
    pattern = r"[-+]?\d*\.\d+|\b\d+\b|\b\w+_\w+\b|\b\w+\b|[齊隶丶丿而或⊕无无‍而无‍或()門]"
    return [token for token in re.findall(pattern, command) if token.strip()]

def main():
    filename = 'input.wfl'

    try:
        with open(filename, 'r', encoding='utf-8') as file:
            commands = [line.strip() for line in file.readlines() if line.strip()]
    except FileNotFoundError:
        print(f"Error: The file '{filename}' was not found.")
        exit()

    variables = {}
    variables_history = []  # List to store history of variables

    for command in commands:
        variables = interpret_command(command, variables)
        variables_history.append(variables.copy())

    # Plotting logic
    formatted_data = {}
    for step_index, step_vars in enumerate(variables_history):
        for var_name, var_value in step_vars.items():
            if isinstance(var_value, (int, float)):
                formatted_data.setdefault(var_name, []).append((step_index, var_value))

    # Check if formatted_data is not empty
    if formatted_data:
        plt.figure(figsize=(10, 6))
        for var_name, data_points in formatted_data.items():
            x_vals, y_vals = zip(*data_points)
            plt.plot(x_vals, y_vals, label=var_name)

        plt.title("Variable Changes Over Time")
        plt.xlabel("Command Index")
        plt.ylabel("Variable Value")
        plt.legend()
        plt.show()
    else:
        print("No data to plot.")

    for _ in range(num_rows):
        ax.clear()
        ax.imshow([current_row], cmap='binary', aspect='auto')
        plt.title('Scrolling Rule 90 Cellular Automaton')
        plt.draw()
        plt.pause(0.1)  # Pause for a short period to create scrolling effect
        
        # Generate the next row
        current_row = rule90_next_row(current_row)

if __name__ == "__main__":
    # Parameters for the automaton
    num_rows = 100  # Number of rows to generate/display
    row_length = 101  # Length of each row

    # Run the scrolling automaton
    plot_automaton_scrolling(num_rows, row_length)

    print("Script completed")

if __name__ == "__main__":
    main()
