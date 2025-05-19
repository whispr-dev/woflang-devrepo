import re
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import random

class WoFInterpreter:
    def __init__(self):
        self.variables = {}
        self.variables_history = []
        self.fig, self.ax = plt.subplots(figsize=(10, 6))
        self.lines = {}
        self.commands = []
        
        # Keep your original operations
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
        pattern = r"[-+]?\d*\.\d+|\b\d+\b|\b\w+_\w+\b|\b\w+\b|[齊隶丶丿而或⊕无无‍而无‍或()門]"
        return [token for token in re.findall(pattern, command) if token.strip()]

    def get_value(self, token, variables):
        try:
            return float(token)
        except ValueError:
            return variables.get(token, None)

    def interpret_command(self, command):
        tokens = self.parse_tokens(command)
        print(f"Processing command: {command}")
        print(f"Tokens: {tokens}")

        if len(tokens) < 3:
            print(f"Skipping invalid command: {tokens}")
            return

        if tokens[1] == '門':
            var_name = tokens[0]
            if len(tokens) == 3:
                value = self.get_value(tokens[2], self.variables)
                self.variables[var_name] = value
            elif len(tokens) >= 4 and tokens[3] in self.operations:
                op = tokens[3]
                operand1 = self.get_value(tokens[2], self.variables)
                operand2 = self.get_value(tokens[4], self.variables)
                if operand1 is not None and operand2 is not None:
                    self.variables[var_name] = self.operations[op](operand1, operand2)
                else:
                    print(f"Skipping operation due to None values: {tokens}")
                    self.variables[var_name] = None
            else:
                print(f"Invalid operation or operand: {tokens}")
        else:
            print(f"Unsupported command structure: {tokens}")

        self.variables_history.append(self.variables.copy())

    def init_animation(self):
        self.ax.clear()
        self.lines = {}
        self.ax.set_title("Neural Network Variables (Real-time)")
        self.ax.set_xlabel("Step")
        self.ax.set_ylabel("Value")
        return []

    def update(self, frame):
        if frame < len(self.commands):
            self.interpret_command(self.commands[frame])
            
            # Update or create lines for each variable
            for var_name, value in self.variables.items():
                if var_name not in self.lines:
                    # Create new line with random color
                    color = f'#{random.randint(0, 0xFFFFFF):06x}'
                    self.lines[var_name], = self.ax.plot([], [], label=var_name, color=color)
                
                # Update line data
                line = self.lines[var_name]
                x_data = list(range(len(self.variables_history)))
                y_data = [hist.get(var_name, None) for hist in self.variables_history]
                y_data = [y for y in y_data if y is not None]  # Remove None values
                line.set_data(range(len(y_data)), y_data)

            # Adjust plot limits
            self.ax.relim()
            self.ax.autoscale_view()
            self.ax.legend(loc='upper left', bbox_to_anchor=(1, 1))

        return list(self.lines.values())

    def run(self, filename='input.wfl'):
        # Load commands
        try:
            with open(filename, 'r', encoding='utf-8') as file:
                self.commands = [line.strip() for line in file.readlines() if line.strip()]
        except FileNotFoundError:
            print(f"Error: The file '{filename}' was not found.")
            return

        # Set up the animation
        anim = FuncAnimation(
            self.fig, 
            self.update,
            init_func=self.init_animation,
            frames=len(self.commands),
            interval=500,  # 500ms between updates
            repeat=False,
            blit=True
        )

        # Adjust layout to prevent legend overlap
        plt.subplots_adjust(right=0.85)
        plt.show()

if __name__ == "__main__":
    interpreter = WoFInterpreter()
    interpreter.run()