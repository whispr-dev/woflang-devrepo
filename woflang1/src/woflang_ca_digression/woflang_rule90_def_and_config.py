# v0.0.1 of the cellular automata, the rule defined by the .wfl script
# currently only half working.

# debug code begins
print("code initiated")

import matplotlib.pyplot as plt
import numpy as np

# Function to read automaton configuration from the input file
def read_configuration(filename):
    initial_state = []
    rule = 90  # Default rule (can be overridden)
    num_rows = 100  # Default number of rows (can be overridden)
    
    with open(filename, 'r', encoding='utf-8') as file:
        for line in file:
            line = line.strip()
            if line.startswith("initial_state:"):
                initial_state = list(map(int, line.split(":")[1].split(",")))
            elif line.startswith("rule:"):
                rule = int(line.split(":")[1].strip())
            elif line.startswith("rows:"):
                num_rows = int(line.split(":")[1].strip())
    
    return initial_state, rule, num_rows

# Generate the next row in a Rule 90 automaton
def rule90_next_row(current_row):
    next_row = np.zeros_like(current_row)
    for i in range(1, len(current_row) - 1):
        next_row[i] = current_row[i-1] ^ current_row[i+1]  # XOR operation
    return next_row

# debug @gen next rule def pre def plotting
print("initial beesknees")

# Plotting the automaton row-by-row (scrolling)
def plot_automaton_scrolling(initial_state, rule, num_rows):
    plt.ion()  # Turn on interactive mode for dynamic plotting
    fig, ax = plt.subplots()

    current_row = np.array(initial_state)

    # Plotting and updating the automaton
    for _ in range(num_rows):
        ax.clear()
        ax.imshow([current_row], cmap='binary', aspect='auto')
        plt.title('Scrolling Rule 90 Cellular Automaton')
        plt.draw()
        plt.pause(0.1)  # Pause for a short period to create scrolling effect
        
        try:
            # Generate the next row based on the rule
            current_row = rule90_next_row(current_row)
        except Exception as e:
            print(f"Error generating next row: {e}")
            break  # Exit loop if there's an error

    # plt.ioff()  # Turn off interactive mode
    plt.show()

# reporting progress sir.
print("pllotting begun? pots and trucks afoot!")

if __name__ == "__main__":
    # Read configuration from input file
    input_file = 'input.wfl'
    initial_state, rule, num_rows = read_configuration(input_file)

    # Run the scrolling automaton
    plot_automaton_scrolling(initial_state, rule, num_rows)

# debug code ends
print("code completed")
