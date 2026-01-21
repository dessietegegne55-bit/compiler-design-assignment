# 🧠 Design of a Type Checker for a Mini Language with Lambda Functions

## 📌 Introduction
A **type checker** is a core component of the **semantic analysis phase** of a compiler.  
Its primary purpose is to ensure **type safety** by verifying that all operations in a program are applied to compatible data types.

This project presents the design of a **type checker for a mini language** extended with support for **lambda (anonymous) functions**, focusing on scope handling, function types, and variable capture.

---

## 🧩 Language Assumptions
The mini language supports the following features:

### 🔹 Data Types
- **Primitive Types:** `Int`, `Bool`
- **Function Types:** `T1 → T2`

### 🔹 Expressions
- Variables  
- Literals  
- Arithmetic expressions  
- Lambda expressions  
- Function applications  

### 🔹 Lambda Syntax
```text
λ(x : T) . e
(x : T) -> e

📂 Symbol Table (Type Environment)

A stack-based symbol table is used to support nested scopes, which are created by lambda expressions.

🔹 Symbol Table Mapping
Identifier → Type

🔹 Operations

enterScope() – create a new scope

exitScope() – remove the current scope

insert(identifier, type) – add identifier to current scope

lookup(identifier) – search from innermost to outer scopes

🔹 Example Symbol Table
Scope Level	Identifier	Type	Notes
0	y	Int	Global variable
1	x	Int	Parameter of λ(x)
1	z	Bool	Local variable
2	a	Int	Nested lambda parameter

Key Points:

Scope Level 0 → Global scope

Scope Levels 1 & 2 → Lambda scopes

Captured variables (e.g., y) are resolved from outer scopes

Lookup proceeds inner → outer

📐 Type Rules
🔹 Variable Rule

If x : T exists in the symbol table:

Γ ⊢ x : T

🔹 Lambda Expression Rule

For λ(x : T1) . e:

Enter a new scope

Insert x : T1

Type-check body e → T2

Exit scope

Resulting type:

Γ ⊢ λ(x : T1) . e : T1 → T2

🔹 Function Application Rule

For e1 e2:

e1 : T1 → T2

e2 : T1

Result type is T2, otherwise a type error occurs

🔁 Return Type Validation

Lambda return types are inferred from the body

If an explicit return type is declared, it must match the inferred type

🔗 Capture Semantics

Captured (free) variables are variables used inside a lambda but declared in an outer scope.

🔹 Rules

Must exist in an enclosing scope

Type is resolved using symbol table lookup

🔹 Example
y : Int
λ(x : Int) . x + y   ✔ Valid capture

⚙️ Type Checking Algorithm (High-Level)
typeCheck(expr, env):
    if expr is literal:
        return literalType
    if expr is variable:
        return env.lookup(expr)
    if expr is lambda (x : T1, body):
        env.enterScope()
        env.insert(x, T1)
        T2 = typeCheck(body, env)
        env.exitScope()
        return T1 → T2
    if expr is application (e1 e2):
        Tfun = typeCheck(e1, env)
        Targ = typeCheck(e2, env)
        ensure Tfun == (Targ → Tret)
        return Tret

❌ Error Handling

The type checker detects and reports:

Use of undeclared variables

Type mismatches in function applications

Invalid variable capture

Return type mismatches in lambda expressions

✅ Conclusion

This design demonstrates a statically typed lambda-capable language with:

Proper scope management

Function parameter validation

Return type inference

Correct handling of captured variables

The stack-based symbol table ensures correctness in nested lambdas and guarantees static type safety, forming a strong foundation for advanced compiler features.

📌 Prepared for academic and educational purposes as part of Compiler Design coursework.


---

### ✅ If you want next
- ✨ Short version (1-page README)
- 🎓 Exam-oriented notes
- 💻 Convert algorithm into **C++ / Java**
- 📂 Integrate into your **Assignment repository**

Just tell me 👍

