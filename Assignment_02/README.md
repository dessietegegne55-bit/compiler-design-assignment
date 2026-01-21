## 📘 Identifier and Keyword Recognition – Compiler Design

### 📌 Overview
This presentation explains how **identifiers and keywords are distinguished** during the
**lexical analysis phase** of a compiler. It focuses on the fundamental role of the **lexer (scanner)**
in converting a source program into a valid stream of tokens for further compilation phases.

---

## 🎯 Objectives
- Understand the role of **lexical analysis** in compiler design  
- Differentiate between **keywords** and **identifiers**  
- Learn how **finite automata (DFA)** and **regular expressions** are used for token recognition  
- Explain the use of **keyword tables** and **symbol tables**  

---

## 🧠 Topics Covered
- What is a compiler and why tokenization is important  
- Overview of **compiler phases**  
- Definition and characteristics of:
  - **Keywords** (reserved words with fixed meaning)
  - **Identifiers** (user-defined names)
- Recognition mechanisms:
  - Regular expressions
  - Deterministic Finite Automata (DFA)
  - Keyword lookup tables
- Rules, examples, and common lexical errors  
- Best practices in lexical analysis  

---

## ⚙️ Key Concepts Explained
- **Lexical Analysis** converts character streams into tokens  
- **Keywords** are matched using exact lookup and have higher priority  
- **Identifiers** follow specific patterns and are stored in the symbol table  
- The **longest match rule** ensures correct token recognition  

---

## 📂 Repository Context
This presentation is part of the **Compiler Design coursework** and supports theoretical
understanding of:
- Token classification
- Error-free parsing
- Efficient compiler implementation

---

## 📚 References
- Aho, Sethi, Ullman – *Compilers: Principles, Techniques, and Tools*  
- GeeksforGeeks – Compiler Phases & Lexical Analysis  
- Tutorialspoint – Symbol Table and Lexical Analysis  

---

📌 *Prepared for academic and educational purposes as part of the Compiler Design course.*

