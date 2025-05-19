# v0.0.2 of the cellular automata, the rule defined by the .wfl script
# currently only half working

import matplotlib.pyplot as plt
import numpy as np

# Debug code begins
print("code initiated")

# Function to read automaton configuration from the input file
def read_configuration(filename):
    # initial_state = []
    # rule = 90  # Default rule (can be overridden)
    # num_rows = 100  # Default number of rows (can be overridden)
    
    with open(filename, 'r', encoding='utf-8') as file:
        for line in file:
            line = line.strip()
            if line.startswith("initial_state:"):
                initial_state = list(map(int, line.split(":")[1].split(",")))
            elif line.startswith("rule:"):
                rule = int(line.split(":")[1].strip())
            elif line.startswith("rows:"):
                num_rows = int(line.split(":")[1].strip())
    
       # return initial_state, rule, num_rows

# Generate the next row in a Rule 90 automaton
def rule90_next_row(current_row):
    next_row = np.zeros_like(current_row)
    for i in range(1, len(current_row) - 1):
        next_row[i] = current_row[i-1] ^ current_row[i+1]  # XOR operation
    return next_row

# Debug @gen next rule def pre def plotting
print("initial beesknees")

# Plotting the automaton row-by-row (scrolling)
def plot_automaton_scrolling(initial_state, rule, num_rows):
    plt.ion()  # Turn on interactive mode for dynamic plotting
    fig, ax = plt.subplots()

    # Initialize with the initial state
    current_row = np.array(initial_state)
    all_rows = np.zeros((num_rows, len(initial_state)))

    # Set initial row in the plot
    all_rows[-1] = current_row  # Place the initial row at the bottom

    # Create the initial plot
    im = ax.imshow(all_rows, cmap='binary', aspect='auto', interpolation='none')
    plt.title('Scrolling Rule 90 Cellular Automaton')

    # Correcting axes limits
    ax.set_xlim(0, len(current_row))
    ax.set_ylim(0, num_rows)  # Adjust the ylim to go from 0 to num_rows

    # Debug message
    print("plotting begun? plots and trucks afoot!")

    # Plotting and updating the automaton
    for step in range(1, num_rows):
        try:
            # Generate the next row based on the rule
            current_row = rule90_next_row(current_row)

            # Use np.roll to shift the plot and add new row at the end
            all_rows = np.roll(all_rows, -1, axis=0)
            all_rows[-1] = current_row

            # Update plot data and redraw
            im.set_array(all_rows)
            plt.draw()
            plt.pause(0.1)  # Pause for a short period to create scrolling effect
        except Exception as e:
            print(f"Error generating next row: {e}")
            break  # Exit loop if there's an error

    plt.ioff()  # Turn off interactive mode
    plt.show()

if __name__ == "__main__":
    # Read configuration from input file
    input_file = 'input.wfl'
    initial_state, rule, num_rows = read_configuration(input_file)
    def read_configuration(filename):
        initial_state = []
    rule = None  # Initialize rule as None
    num_rows = None  # Initialize num_rows as None
    
    try:
        with open(filename, 'r', encoding='utf-8') as file:
            for line in file:
                line = line.strip()
                if line.startswith("initial_state:"):
                    initial_state = list(map(int, line.split(":")[1].split(",")))
                elif line.startswith("rule:"):
                    rule = int(line.split(":")[1].strip())
                elif line.startswith("rows:"):
                    num_rows = int(line.split(":")[1].strip())
                    
        if rule is None or num_rows is None:  # Check if rule or num_rows are still None
            print("Error: Missing rule or rows in the configuration file.")
            return None  # Return None if the configuration is incomplete

    except FileNotFoundError:
        print(f"Error: The file '{filename}' was not found.")
        return None
    except ValueError as e:
        print(f"Error: Incorrect file format or value error: {e}")
        return None
    
    return initial_state, rule, num_rows  # Return all values if everything is correct

# Run the scrolling automaton
plot_automaton_scrolling(initial_state, rule, num_rows)

# Debug code ends
print("code completed")
