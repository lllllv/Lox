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

#endif //LOX_AST_H
