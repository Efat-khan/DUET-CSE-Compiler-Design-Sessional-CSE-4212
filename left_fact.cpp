#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int main()
{
    // Declare variables for storing grammar and its parts
    char gram[100], part1[50], part2[50], modifiedGram[50], newGram[100];
    int i, j = 0, k = 0, pos;

    // Prompt the user to enter a production
    cout << "Enter Production: A-> ";
    fgets(gram, sizeof(gram), stdin); // Read the grammar from standard input (includes spaces)

    // Remove trailing newline character if it exists
    size_t len = strlen(gram);
    if (len > 0 && gram[len - 1] == '\n')
        gram[len - 1] = '\0';

    // Split the input into two parts (before and after the '|')
    for (i = 0; gram[i] != '|' && gram[i] != '\0'; i++, j++)
        part1[j] = gram[i]; // Copy characters before '|' to part1
    part1[j] = '\0';        // Null-terminate the string

    j = 0; // Reset j to reuse for part2
    for (i = i + 1; gram[i] != '\0'; i++, j++)
        part2[j] = gram[i]; // Copy characters after '|' to part2
    part2[j] = '\0';        // Null-terminate the string

    // Identify the common prefix between part1 and part2
    for (i = 0; i < strlen(part1) && i < strlen(part2); i++)
    {
        if (part1[i] == part2[i])
        {
            // If characters match, add them to the modified grammar
            modifiedGram[k++] = part1[i];
            pos = i + 1; // Track the position where the common prefix ends
        }
        else
        {
            break; // Exit the loop when characters no longer match
        }
    }

    // Add the remaining characters of part1 after the common prefix to new grammar
    for (i = pos, j = 0; part1[i] != '\0'; i++, j++)
        newGram[j] = part1[i];

    // Add '|' to separate the options in the new grammar
    newGram[j++] = '|';

    // Add the remaining characters of part2 after the common prefix to new grammar
    for (i = pos; part2[i] != '\0'; i++, j++)
        newGram[j] = part2[i];

    // Append 'X' to the modified grammar as a placeholder for the new production
    modifiedGram[k++] = 'X';
    modifiedGram[k] = '\0'; // Null-terminate the modified grammar

    newGram[j] = '\0'; // Null-terminate the new grammar

    // Output the results: the modified grammar and the new grammar
    cout << "\nA-> [" << modifiedGram << "]"; // Production with common prefix
    cout << "\nX-> [" << newGram << "]";      // New production with remaining options

    return 0;
}
