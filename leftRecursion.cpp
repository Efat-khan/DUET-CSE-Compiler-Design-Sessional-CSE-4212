#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to eliminate left recursion for a given non-terminal and its productions
void eliminateLeftRecursion(const string& nonTerminal, vector<string>& productions) {
    vector<string> alpha, beta; // Vectors to store left-recursive (alpha) and non-recursive (beta) productions
    bool isLeftRecursive = false; // Flag to check if left recursion exists

    // Separate the productions into alpha and beta
    for (const string& production : productions) {
        if (production[0] == nonTerminal[0]) { // Check if the production is left-recursive
            alpha.push_back(production.substr(1)); // Add the remaining part (after the non-terminal) to alpha
            isLeftRecursive = true; // Mark as left-recursive
        } else {
            beta.push_back(production); // Add non-left-recursive production to beta
        }
    }

    // If no left recursion exists, print the original grammar
    if (!isLeftRecursive) {
        cout << "The grammar is not left-recursive." << endl;
        cout << nonTerminal << " -> ";
        for (int i = 0; i < productions.size(); ++i) {
            if (i > 0) cout << " | "; // Add '|' between productions
            cout << productions[i]; // Print each production
        }
        cout << endl;
        return; // Exit as no changes are needed
    }

    // If left recursion exists, eliminate it
    cout << "The grammar is left-recursive." << endl;
    string newNonTerminal = nonTerminal + "'"; // Create a new non-terminal (e.g., S')

    // Print the modified grammar for the original non-terminal
    cout << nonTerminal << " -> ";
    for (int i = 0; i < beta.size(); ++i) {
        cout << beta[i] << newNonTerminal; // Append the new non-terminal to each beta production
        if (i < beta.size() - 1) cout << " | "; // Add '|' between beta productions
    }
    cout << endl;

    // Print the productions for the new non-terminal
    cout << newNonTerminal << " -> ";
    for (int i = 0; i < alpha.size(); ++i) {
        cout << alpha[i] << newNonTerminal << " | "; // Append recursion to each alpha production
    }
    cout << "*"; // Add '*' to denote epsilon (empty production)
    cout << endl;
}

int main() {
    string nonTerminal; // To store the non-terminal
    int numProductions; // Number of productions for the non-terminal

    // Input the non-terminal
    cout << "Enter the non-terminal: ";
    cin >> nonTerminal;

    // Input the number of productions
    cout << "Enter the number of productions for " << nonTerminal << ": ";
    cin >> numProductions;

    // Input each production
    vector<string> productions(numProductions);
    cout << "Enter the productions \n";
    for (int i = 0; i < numProductions; ++i) {
        cout << "Production " << i + 1 << ": ";
        cin >> productions[i];
    }

    // Check for and eliminate left recursion
    cout << "\nChecking for left recursion and eliminating if necessary\n";
    eliminateLeftRecursion(nonTerminal, productions);

    return 0; // End of the program
}

/*
Sample Input:
Enter the non-terminal: S
Enter the number of productions for S: 4
Enter the productions
Production 1: Sa
Production 2: Sb
Production 3: c
Production 4: d

Sample Output:
Checking for left recursion and eliminating if necessary
The grammar is left-recursive.
S -> cS' | dS'
S' -> aS' | bS' | *
*/
