# v0.0.6 has the stunted forest of fuzzy trees code

import matplotlib.pyplot as plt
import numpy as np
import random

# Debug code begins
print("code initiated")

# Function to read automaton configuration from the input file
def read_configuration(filename):
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

        return initial_state, rule, num_rows  # Return all values if everything is correct

    except FileNotFoundError:
        print(f"Error: The file '{filename}' was not found.")
        return None
    except ValueError as e:
        print(f"Error: Incorrect file format or value error: {e}")
        return None
    
def update_grid(grid, growth_prob, decay_prob):
    """Update the grid based on the growth and decay probabilities."""
    new_grid = grid.copy()
    size = grid.shape[0]

    for i in range(size):
        for j in range(size):
            if grid[i, j] == EMPTY:
                continue
            elif grid[i, j] == SAPLING:
                if random.random() < growth_prob:
                    new_grid[i, j] = STUNTED_TREE
            elif grid[i, j] == STUNTED_TREE:
                if random.random() < decay_prob:
                    new_grid[i, j] = EMPTY
    return new_grid

def plot_grid(grid, step):
    """Plot the current state of the grid."""
    plt.imshow(grid, cmap='Greens', interpolation='nearest')
    plt.title(f'Sparse Forest of Stunted Trees - Step {step}')
    plt.colorbar(ticks=[EMPTY, SAPLING, STUNTED_TREE], label='Cell State')
    plt.pause(0.1)
    plt.clf()  # Clear the figure to avoid overlaps

# Constants representing cell states
EMPTY = 0
SAPLING = 1
STUNTED_TREE = 2

# Parameters
grid_size = 50          # Size of the grid
sapling_growth_prob = 0.2  # Probability of sapling growing into a stunted tree
tree_decay_prob = 0.05     # Probability of stunted tree decaying back to empty
initial_sapling_prob = 0.1 # Initial probability of each cell starting as a sapling
num_steps = 100             # Number of steps to run the CA

def initialize_grid(size, sapling_prob):
    """Initialize the rows with empty and sapling states based on sapling_prob."""
    grid = np.zeros((size, size), dtype=int)
    for i in range(size):
        for j in range(size):
            if random.random() < sapling_prob:
                grid[i, j] = SAPLING
    return grid

def run_simulation(grid_size, sapling_prob, growth_prob, decay_prob, num_steps):
    """Run the CA simulation."""
    grid = initialize_grid(grid_size, sapling_prob)
    plt.figure(figsize=(6, 6))  # Set the figure size to be more square

    for step in range(num_steps):
        plot_grid(grid, step)
        grid = update_grid(grid, growth_prob, decay_prob)

    plt.ioff()  # Turn off interactive mode
    plt.show()

if __name__ == "__main__":
    # Read configuration from input file
    input_file = 'input.wfl'
    config = read_configuration(input_file)
    
    if config is None:
        print("Failed to read configuration. Exiting program.")
    else:
        initial_state, rule, num_rows = config

        # Run the simulation
        run_simulation(grid_size, initial_sapling_prob, sapling_growth_prob, tree_decay_prob, num_steps)

# Debug code ends
print("code completed")
