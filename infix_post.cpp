#include <iostream>
#include <stack>
#include <cctype>
using namespace std;

// Function to determine the precedence of operators
int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1; // Lowest precedence
    if (op == '*' || op == '/')
        return 2; // Higher precedence
    return 0;     // No precedence for non-operators
}

// Function to convert an infix expression to a postfix expression
string infixToPostfix(const string &exp)
{
    stack<char> s;       // Stack to store operators and parentheses
    string postfix = ""; // Resultant postfix expression

    // Iterate through each character in the infix expression
    for (char ch : exp)
    {
        if (isalnum(ch))
        {
            // If the character is an operand (number or variable), append it to the postfix string
            postfix += ch;
        }
        else if (ch == '(')
        {
            // If the character is '(', push it onto the stack
            s.push(ch);
        }
        else if (ch == ')')
        {
            // If the character is ')', pop and append all operators until '(' is found
            while (!s.empty() && s.top() != '(')
            {
                postfix += s.top();
                s.pop();
            }
            s.pop(); // Pop the '(' from the stack
        }
        else
        {
            // If the character is an operator (+, -, *, /)
            // Pop and append operators from the stack with greater or equal precedence
            while (!s.empty() && precedence(s.top()) >= precedence(ch))
            {
                postfix += s.top();
                s.pop();
            }
            // Push the current operator onto the stack
            s.push(ch);
        }
    }

    // Pop and append any remaining operators in the stack to the postfix expression
    while (!s.empty())
    {
        postfix += s.top();
        s.pop();
    }
    return postfix; // Return the resultant postfix expression
}

int main()
{
    string infix; // Variable to store the infix expression
    cout << "Enter infix expression: ";
    cin >> infix; // Input the infix expression from the user

    // Convert the infix expression to postfix and display the result
    string postfix = infixToPostfix(infix);
    cout << "Postfix expression: " << postfix << endl;

    return 0; // End of program
}
