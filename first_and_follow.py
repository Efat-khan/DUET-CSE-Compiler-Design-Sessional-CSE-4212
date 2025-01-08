from collections import defaultdict

# Global variables for FIRST and FOLLOW sets
first = defaultdict(set)
follow = defaultdict(set)
productions = defaultdict(list)

# Function to add a symbol to a set
def add_to_set(target_set, symbol):
    target_set.add(symbol)

# Compute FIRST set for a non-terminal
def compute_first(non_terminal):
    for production in productions[non_terminal]:
        for symbol in production:
            if not symbol.isupper():  # Terminal or epsilon
                add_to_set(first[non_terminal], symbol)
                break
            else:  # Non-terminal
                compute_first(symbol)
                has_epsilon = False
                for sub_first in first[symbol]:
                    if sub_first != 'ε':
                        add_to_set(first[non_terminal], sub_first)
                    else:
                        has_epsilon = True
                if not has_epsilon:
                    break

# Compute FOLLOW set for all non-terminals
def compute_follow(start_symbol):
    follow[start_symbol].add('$')  # Start symbol includes end marker

    updated = True
    while updated:
        updated = False

        for lhs, production_list in productions.items():
            for production in production_list:
                trailer = follow[lhs].copy()

                for symbol in reversed(production):
                    if symbol.isupper():  # Non-terminal
                        before_size = len(follow[symbol])

                        follow[symbol].update(trailer)

                        if 'ε' in first[symbol]:
                            trailer.update(first[symbol] - {'ε'})
                        else:
                            trailer = first[symbol]

                        if len(follow[symbol]) != before_size:
                            updated = True
                    else:
                        trailer = {symbol}

# Example grammar
productions['S'] = ["aSa", "bSb", "A"]
productions['A'] = ["aBb"]
productions['B'] = ["aB", "bB", "ε"]

start_symbol = 'S'

# Compute FIRST sets
for non_terminal in productions.keys():
    compute_first(non_terminal)

# Compute FOLLOW sets
compute_follow(start_symbol)

# Print FIRST sets
print("+-------------------------+")
print("|        FIRST Sets       |")
print("+-------------------------+")
for non_terminal, first_set in first.items():
    print(f"| FIRST({non_terminal}) = {{ {', '.join(first_set)} }}")
print("+-------------------------+")

# Print FOLLOW sets
print("\n+-------------------------+")
print("|       FOLLOW Sets       |")
print("+-------------------------+")
for non_terminal, follow_set in follow.items():
    print(f"| FOLLOW({non_terminal}) = {{ {', '.join(follow_set)} }}")
print("+-------------------------+")
