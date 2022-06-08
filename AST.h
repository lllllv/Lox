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


class Stmt : public AST_Node {
public:
    Stmt() = default;
    ~Stmt() override = default;
};

class Expression : public Stmt {
public:
    Expr* expr;
    explicit Expression(Expr* expr);
    void accept(Visitor* v) override;
};

class Print : public Stmt {
public:
    Expr* expr;
    explicit Print(Expr* expr);
    void accept(Visitor* v) override;
};

#endif //LOX_AST_H
