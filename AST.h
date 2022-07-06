//
// Created by lvxia on 2022/6/1.
//

#ifndef LOX_AST_H
#define LOX_AST_H
#include <utility>

#include "scanner.h"
#include "visitor.h"
//class Visitor;

class AST_Node;
class Expr;


class AST_Node {
public:
    AST_Node() = default;
    virtual ~ AST_Node()= default;
    virtual void accept(Visitor* v) = 0;
};


class Expr : public AST_Node {
public:
    Expr() = default;
    ~Expr() override = default;

};

class Literal_Expr : public Expr {
public:
    Token* t;
    explicit Literal_Expr(Token* t) : t(t) {};
    void accept(Visitor* v) override;
};

class Unary_Expr : public Expr {
public:
    Token* op;
    Expr* operand;
    Unary_Expr(Token* op, Expr* operand) : op(op), operand(operand){};
    void accept(Visitor* v) override;
};

class Binary_Expr : public Expr {
public:
    Token* op;
    Expr* lhs;
    Expr* rhs;
    Binary_Expr(Token* op, Expr* lhs, Expr* rhs) : op(op), lhs(lhs), rhs(rhs){};
    void accept(Visitor* v) override;
};

class Grouping_Expr : public Expr {
public:
    Expr* exp;
    explicit Grouping_Expr(Expr* exp) : exp(exp){};
    void accept(Visitor* v) override;
};

class Variable_Expr : public Expr {
public:
    Token* name;
    explicit Variable_Expr(Token* t);
    void accept(Visitor* v) override;
};

class Assignment_Expr : public Expr {
public:
    Token* name;
    Expr* expr;
    Assignment_Expr(Token* name, Expr* expr) : name(name), expr(expr) {};
    void accept(Visitor* v) override;
};

class Logical_Expr : public Expr {
public:
    Expr* left, *right;
    Token* op;
    Logical_Expr(Expr* left, Token* op, Expr* right) : left(left), op(op), right(right){};
    void accept(Visitor* v) override;
};

class Call_Expr : public Expr {
public:
    Expr* callee;
    Token* paren;
    vector<Expr*>* arguments;
    Call_Expr(Expr* callee, Token* paren, vector<Expr*>* arguments) : callee(callee), paren(paren), arguments(arguments) {};
    void accept(Visitor* v) override;
};

class Get_Expr : public Expr {
public:
    Expr* object;
    Token* name;
    Get_Expr(Expr* object, Token* name) : object(object), name(name){};
    void accept(Visitor* v) override;
};

class Set_Expr : public Expr {
public:
    Expr* object;
    Token* name;
    Expr* value;
    Set_Expr(Expr* object, Token* name, Expr* value) : object(object), name(name), value(value){};
    void accept(Visitor* v) override;
};

class This_Expr : public Expr {
public:
    Token* keyword;
    explicit This_Expr(Token* keyword) : keyword(keyword){};
    void accept(Visitor* v) override;
};

class Super_Expr : public Expr {
public:
    Token* keyword, *method;
    Super_Expr(Token* keyword, Token* method) : keyword(keyword), method(method){};
    void accept(Visitor* v) override;
};


class Stmt : public AST_Node {
public:
    Stmt() = default;
    ~Stmt() override = default;
};

class Expression_Stmt : public Stmt {
public:
    Expr* expr;
    explicit Expression_Stmt(Expr* expr);
    void accept(Visitor* v) override;
};

class Print_Stmt : public Stmt {
public:
    Expr* expr;
    explicit Print_Stmt(Expr* expr);
    void accept(Visitor* v) override;
};

class Var_Stmt : public Stmt {
public:
    Token* name;
    Expr* initializer;
    Var_Stmt(Token* name, Expr* initializer);
    void accept(Visitor* v) override;
};

class Block_Stmt : public Stmt {
public:
    vector<Stmt*>* stmts;
    explicit Block_Stmt(vector<Stmt*>* stmts) : stmts(stmts){};
    void accept(Visitor* v) override;
};

class If_Stmt : public Stmt {
public:
    Expr* condition;
    Stmt* then_branch, * else_branch;
    If_Stmt(Expr* c, Stmt* t, Stmt* e) : condition(c), then_branch(t), else_branch(e){};
    void accept(Visitor* v) override;
};

class While_Stmt : public Stmt {
public:
    Expr* condition;
    Stmt* body;
    While_Stmt(Expr* condition, Stmt* body) : condition(condition), body(body) {};
    void accept(Visitor* v) override;
};

class Function_Stmt : public Stmt {
public:
    Token* name;
    vector<Token*>* params;
    vector<Stmt*>* body;
    Function_Stmt(Token* name, vector<Token*>* params, vector<Stmt*>* body) : name(name), params(params), body(body) {};
    void accept(Visitor* v) override;
};

class Return_Stmt : public Stmt {
public:
    Token* keyword;
    Expr* value;
    Return_Stmt(Token* keyword, Expr* value) : keyword(keyword), value(value){};
    void accept(Visitor* v) override;
};

class Class_Stmt : public Stmt {
public:
    Token* name;
    Variable_Expr* super_class;
    vector<Function_Stmt*>* methods;
    Class_Stmt(Token* name, Variable_Expr* super_class, vector<Function_Stmt*>* methods)
        : name(name), methods(methods), super_class(super_class){};
    void accept(Visitor* v) override;
};

#endif //LOX_AST_H
