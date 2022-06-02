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
    Expr() = default;;
    virtual ~Expr() = default;
};

class Literal_Expr : public Expr {
public:
    Token* t;
    explicit Literal_Expr(Token* t) : t(t) {};
    virtual void accept(Visitor* v);
};

class Unary_Expr : public Expr {
public:
    Token* op;
    Expr* operand;
    Unary_Expr(Token* op, Expr* operand) : op(op), operand(operand){};
    virtual void accept(Visitor* v);
};

class Binary_Expr : public Expr {
public:
    Token* op;
    Expr* lhs;
    Expr* rhs;
    Binary_Expr(Token* op, Expr* lhs, Expr* rhs) : op(op), lhs(lhs), rhs(rhs){};
    virtual void accept(Visitor* v);
};

class Grouping_Expr : public Expr {
public:
    Expr* exp;
    explicit Grouping_Expr(Expr* exp) : exp(exp){};
    virtual void accept(Visitor* v);
};

#endif //LOX_AST_H
