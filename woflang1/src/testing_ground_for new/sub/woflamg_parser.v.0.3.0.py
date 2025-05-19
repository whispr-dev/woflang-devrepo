import re
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import random
import numpy as np
from collections import defaultdict

class WoFNeuralNet:
    def __init__(self):
        # Network structure
        self.layers = defaultdict(dict)
        self.weights = {}
        self.thresholds = {}
        self.variables = {}
        self.input_vars = []
        self.output_vars = []
        
        # Visualization
        plt.ion()  # Turn on interactive mode
        self.fig, (self.ax1, self.ax2) = plt.subplots(2, 1, figsize=(12, 8))
        self.lines = {}
        self.history = defaultdict(list)
        self.step = 0
        
        # WoFLang operations
        self.operations = {
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

    def parse_tokens(self, command):
        pattern = r"[-+]?\d*\.?\d+|\b\w+_\w+\b|\b\w+\b|[齊隶丶丿而或⊕无无‍而无‍或()門]|若|则|另"
        return [token for token in re.findall(pattern, command) if token.strip()]

    def load_network_definition(self, filename):
        """Parse WoFLang file to set up network structure"""
        try:
            with open(filename, 'r', encoding='utf-8') as file:
                commands = [line.strip() for line in file.readlines() if line.strip()]
        except FileNotFoundError:
            print(f"Error: The file '{filename}' was not found.")
            return

        # First pass: identify inputs and structure
        for cmd in commands:
            tokens = self.parse_tokens(cmd)
            if len(tokens) >= 3 and tokens[1] == '門':
                var_name = tokens[0]
                
                # Identify inputs (i_* variables)
                if var_name.startswith('i_'):
                    self.input_vars.append(var_name)
                    self.layers['input'][var_name] = 0
                # Identify weights (w_* variables)
                elif var_name.startswith('w_'):
                    self.weights[var_name] = float(tokens[2])
                # Identify thresholds (Θ_* variables)
                elif var_name.startswith('Θ_') or var_name.startswith('theta_'):
                    self.thresholds[var_name[-1]] = float(tokens[2])
                # Identify outputs (a_* variables)
                elif var_name.startswith('a_'):
                    self.output_vars.append(var_name)
                    layer = var_name[-1]
                    self.layers[layer][var_name] = 0
                # Identify intermediate variables
                elif var_name.startswith('v_'):
                    layer = var_name[-1]
                    self.layers[layer][var_name] = 0

        print("Network Structure Loaded:")
        print(f"Inputs: {self.input_vars}")
        print(f"Outputs: {self.output_vars}")
        print(f"Layers: {dict(self.layers)}")
        print(f"Weights: {self.weights}")
        print(f"Thresholds: {self.thresholds}")

    def generate_inputs(self):
        """Generate random inputs for testing"""
        for input_var in self.input_vars:
            self.layers['input'][input_var] = random.uniform(0, 100)

    def activation_function(self, x, threshold):
        """ReLU-like activation with threshold"""
        return max(0, x - threshold)

    def forward_pass(self):
        """Perform one forward pass through the network"""
        # Update inputs first
        self.generate_inputs()
        
        # Process each layer (except input layer)
        layer_order = ['A', 'B', 'C']  # Explicit layer order
        for layer in layer_order:
            if layer not in self.layers:
                continue
                
            # Process each neuron in the layer
            for var_name in list(self.layers[layer].keys()):
                if var_name.startswith('v_'):
                    # Get input values
                    inputs = []
                    weights = []
                    for i in range(1, 3):  # Assuming 2 inputs per neuron
                        input_name = f"i_{i}_{layer}"
                        weight_name = f"w_{i}_{layer}"
                        if input_name in self.variables and weight_name in self.weights:
                            inputs.append(self.variables[input_name])
                            weights.append(self.weights[weight_name])
                    
                    if inputs and weights:
                        weighted_sum = sum(i * w for i, w in zip(inputs, weights))
                        self.layers[layer][var_name] = weighted_sum
                
                elif var_name.startswith('a_'):
                    v_name = f"v_{layer}"
                    if v_name in self.layers[layer]:
                        threshold = self.thresholds.get(layer, 0)
                        self.layers[layer][var_name] = self.activation_function(
                            self.layers[layer][v_name], threshold)

        # Update history
        for layer, neurons in self.layers.items():
            for var_name, value in neurons.items():
                self.history[var_name].append(value)

    def visualize_network_structure(self):
        """Draw the network structure"""
        self.ax2.clear()
        self.ax2.set_title("Network Structure")
        self.ax2.set_xticks([])
        self.ax2.set_yticks([])
        
        # Define layer positions
        layer_positions = {'input': 0}
        for i, layer in enumerate(['A', 'B', 'C']):
            if layer in self.layers:
                layer_positions[layer] = i + 1

        # Draw neurons
        for layer_name, layer_pos in layer_positions.items():
            if layer_name not in self.layers:
                continue
                
            neurons = self.layers[layer_name]
            n_neurons = len(neurons)
            
            for i, (neuron_name, value) in enumerate(neurons.items()):
                y_pos = i - n_neurons/2
                circle = plt.Circle((layer_pos, y_pos), 0.2, 
                                  color='lightblue', fill=True)
                self.ax2.add_patch(circle)
                self.ax2.text(layer_pos, y_pos, neuron_name, 
                            ha='center', va='center')

        # Set limits
        self.ax2.set_xlim(-1, len(layer_positions))
        self.ax2.set_ylim(-3, 3)

    def update(self, frame):
        """Update animation frame"""
        # Perform forward pass
        self.forward_pass()
        
        # Update activity plot
        self.ax1.clear()
        self.ax1.set_title("Neural Network Activity")
        self.ax1.set_xlabel("Time Step")
        self.ax1.set_ylabel("Value")
        
        # Plot histories
        for var_name, history in self.history.items():
            self.ax1.plot(history, label=var_name)
        
        self.ax1.legend(loc='center left', bbox_to_anchor=(1, 0.5))
        
        # Update network structure visualization
        self.visualize_network_structure()
        
        plt.tight_layout()
        self.fig.canvas.draw()
        self.fig.canvas.flush_events()

    def run(self, filename='input.wfl'):
            """Run the neural network"""
            self.load_network_definition(filename)
        
            # Flag to track if window is closed
            self.running = True
        
    def run(self, filename='input.wfl'):
        """Run the neural network"""
        self.load_network_definition(filename)
        
        # Flag to track if window is closed
        self.running = True
        
        def on_close(event):
            self.running = False
            plt.close('all')
        
        # Connect the close event
        self.fig.canvas.mpl_connect('close_event', on_close)
        
        print("Starting neural network simulation...")
        print("Close window or press Ctrl+C to stop")
        
        while self.running:
            try:
                self.update(None)
                plt.pause(0.1)  # 100ms delay
                
                # Check if all windows are closed
                if not plt.get_fignums():
                    self.running = False
                    break
                    
            except KeyboardInterrupt:
                print("\nStopping network...")
                self.running = False
                plt.close('all')
                break
            except Exception as e:
                print(f"Error occurred: {e}")
                self.running = False
                plt.close('all')
                break
        
        # Cleanup
        plt.close('all')

# At the end of your file, change this:
if __name__ == "__main__":
    network = WoFNeuralNet()
    network.run()        