import random

# Define possible variables and operations
variables = ['i_1', 'i_2', 'theta_A', 'i_1_B', 'i_2_B', 'w_1_B', 'theta_B', 'w_2_C', 'theta_C']
operations = ['齊', '隶', '丶', '丿', '而', '或', '⊕', '无', '无‍而', '无‍或']
conditions = ['大', '小', '卜', '丨', '走', '夊']

# Number of commands to generate
num_commands = 20  # Increased number to cover a wider range of scenarios

# Function to generate random value or variable
def random_value_or_var(ensure_init=False):
    if ensure_init or random.choice([True, False]):
        return str(random.uniform(0, 100))  # Random float between 0 and 100 to reflect 0-100 degrees of truth
    else:
        return random.choice(variables)

# Generate random commands
random_commands = []

# Step 1: Initialize all variables at least once with a value between 0 and 100
for var in variables:
    command = f"{var} 門 {random_value_or_var(ensure_init=True)}"
    random_commands.append(command)

# Step 2: Generate additional commands with various operations
for _ in range(num_commands):
    var = random.choice(variables)
    op = random.choice(operations)
    
    # Unary operation
    if op in ['无']:
        val1 = random_value_or_var(ensure_init=True)  # Ensure initialization of variables
        command = f"{var} 門 {op} {val1}"
    
    # Binary or special operators
    else:
        val1 = random_value_or_var(ensure_init=False)
        val2 = random_value_or_var(ensure_init=False)
        if op in ['無‍而', '無‍或']:  # Special operators with space in name
            command = f"{var} 門 {val1} {op} {val2}"
        else:  # Regular binary operators
            command = f"{var} 門 {val1} {op} {val2}"
    
    random_commands.append(command)

# Step 3: Add conditional command
condition_var = random.choice(variables)
condition_op = random.choice(conditions)
condition_val = random_value_or_var(ensure_init=True)
then_var = random.choice(variables)
then_val = random_value_or_var(ensure_init=True)
else_var = random.choice(variables)
else_val = random_value_or_var(ensure_init=True)

condition_command = f"若 {condition_var} {condition_op} {condition_val} 则 {then_var} {then_val} 另 {else_var} {else_val}"
random_commands.append(condition_command)

# Print generated commands
print("Generated random commands:")
for cmd in random_commands:
    print(cmd)

# Write random commands to 'input.wfl' file
with open('input.wfl', 'w', encoding='utf-8') as file:
    for cmd in random_commands:
        file.write(cmd + '\n')
