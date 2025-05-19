import os
import time
import re

# Function to interpret commands and initialize variables
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
        else:
            print(f"Invalid operation or operand: {tokens}")
    else:
        print(f"Unsupported command structure: {tokens}")

    return variables

# Parse tokens from command
def parse_tokens(command):
    pattern = r"[-+]?\d*\.\d+|\b\d+\b|\b\w+_\w+\b|\b\w+\b|[齊隶丶丿而或⊕无无‍而无‍或()門]"
    return [token for token in re.findall(pattern, command) if token.strip()]

# Convert variable values to integers (0 or 1) to initialize automaton
def convert_to_binary(variables, size):
    # Convert variables to binary (0 or 1)
    automaton = [0] * size
    for var, value in variables.items():
        index = int(re.search(r'\d+', var).group()) if re.search(r'\d+', var) else 0
        automaton[index % size] = 1 if value > 50 else 0
    return automaton

# Apply Rule 90 to compute the next state
def rule_90_step(current_state):
    size = len(current_state)
    new_state = [0] * size
    for i in range(size):
        left = current_state[(i - 1) % size]
        right = current_state[(i + 1) % size]
        new_state[i] = left ^ right  # XOR operation
    return new_state

# Display the automaton state in real-time
def display_automaton(state):
    print("".join('#' if cell else '.' for cell in state))

def main():
    # Read input from file
    filename = 'input.wfl'
    try:
        with open(filename, 'r', encoding='utf-8') as file:
            commands = [line.strip() for line in file.readlines() if line.strip()]
    except FileNotFoundError:
        print(f"Error: The file '{filename}' was not found.")
        return

    # Initialize variables from commands
    variables = {}
    for command in commands:
        variables = interpret_command(command, variables)

    # Initialize automaton size and state
    size = 30  # Choose a size for the automaton
    automaton = convert_to_binary(variables, size)

    # Continuously update and display the automaton
    print("Real-time Rule 90 Cellular Automaton:")
    while True:
        os.system('cls' if os.name == 'nt' else 'clear')
        display_automaton(automaton)
        automaton = rule_90_step(automaton)
        time.sleep(0.1)  # Adjust the speed of scrolling

if __name__ == "__main__":
    main()
