import re

# Token definitions (regex patterns)
# Each tuple in the list represents a token type and its corresponding regex pattern.
token_patterns = [
    ('KEYWORD', r'\b(int|float|if|else|while|return)\b'),  # Matches keywords like int, float, etc.
    ('IDENTIFIER', r'[a-zA-Z_][a-zA-Z0-9_]*'),            # Matches variable/function names (identifiers)
    ('NUMBER', r'\b\d+\b'),                               # Matches numeric literals (e.g., 123)
    ('OPERATOR', r'[+\-*/=]'),                            # Matches operators like +, -, *, /, =
    ('SEPARATOR', r'[;,\(\)\{\}]'),                       # Matches separators like ;, (, ), {, }
    ('WHITESPACE', r'\s+'),                               # Matches whitespace (spaces, tabs, newlines)
    ('UNKNOWN', r'.')                                     # Matches any unknown character (catch-all)
]

# Function to perform lexical analysis on the given input code
def lexical_analyzer(input_code):
    tokens = []  # List to store the generated tokens
    while input_code:  # Continue until the entire input code is processed
        for token_type, pattern in token_patterns:
            regex = re.compile(pattern)  # Compile the regex pattern
            match = regex.match(input_code)  # Match the pattern at the start of the input code
            if match:  # If a match is found
                lexeme = match.group(0)  # Extract the matched lexeme
                if token_type != 'WHITESPACE':  # Ignore tokens of type WHITESPACE
                    tokens.append((token_type, lexeme))  # Append the token type and lexeme to the list
                input_code = input_code[len(lexeme):]  # Remove the matched lexeme from the input code
                break  # Exit the loop and start matching the next part of the code
    return tokens  # Return the list of tokens

# Example usage of the lexical analyzer
code = "int age = 25;"  # Sample input code
tokens = lexical_analyzer(code)  # Call the lexical analyzer to tokenize the input code

# Print the generated tokens
for token in tokens:
    print(token)  # Each token is a tuple (token_type, lexeme)
