import re
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import random
import numpy as np

class WoFInterpreter:
    def __init__(self):
        self.variables = {}
        self.variables_history = []
        self.fig, self.ax = plt.subplots(figsize=(10, 6))
        self.lines = {}
        self.commands = []
        
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

        self.comparisons = {
            '大': lambda x, y: x > y,
            '小': lambda x, y: x < y,
            '卜': lambda x, y: x == y,
            '丨': lambda x, y: x != y,
            '走': lambda x, y: x >= y,
            '夊': lambda x, y: x <= y,
        }

    def parse_tokens(self, command):
        # Enhanced pattern to handle parentheses and conditional keywords
        pattern = r"[-+]?\d*\.?\d+|\b\w+_\w+\b|\b\w+\b|[齊隶丶丿而或⊕无无‍而无‍或()門]|若|则|另|大|小|卜|丨|走|夊"
        return [token for token in re.findall(pattern, command) if token.strip()]

    def evaluate_expression(self, tokens, start_idx=0):
        if '(' not in tokens:
            return self.get_value(tokens[start_idx], self.variables), start_idx + 1

        stack = []
        i = start_idx
        while i < len(tokens):
            if tokens[i] == '(':
                sub_expr, new_i = self.evaluate_expression(tokens, i + 1)
                stack.append(sub_expr)
                i = new_i
            elif tokens[i] == ')':
                return stack[-1], i + 1
            elif tokens[i] in self.operations and len(stack) >= 1:
                op = self.operations[tokens[i]]
                operand2, new_i = self.evaluate_expression(tokens, i + 1)
                stack[-1] = op(stack[-1], operand2)
                i = new_i
            else:
                stack.append(self.get_value(tokens[i], self.variables))
                i += 1

        return stack[-1] if stack else None, i

    def get_value(self, token, variables):
        try:
            return float(token)
        except ValueError:
            return variables.get(token, None)

    def interpret_command(self, command):
        tokens = self.parse_tokens(command)
        print(f"Processing command: {command}")
        print(f"Tokens: {tokens}")

        # Handle conditional statements
        if tokens[0] == '若':
            condition_var = self.get_value(tokens[1], self.variables)
            comparison = tokens[2]
            compare_value = float(tokens[3])
            
            if condition_var is not None and comparison in self.comparisons:
                if self.comparisons[comparison](condition_var, compare_value):
                    # Execute 'then' part
                    then_cmd = ' '.join(tokens[tokens.index('则')+1:tokens.index('另')])
                    self.interpret_command(then_cmd)
                else:
                    # Execute 'else' part
                    else_cmd = ' '.join(tokens[tokens.index('另')+1:])
                    self.interpret_command(else_cmd)
            return

        # Handle normal assignments
        if len(tokens) >= 3 and tokens[1] == '門':
            var_name = tokens[0]
            if '(' in tokens:
                # Handle parenthetical expressions
                value, _ = self.evaluate_expression(tokens[2:])
                self.variables[var_name] = value
            else:
                # Handle simple assignments and operations
                if len(tokens) == 3:
                    self.variables[var_name] = self.get_value(tokens[2], self.variables)
                elif len(tokens) >= 4 and tokens[3] in self.operations:
                    op = self.operations[tokens[3]]
                    operand1 = self.get_value(tokens[2], self.variables)
                    operand2 = self.get_value(tokens[4], self.variables)
                    if operand1 is not None and operand2 is not None:
                        self.variables[var_name] = op(operand1, operand2)

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
            
            for var_name, value in self.variables.items():
                if var_name not in self.lines:
                    color = f'#{random.randint(0, 0xFFFFFF):06x}'
                    self.lines[var_name], = self.ax.plot([], [], label=var_name, color=color)
                
                line = self.lines[var_name]
                x_data = list(range(len(self.variables_history)))
                y_data = [hist.get(var_name, None) for hist in self.variables_history]
                y_data = [y for y in y_data if y is not None]
                line.set_data(range(len(y_data)), y_data)

            # Update x-axis to show actual step numbers
            if self.variables_history:
                self.ax.set_xlim(-1, len(self.variables_history) + 1)
                # Set x-ticks to show whole numbers
                self.ax.set_xticks(np.arange(0, len(self.variables_history), 1))
            
            self.ax.relim()
            self.ax.autoscale_view(scalex=False)  # Don't autoscale x-axis
            self.ax.legend(loc='upper left', bbox_to_anchor=(1, 1))

        return list(self.lines.values())

    def run(self, filename='input.wfl'):
        try:
            with open(filename, 'r', encoding='utf-8') as file:
                self.commands = [line.strip() for line in file.readlines() if line.strip()]
        except FileNotFoundError:
            print(f"Error: The file '{filename}' was not found.")
            return

        # Initialize x-axis limits based on number of commands
        self.ax.set_xlim(-1, len(self.commands) + 1)
        
        anim = FuncAnimation(
            self.fig, 
            self.update,
            init_func=self.init_animation,
            frames=len(self.commands),
            interval=500,  # 500ms between updates
            repeat=False,
            blit=True
        )

        plt.subplots_adjust(right=0.85)
        plt.grid(True)  # Added grid for better readability
        plt.show()

if __name__ == "__main__":
    interpreter = WoFInterpreter()
    interpreter.run()