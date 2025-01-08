#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Global variables for FIRST and FOLLOW sets
map<char, set<char>> first;
map<char, set<char>> follow;
map<char, vector<string>> productions;

// Function to add a symbol to a set
void addToSet(set<char> &targetSet, char symbol)
{
  targetSet.insert(symbol);
}

// Compute FIRST set for a non-terminal
void computeFirst(char nonTerminal)
{
  for (const string &production : productions[nonTerminal])
  {
    for (char symbol : production)
    {
      if (!isupper(symbol))
      { // Terminal or epsilon
        addToSet(first[nonTerminal], symbol);
        break;
      }
      else
      { // Non-terminal
        computeFirst(symbol);
        bool hasEpsilon = false;
        for (char subFirst : first[symbol])
        {
          if (subFirst != 'ε')
          {
            addToSet(first[nonTerminal], subFirst);
          }
          else
          {
            hasEpsilon = true;
          }
        }
        if (!hasEpsilon)
          break;
      }
    }
  }
}

// Compute FOLLOW set for all non-terminals
void computeFollow(char startSymbol)
{
  follow[startSymbol].insert('$'); // Start symbol includes end marker

  bool updated;
  do
  {
    updated = false;

    for (const auto &[lhs, productionList] : productions)
    {
      for (const string &production : productionList)
      {
        set<char> trailer = follow[lhs];

        for (auto it = production.rbegin(); it != production.rend(); ++it)
        {
          char symbol = *it;

          if (isupper(symbol))
          { // Non-terminal
            size_t beforeSize = follow[symbol].size();

            follow[symbol].insert(trailer.begin(), trailer.end());
            if (first[symbol].count('ε'))
            {
              trailer.insert(first[symbol].begin(), first[symbol].end());
              trailer.erase('ε');
            }
            else
            {
              trailer = first[symbol];
            }

            if (follow[symbol].size() != beforeSize)
              updated = true;
          }
          else
          {
            trailer = {symbol};
          }
        }
      }
    }
  } while (updated);
}

int main()
{
  // Example grammar
  productions['S'] = {"aSa", "bSb", "A"};
  productions['A'] = {"aBb"};
  productions['B'] = {"aB", "bB", "ε"};

  char startSymbol = 'S';

  // Compute FIRST sets
  for (const auto &[nonTerminal, _] : productions)
  {
    computeFirst(nonTerminal);
  }

  // Compute FOLLOW sets
  computeFollow(startSymbol);

  // Print FIRST sets
  cout << "+-------------------------+\n";
  cout << "|        FIRST Sets       |\n";
  cout << "+-------------------------+\n";
  for (const auto &[nonTerminal, firstSet] : first)
  {
    cout << "| FIRST(" << nonTerminal << ") = { ";
    for (char symbol : firstSet)
    {
      cout << symbol << " ";
    }
    cout << "}\n";
  }
  cout << "+-------------------------+\n";

  // Print FOLLOW sets
  cout << "\n+-------------------------+\n";
  cout << "|       FOLLOW Sets       |\n";
  cout << "+-------------------------+\n";
  for (const auto &[nonTerminal, followSet] : follow)
  {
    cout << "| FOLLOW(" << nonTerminal << ") = { ";
    for (char symbol : followSet)
    {
      cout << symbol << " ";
    }
    cout << "}\n";
  }
  cout << "+-------------------------+\n";

  return 0;
}
