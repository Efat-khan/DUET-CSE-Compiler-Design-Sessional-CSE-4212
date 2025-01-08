#include <bits/stdc++.h>

using namespace std;

// Tokenize the input string
vector<string> tokenize(const string& input_string) {
    vector<string> tokens;
    size_t i = 0;

    // Loop through the input string
    while (i < input_string.size()) {
        if (isalpha(input_string[i])) { // Match identifiers (e.g., "id")
            tokens.push_back("id");
            while (i < input_string.size() && isalpha(input_string[i])) {
                i++; // Consume all letters in the identifier
            }
        } else if (string("()+*$").find(input_string[i]) != string::npos) { // Match operators and parentheses
            tokens.push_back(string(1, input_string[i])); // Add as a token
            i++;
        } else if (isspace(input_string[i])) { // Skip whitespace
            i++;
        } else {
            i++; // Skip invalid characters
        }
    }
    return tokens; // Return the list of tokens
}

// Custom hash function for pair<string, string>
// This is used to handle pair keys in the unordered_map for the parsing table
struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& pair) const {
        auto hash1 = hash<T1>{}(pair.first);
        auto hash2 = hash<T2>{}(pair.second);
        return hash1 ^ hash2; // Combine the two hash values
    }
};

// Parse the input string using LL(1) parsing
bool parse_string(const string& input_string) {
    // Define grammar rules
    unordered_map<string, vector<string>> grammar = {
        {"E", {"T E'"}},          // E -> T E'
        {"E'", {"+ T E'", "@"}},  // E' -> + T E' | ε (epsilon)
        {"T", {"F T'"}},          // T -> F T'
        {"T'", {"* F T'", "@"}},  // T' -> * F T' | ε
        {"F", {"id", "( E )"}}    // F -> id | ( E )
    };

    // Define the parsing table
    unordered_map<pair<string, string>, string, pair_hash> parsing_table = {
        {{"E", "id"}, "T E'"},
        {{"E", "("}, "T E'"},
        {{"E'", "+"}, "+ T E'"},
        {{"E'", ")"}, "@"},
        {{"E'", "$"}, "@"},
        {{"T", "id"}, "F T'"},
        {{"T", "("}, "F T'"},
        {{"T'", "+"}, "@"},
        {{"T'", "*"}, "* F T'"},
        {{"T'", ")"}, "@"},
        {{"T'", "$"}, "@"},
        {{"F", "id"}, "id"},
        {{"F", "("}, "( E )"}
    };

    // Tokenize the input string
    vector<string> tokens = tokenize(input_string);
    tokens.push_back("$"); // Append the end marker

    // Initialize the stack for parsing
    stack<string> parse_stack;
    parse_stack.push("$"); // Push the end marker
    parse_stack.push("E"); // Push the start symbol

    size_t pointer = 0; // Input pointer

    // Print the parsing steps (header)
    cout << left << setw(30) << "Stack"
         << setw(30) << "Input"
         << "Action" << endl;

    // Parsing loop
    while (!parse_stack.empty()) {
        string top = parse_stack.top();          // Top of the stack
        string current_input = tokens[pointer]; // Current input token

        // Prepare stack and input contents for debugging output
        string stack_content, input_content;
        stack<string> temp_stack = parse_stack;
        while (!temp_stack.empty()) {
            stack_content = temp_stack.top() + " " + stack_content;
            temp_stack.pop();
        }
        for (size_t i = pointer; i < tokens.size(); ++i) {
            input_content += tokens[i] + " ";
        }

        // Print the current state
        cout << setw(30) << stack_content << setw(20) << input_content;

        // If the top of the stack matches the current input token
        if (top == current_input) {
            cout << "Match '" << top << "'" << endl;
            parse_stack.pop(); // Remove the matched token from the stack
            pointer++;         // Move to the next input token
        }
        // If the top of the stack is a non-terminal
        else if (parsing_table.count({top, current_input})) {
            string rule = parsing_table[{top, current_input}];
            cout << "Apply " << top << " -> " << rule << endl;
            parse_stack.pop(); // Remove the non-terminal
            if (rule != "@") { // If the production is not epsilon
                stringstream ss(rule);
                vector<string> symbols;
                string symbol;
                while (ss >> symbol) {
                    symbols.push_back(symbol); // Split the rule into symbols
                }
                for (auto it = symbols.rbegin(); it != symbols.rend(); ++it) {
                    parse_stack.push(*it); // Push symbols in reverse order
                }
            }
        }
        // If no rule is found in the parsing table
        else {
            cout << "Error: No rule for (" << top << ", " << current_input << ")" << endl;
            return false; // Parsing fails
        }
    }

    // Check if parsing was successful
    if (pointer == tokens.size()) {
        cout << "Parsing Successful!" << endl;
        return true;
    } else {
        cout << "Parsing Failed!" << endl;
        return false;
    }
}

// Main function
int main() {
    string input_string = "id + id * id"; // Example input
    parse_string(input_string);          // Parse the input string
    return 0;
}
