# v0.0.8 of fuzzy trees still has me pondering the bifurcation if i get this working

import matplotlib.pyplot as plt
import numpy as np
import random

# Constants representing cell states
EMPTY = 0
SAPLING = 1
STUNTED_TREE = 2

# Parameters
grid_size = 50          # Size of the grid
sapling_growth_prob = 0.1  # Adjusted growth probability
tree_decay_prob = 0.01     # Adjusted decay probability
initial_sapling_prob = 0.1 # Initial probability of each cell starting as a sapling
num_steps = 100             # Number of steps to run the CA

def initialize_grid(size, sapling_prob):
    """Initialize the grid with continuous values based on sapling_prob."""
    grid = np.zeros((size, size), dtype=float)
    for i in range(size):
        for j in range(size):
            # if random.random() < sapling_prob:
                # grid[i, j] = SAPLING
            grid[i, j] = np.random.rand() * sapling_prob
    return grid



def update_grid(grid, growth_prob, decay_prob):
    """Update the grid based on continuous growth and decay probabilities."""
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

            # if grid[i, j] == EMPTY:
                # Empty cells remain empty or could potentially become saplings
                # continue
            # elif grid[i, j] == SAPLING:
                # Saplings have a chance to grow into stunted trees
                # if random.random() < growth_prob:
                    # new_grid[i, j] = STUNTED_TREE
            # elif grid[i, j] == STUNTED_TREE:
                # Stunted trees have a chance to decay back to empty
                # if random.random() < decay_prob:
                    # new_grid[i, j] = EMPTY
    # return new_grid

def plot_grid(grid, step):
    """Plot the current state of the grid with a continuous colormap."""
    plt.imshow(grid, cmap='viridis', interpolation='nearest')
    plt.title(f'Sparse Forest of Stunted Trees - Step {step}')
    plt.colorbar(label='Cell State')
    plt.pause(0.1)

    # plt.clf()  # Clear the figure to avoid overlays
    # plt.imshow(grid, cmap='Greens', interpolation='nearest', vmin=EMPTY, vmax=STUNTED_TREE)
    # plt.colorbar(ticks=[EMPTY, SAPLING, STUNTED_TREE], label='Cell State')
    # plt.axis('equal')  # Ensure each cell is square

def run_simulation(grid_size, sapling_prob, growth_prob, decay_prob, num_steps):
    """Run the CA simulation."""
    grid = initialize_grid(grid_size, sapling_prob)
    plt.figure(figsize=(6, 6))

    for step in range(num_steps):
        plot_grid(grid, step)
        grid = update_grid(grid, growth_prob, decay_prob)

    plt.ioff()  # Turn off interactive mode
    plt.show()

if __name__ == "__main__":
    run_simulation(grid_size, initial_sapling_prob, sapling_growth_prob, tree_decay_prob, num_steps)
