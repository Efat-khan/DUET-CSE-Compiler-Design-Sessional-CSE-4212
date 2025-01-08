#include <iostream>
#include <stack>
#include <string>
#include <map>
using namespace std;

// Parsing Table
// This table defines the grammar rules for each (non-terminal, terminal) pair.
map<pair<char, char>, string> parsingTable = {
    {{'S', 'a'}, "aB"},   // Rule: S -> aB
    {{'B', 'b'}, "b"},    // Rule: B -> b
    {{'B', '$'}, ""}      // Rule: B -> ε (epsilon, represented as an empty string)
};

// Function to check if a symbol is a terminal
bool isTerminal(char symbol) {
    // Terminals are symbols that are not uppercase letters (non-terminals).
    return !(symbol >= 'A' && symbol <= 'Z');
}

// Predictive Parser
bool predictiveParser(string input) {
    stack<char> st;        // Stack for parsing
    st.push('$');          // Push the end marker ('$') onto the stack
    st.push('S');          // Push the start symbol ('S') onto the stack

    input += '$';          // Append the end marker ('$') to the input string
    int i = 0;             // Input pointer

    // Parsing loop
    while (!st.empty()) {
        char top = st.top();     // Get the top symbol of the stack
        char current = input[i]; // Get the current input character

        // If top of stack matches the current input character
        if (top == current) {
            st.pop();  // Pop the matched symbol from the stack
            i++;       // Move to the next input character
        }
        // If top of stack is a terminal but doesn't match the input
        else if (isTerminal(top)) {
            return false;  // Error: Terminal mismatch
        }
        // If top of stack is a non-terminal
        else {
            st.pop();  // Pop the non-terminal from the stack
            string production = parsingTable[{top, current}]; // Get the production rule
            if (production.empty()) {
                return false;  // Error: No matching rule in the parsing table
            }
            // Push the production (reversed) onto the stack
            for (int j = production.size() - 1; j >= 0; j--) {
                if (production[j] != 'ε') { // Skip epsilon (empty string)
                    st.push(production[j]);
                }
            }
        }
    }

    // Parsing is successful if the input string is fully parsed and the stack is empty
    return (i == input.size());
}

// Main function
int main() {
    string input;
    cout << "Enter input string: ";
    cin >> input;

    // Call the predictive parser with the input string
    if (predictiveParser(input)) {
        cout << "String is accepted.\n"; // Output if the string is valid according to the grammar
    } else {
        cout << "String is rejected.\n"; // Output if the string is invalid
    }

    return 0;
}
