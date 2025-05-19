import matplotlib.pyplot as plt
import numpy as np

# Function to initialize the state of the cells
def initialize_cells(num_cells):
    cells = [0] * num_cells
    # Set the middle cell to 1 for initial state
    cells[num_cells // 2] = 1
    return cells

# Function to compute the next state using Rule 90 with wrap-around
def compute_next_state(cells):
    num_cells = len(cells)
    next_cells = [0] * num_cells
    for i in range(num_cells):
        # XOR of the left and right neighbors with wrap-around
        left = cells[i - 1]  # Wraps around on the left
        right = cells[(i + 1) % num_cells]  # Wraps around on the right
        next_cells[i] = left ^ right  # Rule 90 XOR operation
    return next_cells

# Plotting setup
num_cells = 11  # Number of cells in the automaton
cells = initialize_cells(num_cells)
fig, ax = plt.subplots()
line, = ax.plot(range(num_cells), cells, 'bo')
ax.set_ylim(-1, 2)
ax.set_xlim(0, num_cells - 1)
plt.title("Rule 90 Cellular Automaton with Wrap-Around")
plt.xlabel("Cell Index")
plt.ylabel("State (0 or 1)")

def update_plot(frame):
    global cells
    cells = compute_next_state(cells)  # Compute next state
    line.set_ydata(cells)  # Update plot data
    return line,

# Animation loop using FuncAnimation
from matplotlib.animation import FuncAnimation
ani = FuncAnimation(fig, update_plot, frames=100, interval=500, blit=True)
plt.show()
