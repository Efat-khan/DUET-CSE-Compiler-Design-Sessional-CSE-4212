#include <bits/stdc++.h>

using namespace std;

// Function to compute FIRST set
void computeFirst(string symbol, map<string, vector<string>> &grammar, map<string, set<string>> &first, set<string> &visited) {
    if (visited.count(symbol)) return; // Avoid reprocessing
    visited.insert(symbol);

    for (const auto &rule : grammar[symbol]) {
        if (isupper(rule[0])) { // Rule starts with a non-terminal
            computeFirst(string(1, rule[0]), grammar, first, visited);
            first[symbol].insert(first[string(1, rule[0])].begin(), first[string(1, rule[0])].end());
        } else {
            first[symbol].insert(string(1, rule[0])); // Terminal or epsilon
        }
    }
}

// Function to compute FOLLOW set
void computeFollow(string symbol, map<string, vector<string>> &grammar, map<string, set<string>> &first, map<string, set<string>> &follow, set<string> &visited, string start) {
    if (visited.count(symbol)) return;
    visited.insert(symbol);

    if (symbol == start) {
        follow[symbol].insert("$"); // Add end-of-input marker for the start symbol
    }

    for (const auto &prod : grammar) {
        for (const auto &rule : prod.second) {
            for (size_t i = 0; i < rule.size(); ++i) {
                if (string(1, rule[i]) == symbol) {
                    if (i + 1 < rule.size()) { // There are symbols after the current one
                        if (isupper(rule[i + 1])) {
                            follow[symbol].insert(first[string(1, rule[i + 1])].begin(), first[string(1, rule[i + 1])].end());
                            follow[symbol].erase("#"); // Remove epsilon
                        } else {
                            follow[symbol].insert(string(1, rule[i + 1]));
                        }
                    }
                    if (i + 1 == rule.size() || first[string(1, rule[i + 1])].count("#")) {
                        computeFollow(prod.first, grammar, first, follow, visited, start);
                        follow[symbol].insert(follow[prod.first].begin(), follow[prod.first].end());
                    }
                }
            }
        }
    }
}

int main() {
    map<string, vector<string>> grammar;
    grammar["S"] = {"aSa", "bSb", "A"};
    grammar["A"] = {"aBb"};
    grammar["B"] = {"aB", "bBb", "#"};

    map<string, set<string>> first, follow;
    set<string> visited;

    // Compute FIRST sets
    for (const auto &prod : grammar) {
        computeFirst(prod.first, grammar, first, visited);
    }

    visited.clear();

    // Compute FOLLOW sets
    string startSymbol = "S";
    for (const auto &prod : grammar) {
        computeFollow(prod.first, grammar, first, follow, visited, startSymbol);
    }

      cout << "FIRST Sets:\n";
    for (const auto &f : first) {
        // Only print FIRST sets for non-terminals
        if (isupper(f.first[0])) {
            cout << "FIRST(" << f.first << ") = { ";
            for (const auto &sym : f.second) {
                cout << sym << " ";
            }
            cout << "}\n";
        }
    }

    // Display FOLLOW sets
    cout << "\nFOLLOW Sets:\n";
    for (const auto &f : follow) {
        cout << "FOLLOW(" << f.first << ") = { ";
        for (const auto &sym : f.second) {
            cout << sym << " ";
        }
        cout << "}\n";
    }}
