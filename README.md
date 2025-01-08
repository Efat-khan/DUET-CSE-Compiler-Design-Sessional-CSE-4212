# Compiler Design Topics 📚💻

This document covers various key concepts and techniques in compiler design. Below are the details:

---

### 1. **Lexical Analyzer** 🧑‍💻🔍  
The lexical analyzer (lexer) is the first phase of a compiler. It reads the source code and breaks it down into **tokens** such as keywords, identifiers, literals, operators, etc.

---

### 2. **First/Follow Determination** 🧑‍🏫📏  
Used in **context-free grammar** to help construct parsers.  
- **First**: The set of terminals that can appear at the beginning of any string derived from a non-terminal.  
- **Follow**: The set of terminals that can appear immediately after a non-terminal in any derivation.

---

### 3. **Non-recursive Predictive Parser (LL(1))** 🤖📊  
A **top-down parser** that uses a single lookahead token to make parsing decisions.  
It’s non-recursive and utilizes a **parsing table** for decision making. The **1** indicates the lookahead of one token.

---

### 4. **Left Recursion & Left Factoring** ↩️🔄  
- **Left Recursion**: A type of recursion that can cause infinite recursion in parsers.  
- **Left Factoring**: A technique to eliminate ambiguity and optimize parsers by factoring out common prefixes.

---

### 5. **Three Address Code (TAC)** 🖥️💡  
An intermediate representation in compilers where each instruction has at most **three operands**. TAC helps in optimizing the program and generating efficient machine code.

---

### 6. **Infix to Postfix Conversion** ➡️💬  
A method to convert infix expressions (e.g., `A + B`) into postfix expressions (e.g., `A B +`), which is easier for a machine to process.

---

### 7. **Operator Precedence Parser** ⏩📐  
A **bottom-up parser** that decides which operators to apply based on their precedence levels and associativity. It handles **operator precedence rules** to construct parse trees.

---

### 8. **Shift-Reduce Parser** ↔️🔄  
A type of **bottom-up parser** that performs shifts and reductions to reduce input symbols into non-terminals based on production rules.

---

### 9. **Symbol Table & Self-Organization** 📋💾  
A **symbol table** stores information about variables, functions, objects, and other constructs in a program.  
**Self-organization** refers to automatic adjustments made to optimize the symbol table.

---

### 10. **Regular Expression** ✨🔤  
A sequence of characters that defines a search pattern. Regular expressions are widely used in **lexical analysis** to match patterns in the source code and **tokenize** the input.

---

Hope this guide helps you dive into the world of compilers! 🚀✨
"# DUET-CSE-Compiler-Design-Sessional-CSE-4212" 
