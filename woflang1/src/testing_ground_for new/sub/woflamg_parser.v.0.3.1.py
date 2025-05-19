import re
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.animation import FuncAnimation

class CellularAutomaton:
    def __init__(self):
        self.initial_state = []
        self.rule_number = 0
        self.num_rows = 0
        self.current_row = 0
        self.grid = None
        
        # Visualization
        plt.ion()  # Turn on interactive mode
        self.fig, self.ax = plt.subplots(figsize=(10, 10))
        self.img = None
        
    def load_configuration(self, filename):
        """Load cellular automaton configuration from file"""
        try:
            with open(filename, 'r') as file:
                for line in file:
                    line = line.strip()
                    if line.startswith('#') or not line:
                        continue
                        
                    if line.startswith('initial_state:'):
                        # Parse initial state
                        state_str = line.split(':', 1)[1].strip()
                        self.initial_state = [int(x.strip()) for x in state_str.split(',')]
                        
                    elif line.startswith('rule:'):
                        # Parse rule number
                        self.rule_number = int(line.split(':', 1)[1].strip())
                        
                    elif line.startswith('rows:'):
                        # Parse number of rows
                        self.num_rows = int(line.split(':', 1)[1].strip())
        
            print(f"Loaded configuration:")
            print(f"Initial state: {self.initial_state}")
            print(f"Rule: {self.rule_number}")
            print(f"Rows: {self.num_rows}")
            
            # Initialize grid
            self.grid = np.zeros((self.num_rows, len(self.initial_state)), dtype=np.int8)
            self.grid[0] = self.initial_state
            
        except FileNotFoundError:
            print(f"Error: The file '{filename}' was not found.")
            return
            
    def apply_rule(self, left, center, right):
        """Apply Rule 90 to three cells"""
        if self.rule_number == 90:
            # Convert to integers and perform XOR
            return int(bool(int(left)) != bool(int(right)))  # XOR using boolean conversion
        return 0
        
    def update(self, frame):
        """Update the cellular automaton state"""
        if self.current_row < self.num_rows - 1:
            current = self.grid[self.current_row]
            next_row = np.zeros_like(current)
            
            # Apply rule to each cell
            size = len(current)
            for i in range(size):
                left = int(current[i-1] if i > 0 else current[-1])  # Wrap around
                center = int(current[i])
                right = int(current[(i+1) % size])  # Wrap around
                next_row[i] = self.apply_rule(left, center, right)
            
            self.current_row += 1
            self.grid[self.current_row] = next_row
            
            # Update visualization
            self.ax.clear()
            self.ax.imshow(self.grid[:self.current_row+1], 
                          cmap='binary', 
                          interpolation='nearest')
            self.ax.set_title(f'Rule {self.rule_number} Cellular Automaton\nStep {self.current_row}')
            self.ax.axis('off')
            
            plt.tight_layout()
            self.fig.canvas.draw()
            self.fig.canvas.flush_events()
            
    def run(self, filename='input.wfl'):
        """Run the cellular automaton"""
        self.load_configuration(filename)
        
        # Flag to track if window is closed
        self.running = True
        
        def on_close(event):
            self.running = False
        
        # Connect the close event
        self.fig.canvas.mpl_connect('close_event', on_close)
        
        print("Starting cellular automaton simulation...")
        print("Close window or press Ctrl+C to stop")
        
        try:
            while self.running and self.current_row < self.num_rows - 1:
                self.update(None)
                plt.pause(0.1)  # 100ms delay
                
                # Check if all windows are closed
                if not plt.get_fignums():
                    self.running = False
                    break
                    
        except KeyboardInterrupt:
            print("\nStopping simulation...")
        except Exception as e:
            print(f"Error occurred: {e}")
        finally:
            plt.close('all')

if __name__ == "__main__":
    automaton = CellularAutomaton()
    automaton.run()