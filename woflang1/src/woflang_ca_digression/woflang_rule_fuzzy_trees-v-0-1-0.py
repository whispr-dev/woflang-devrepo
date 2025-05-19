import matplotlib.pyplot as plt
import numpy as np
import random

# Debug code begins
print("code initiated")

# Function to read automaton configuration from the input file
def read_configuration(filename):
    initial_state = []
    rule = None
    num_rows = None
    
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
                    
        if rule is None or num_rows is None:
            print("Error: Missing rule or rows in the configuration file.")
            return None
    except FileNotFoundError:
        print(f"Error: The file '{filename}' was not found.")
        return None
    except ValueError as e:
        print(f"Error: Incorrect file format or value error: {e}")
        return None
    
    return initial_state, rule, num_rows

# Generate the next row in a Rule 90 automaton
def update_grid(grid, growth_prob, decay_prob):
    new_grid = grid.copy()
    size = grid.shape[0]

    for i in range(size):
        for j in range(size):
            if grid[i, j] > 0:  # If not empty
                if grid[i, j] < 1.0:  # If a sapling, grow towards 1.0
                    new_grid[i, j] += growth_prob * (1.0 - grid[i, j])
                elif grid[i, j] >= 1.0:  # If a stunted tree, decay towards 0
                    new_grid[i, j] -= decay_prob * grid[i, j]
                
                # Clamp values between 0 and 2 for visualization
                new_grid[i, j] = max(0.0, min(new_grid[i, j], 2.0))
    
    return new_grid

def initialize_grid(size, sapling_prob):
    """Initialize the grid with continuous values based on sapling_prob."""
    grid = np.zeros((size, size), dtype=float)
    for i in range(size):
        for j in range(size):
            grid[i, j] = np.random.rand() * sapling_prob
    return grid

def plot_grid(grid, step):
    """Plot the current state of the grid with a continuous colormap."""
    plt.imshow(grid, cmap='viridis', interpolation='nearest')
    plt.title(f'Sparse Forest of Stunted Trees - Step {step}')
    plt.colorbar(label='Cell State')
    plt.draw()
    plt.pause(0.1)

def run_simulation(grid_size, sapling_prob, growth_prob, decay_prob, num_steps):
    """Run the CA simulation."""
    grid = initialize_grid(grid_size, sapling_prob)
    plt.figure()

    for step in range(num_steps):
        plt.clf()  # Clear the plot before drawing the new grid
        plot_grid(grid, step)
        grid = update_grid(grid, growth_prob, decay_prob)

    plt.ioff()  # Turn off interactive mode
    plt.show()

# Constants and parameters for the simulation
EMPTY = 0
SAPLING = 1
STUNTED_TREE = 2

grid_size = 50          # Size of the grid
sapling_growth_prob = 0.2  # Probability of sapling growing into a stunted tree
tree_decay_prob = 0.05     # Probability of stunted tree decaying back to empty
initial_sapling_prob = 0.1 # Initial probability of each cell starting as a sapling
num_steps = 100             # Number of steps to run the CA

if __name__ == "__main__":
    # Read configuration from input file
    input_file = 'input.wfl'
    config = read_configuration(input_file)
    
    if config is None:
        print("Failed to read configuration. Exiting program.")
    else:
        initial_state, rule, num_rows = config
        run_simulation(grid_size, initial_sapling_prob, sapling_growth_prob, tree_decay_prob, num_steps)

# Debug code ends
print("code completed")
