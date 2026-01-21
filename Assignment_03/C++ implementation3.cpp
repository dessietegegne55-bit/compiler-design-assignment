#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <stdexcept>

// --------------------------- Symbol Table ---------------------------
struct Type {
    std::string name; // "Int", "Bool", or "Func"
    std::shared_ptr<Type> param;   // for function type
    std::shared_ptr<Type> ret;     // for function type

    Type(std::string n) : name(n), param(nullptr), ret(nullptr) {}
    Type(std::shared_ptr<Type> p, std::shared_ptr<Type> r) : name("Func"), param(p), ret(r) {}
};

struct SymbolTable {
    std::vector<std::unordered_map<std::string, std::shared_ptr<Type>>> scopes;

    SymbolTable() { enterScope(); }

    void enterScope() {
        scopes.push_back({});
    }

    void exitScope() {
        if (!scopes.empty()) scopes.pop_back();
    }

    void insert(const std::string& name, std::shared_ptr<Type> type) {
        if (scopes.empty()) throw std::runtime_error("No active scope");
        scopes.back()[name] = type;
    }

    std::shared_ptr<Type> lookup(const std::string& name) {
        for (int i = scopes.size() - 1; i >= 0; i--) {
            if (scopes[i].count(name)) return scopes[i][name];
        }
        throw std::runtime_error("Undeclared variable: " + name);
    }
};

// --------------------------- AST Nodes ---------------------------
struct Expr {
    virtual std::shared_ptr<Type> typeCheck(SymbolTable& env) = 0;
    virtual ~Expr() {}
};

struct Var : Expr {
    std::string name;
    Var(const std::string& n) : name(n) {}
    std::shared_ptr<Type> typeCheck(SymbolTable& env) override {
        return env.lookup(name);
    }
};

struct IntLit : Expr {
    int value;
    IntLit(int v) : value(v) {}
    std::shared_ptr<Type> typeCheck(SymbolTable& env) override {
        return std::make_shared<Type>("Int");
    }
};

struct Lambda : Expr {
    std::string param;
    std::shared_ptr<Type> paramType;
    std::shared_ptr<Expr> body;

    Lambda(std::string p, std::shared_ptr<Type> pt, std::shared_ptr<Expr> b)
        : param(p), paramType(pt), body(b) {}

    std::shared_ptr<Type> typeCheck(SymbolTable& env) override {
        env.enterScope();
        env.insert(param, paramType);
        std::shared_ptr<Type> retType = body->typeCheck(env);
        env.exitScope();
        return std::make_shared<Type>(paramType, retType);
    }
};

struct Apply : Expr {
    std::shared_ptr<Expr> func;
    std::shared_ptr<Expr> arg;

    Apply(std::shared_ptr<Expr> f, std::shared_ptr<Expr> a) : func(f), arg(a) {}

    std::shared_ptr<Type> typeCheck(SymbolTable& env) override {
        std::shared_ptr<Type> funcType = func->typeCheck(env);
        std::shared_ptr<Type> argType = arg->typeCheck(env);
        if (funcType->name != "Func") throw std::runtime_error("Not a function");
        if (funcType->param->name != argType->name) throw std::runtime_error("Function argument type mismatch");
        return funcType->ret;
    }
};

// --------------------------- Example Usage ---------------------------
int main() {
    SymbolTable env;
    env.insert("y", std::make_shared<Type>("Int")); // global variable

    // λ(x : Int) . x + y
    auto body = std::make_shared<Apply>(
        std::make_shared<Var>("x"),  // pretend '+' is handled here
        std::make_shared<Var>("y")
    );
    auto lambda = std::make_shared<Lambda>("x", std::make_shared<Type>("Int"), body);

    try {
        std::shared_ptr<Type> t = lambda->typeCheck(env);
        std::cout << "Lambda type: " << t->param->name << " -> " << t->ret->name << std::endl;
    } catch (std::runtime_error& e) {
        std::cout << "Type error: " << e.what() << std::endl;
    }

    return 0;
}
