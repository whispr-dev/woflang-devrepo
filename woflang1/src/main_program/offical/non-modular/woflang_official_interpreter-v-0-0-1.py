# woflang official interpreter v0.0.1 unfancy

import re

def tokenize(script):
    token_specification = [
        ('NUMBER', r'\b\d+(\.\d*)?\b'),    # Integer or decimal number
        ('IDENT', r'\b\w+_\w+\b'),         # Identifiers (e.g., i_1, θ_A)
        ('OP', r'[齊隶丶丿而或⊕无无‍而无‍或]'), # Operators (from the dictionary)
        ('KW', r'[若则另老至舛自又入止出氏谷己辵比終響釆卩押支⽰眠⺒⺨⽪⽓待⻤⺙⺆⺘工⺣巡非道⺢字読艮⻔]'), # Keywords
        ('SKIP', r'[ \t]+'),               # Skip over spaces and tabs
        ('MISMATCH', r'.'),                # Any other character
    ]
    token_regex = '|'.join(f'(?P<{pair[0]}>{pair[1]})' for pair in token_specification)
    for match in re.finditer(token_regex, script):
        kind = match.lastgroup
        value = match.group()
        if kind == 'NUMBER':
            yield ('NUMBER', float(value))
        elif kind == 'IDENT':
            yield ('IDENT', value)
        elif kind == 'OP':
            yield ('OP', value)
        elif kind == 'KW':
            yield ('KW', value)
        elif kind == 'SKIP':
            continue
        elif kind == 'MISMATCH':
            raise SyntaxError(f'Unexpected character {value}')

def interpret(tokens):
    variables = {}

    def eval_expression(tokens):
        # Simple parser for expressions
        if not tokens:
            return None
        token = tokens.pop(0)
        if token[0] == 'NUMBER':
            return token[1]
        elif token[0] == 'IDENT':
            return variables.get(token[1], 0)
        elif token[0] == 'OP':
            left = eval_expression(tokens)
            right = eval_expression(tokens)
            if token[1] == '齊':  # Addition
                return left + right
            elif token[1] == '隶':  # Subtraction
                return left - right
            # Handle other operations similarly...

    while tokens:
        token = tokens.pop(0)
        if token[0] == 'IDENT' and token[1] in variables:
            if tokens[0][1] == '門':  # Assignment operator
                tokens.pop(0)  # Remove '門'
                value = eval_expression(tokens)
                variables[token[1]] = value
        # Handle other statements like '若...则...另' (if...then...else)

    return variables

def main():
    input_file = 'woflang_neural-net_input_w_Θ.wfl'
    with open(input_file, 'r', encoding='utf-8') as file:
        script = file.read()

    tokens = list(tokenize(script))
    variables = interpret(tokens)
    print(variables)

if __name__ == '__main__':
    main()
