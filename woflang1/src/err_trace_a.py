print("Script started")

def interpret_command(command, variables):
    tokens = parse_tokens(command)
    print(f"Processing command: {command}")
    print(f"Tokens: {tokens}")
    print(f"Processing command: {command}")

    operations = {
        '齊': lambda x, y: x + y,
        '隶': lambda x, y: x - y,
        '丶': lambda x, y: x * y,
        '丿': lambda x, y: x / y if y != 0 else float('inf'),
        '而': lambda x, y: min(x, y),  # Analog AND
        '或': lambda x, y: max(x, y),  # Analog OR
        '⊕': lambda x, y: abs(x - y),  # Analog XOR (Rule 90)
        '无': lambda x: -x,            # Analog NOT
        '无‍而': lambda x, y: -(min(x, y)), # Analog NAND
        '无‍或': lambda x, y: -(max(x, y)), # Analog NOR
    }

    if len(tokens) == 0:
        return variables
    print(f"Commands loaded: {commands}")

    try:
        if tokens[1] == '門':
            var_name = tokens[0]
            if len(tokens) == 3:
                # Simple assignment
                value = tokens[2]
                variables[var_name] = get_value(value, variables)
            elif len(tokens) == 5 and tokens[3] in operations:
                # Operation assignment
                op = tokens[3]
                operand1 = get_value(tokens[2], variables)
                operand2 = get_value(tokens[4], variables)
                # Check if operands are not None before performing operation
                if operand1 is not None and operand2 is not None:
                    variables[var_name] = operations[op](operand1, operand2)
                else:
                    print(f"Error: Invalid operands for operation '{op}' in command '{command}'")
                    variables[var_name] = None
            elif '(' in tokens:
                # Complex expression
                expression = command.split('門', 1)[1].strip()
                variables[var_name] = evaluate_expression(expression, variables, operations)
        elif tokens[0] == '若':
            condition_var = get_value(tokens[1], variables)
            condition_operator = tokens[2]
            condition_value = get_value(tokens[3], variables)
            then_index = tokens.index('则')
            else_index = tokens.index('另')

            if evaluate_condition(condition_var, condition_operator, condition_value):
                true_assignment = tokens[then_index + 1:else_index]
                var_name = true_assignment[0]
                variables[var_name] = get_value(true_assignment[2], variables)
            else:
                false_assignment = tokens[else_index + 1:]
                var_name = false_assignment[0]
                variables[var_name] = get_value(false_assignment[2], variables)
    except Exception as e:
        print(f"Error processing command '{command}': {e}")

    print(f"Variables: {variables}")
    return variables

# Further processing and plotting (if applicable)
print("Script completed")
