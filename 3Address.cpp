#include <iostream>
#include <stack>
#include <vector>
#include <cctype>
#include <string>
using namespace std;

// Function to determine operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Function to check if a character is an operator
bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

// Function to convert infix expression to postfix
string infixToPostfix(const string &infix) {
    stack<char> operators;
    string postfix = "";
    for (size_t i = 0; i < infix.length(); ++i) {
        char ch = infix[i];

        if (isalnum(ch)) {
            // Append multi-character operands directly
            while (i < infix.length() && (isalnum(infix[i]) || infix[i] == '_')) {
                postfix += infix[i];
                i++;
            }
            postfix += " "; // Add a space to separate operands
            i--;
        } else if (ch == '(') {
            operators.push(ch);
        } else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                postfix += " ";
                operators.pop();
            }
            operators.pop(); // Remove '('
        } else if (isOperator(ch)) {
            // Handle unary negation
            if (ch == '-' && (i == 0 || infix[i - 1] == '(')) {
                postfix += "0 "; // Treat as "0 - operand"
            }
            while (!operators.empty() && precedence(operators.top()) >= precedence(ch)) {
                postfix += operators.top();
                postfix += " ";
                operators.pop();
            }
            operators.push(ch);
        }
    }
    while (!operators.empty()) {
        postfix += operators.top();
        postfix += " ";
        operators.pop();
    }
    return postfix;
}

// Function to generate three-address code from postfix
void generateThreeAddressCode(const string &postfix) {
    stack<string> operands;
    vector<string> code;
    int tempVarCount = 1;

    for (size_t i = 0; i < postfix.length(); ++i) {
        char ch = postfix[i];

        if (isalnum(ch)) {
            string operand = "";
            while (i < postfix.length() && (isalnum(postfix[i]) || postfix[i] == '_')) {
                operand += postfix[i];
                i++;
            }
            operands.push(operand);
            i--;
        } else if (isOperator(ch)) {
            string op2 = operands.top(); operands.pop();
            string op1 = operands.top(); operands.pop();
            string tempVar = "t" + to_string(tempVarCount++);
            code.push_back(tempVar + " = " + op1 + " " + ch + " " + op2);
            operands.push(tempVar);
        } else if (ch == ' ') {
            continue; // Skip spaces
        }
    }

    string resultVar = operands.top();
    for (const string &line : code) {
        cout << line << endl;
    }
    cout << "a = " << resultVar << endl; // Assign final result to 'a'
}

int main() {
    string infix;
    cout << "Enter infix expression: ";
    getline(cin, infix);

    string postfix = infixToPostfix(infix);
    cout << "Postfix expression: " << postfix << endl;

    cout << "Three-address code:" << endl;
    generateThreeAddressCode(postfix);

    return 0;
}

//a=(-c*b)+(-c*d)
