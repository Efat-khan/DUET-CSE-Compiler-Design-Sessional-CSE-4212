#include <bits/stdc++.h>
using namespace std;

// Variables used for parsing
int n;               // Length of the input string
string s;            // Input string
vector<char> st;     // Stack for parsing
vector<char> a;      // Input tape

// Function to display the current state of the stack and input
void StackAndInput() {
    cout << endl << "$"; // Stack starts with "$"
    for (auto x : st) {
        cout << x; // Print stack content
    }
    cout << "\t\t"; // Separator
    for (auto x : a) {
        cout << x; // Print input content
    }
}

// Function to check for reductions in the stack
bool check() {
    bool reduced = false;

    // Iterate over the stack to check for reducible patterns
    for (int i = 0; i < st.size(); i++) {
        // Reduce "id" to "E" (single characters a, b, c, m, n, p are considered "id")
        if (st[i] == 'a' || st[i] == 'b' || st[i] == 'c' || st[i] == 'm' || st[i] == 'n' || st[i] == 'p') {
            st[i] = 'E'; // Replace "id" with "E"
            StackAndInput();
            cout << "$\t\t" << "REDUCE E->id";
            reduced = true;
            return check(); // Recheck for further reductions
        }

        // Reduce "E+E" or "E*E" to "E"
        if (i + 2 < st.size() && st[i] == 'E' && (st[i + 1] == '+' || st[i + 1] == '*') && st[i + 2] == 'E') {
            char op = st[i + 1]; // Store the operator (+ or *)
            st.erase(st.begin() + i + 1, st.begin() + i + 3); // Remove "op" and the second "E"
            StackAndInput();
            if (op == '+') {
                cout << "$\t\t" << "REDUCE E->E+E";
            } else {
                cout << "$\t\t" << "REDUCE E->E*E";
            }
            reduced = true;
            return check(); // Recheck for further reductions
        }
    }
    return reduced; // Return whether a reduction occurred
}

// Main function
int main() {
    // Print grammar rules
    cout << "GRAMMAR: " << endl << "E->E+E" << endl << "E->E*E" << endl << "E->id" << endl;

    // Get input string
    cout << endl << "Input String: ";
    cin >> s;
    n = s.length();

    // Initialize input tape from the string
    for (int i = 0; i < n; i++) {
        a.push_back(s[i]);
    }

    // Print parsing table header
    cout << endl << "Stack\t\t Input\t\tAction";

    bool valid = true; // Flag to check if the string is valid

    // Parsing loop
    for (int i = 0; i < n; i++) {
        st.push_back(a[i]); // Push the next character onto the stack
        a[i] = ' ';         // Mark the character as consumed in the input tape
        StackAndInput();    // Display the current state
        cout << "$\t\t" << "SHIFT->" << st.back();

        // Attempt reductions after each shift
        if (!check()) {
            bool hasError = true;

            // Check if the stack contains only valid symbols
            for (char c : st) {
                if (c == 'a' || c == 'b' || c == 'c' || c == 'm' || c == 'n' || c == 'p' || c == 'E' || c == '+' || c == '*') {
                    hasError = false;
                }
            }

            // If the stack contains invalid symbols, set an error
            if (hasError) {
                valid = false;
                cout << "$\t\tERROR: Invalid string";
                break;
            }
        }
    }

    // Final validation after parsing
    if (valid && st.size() == 1 && st[0] == 'E') {
        cout << endl << endl << "String accepted" << endl; // String is valid
    } else if (valid) {
        cout << endl << endl << "String rejected: Remaining stack does not reduce to E" << endl;
    }
    return 0;
}
