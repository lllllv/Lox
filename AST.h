#pragma once
#include <utility>

#include "scanner.h"
#include "visitor.h"


class AST_Node {
public:
    AST_Node() = default;
    virtual ~ AST_Node() = default;
    virtual void accept(Visitor* v) = 0;
};


class Expr : public AST_Node, public enable_shared_from_this<Expr> {
public:
    Expr() = default;
    ~Expr() override = default;
};

class Literal_Expr : public Expr/*, enable_shared_from_this<Literal_Expr>*/ {
public:
    shared_ptr<Token> t;
    explicit Literal_Expr(shared_ptr<Token> t);
    void accept(Visitor* v) override;
};

class Unary_Expr : public Expr/*, enable_shared_from_this<Unary_Expr>*/ {
public:
    shared_ptr<Token> op;
    shared_ptr<Expr> operand;
    Unary_Expr(shared_ptr<Token> op, shared_ptr<Expr> operand);
    void accept(Visitor* v) override;
};

class Binary_Expr : public Expr/*, enable_shared_from_this<Binary_Expr>*/ {
public:
    shared_ptr<Token> op;
    shared_ptr<Expr> lhs;
    shared_ptr<Expr> rhs;
    Binary_Expr(shared_ptr<Token> op, shared_ptr<Expr> lhs, shared_ptr<Expr> rhs);
    void accept(Visitor* v) override;
};

class Grouping_Expr : public Expr/*, enable_shared_from_this<Grouping_Expr>*/ {
public:
    shared_ptr<Expr> exp;
    explicit Grouping_Expr(shared_ptr<Expr> exp);
    void accept(Visitor* v) override;
};

class Variable_Expr : public Expr/*, enable_shared_from_this<Variable_Expr>*/ {
public:
    shared_ptr<Token> name;
    explicit Variable_Expr(shared_ptr<Token> t);
    void accept(Visitor* v) override;
};

class Assignment_Expr : public Expr/*, enable_shared_from_this<Assignment_Expr>*/ {
public:
    shared_ptr<Token> name;
    shared_ptr<Expr> expr;
    Assignment_Expr(shared_ptr<Token> name, shared_ptr<Expr> expr);
    void accept(Visitor* v) override;
};

class Logical_Expr : public Expr/*, enable_shared_from_this<Logical_Expr>*/ {
public:
    shared_ptr<Expr> left, right;
    shared_ptr<Token> op;
    Logical_Expr(shared_ptr<Expr> left, shared_ptr<Token> op, shared_ptr<Expr> right);
    void accept(Visitor* v) override;
};

class Call_Expr : public Expr/*, enable_shared_from_this<Call_Expr>*/ {
public:
    shared_ptr<Expr> callee;
    shared_ptr<Token> paren;
    shared_ptr<vector<shared_ptr<Expr>>> arguments;
    Call_Expr(shared_ptr<Expr> callee, shared_ptr<Token> paren, shared_ptr<vector<shared_ptr<Expr>>> arguments);
    void accept(Visitor* v) override;
};

class Get_Expr : public Expr/*, enable_shared_from_this<Get_Expr>*/ {
public:
    shared_ptr<Expr> object;
    shared_ptr<Token> name;
    Get_Expr(shared_ptr<Expr> object, shared_ptr<Token> name);
    void accept(Visitor* v) override;
};

class Set_Expr : public Expr/*, enable_shared_from_this<Set_Expr>*/ {
public:
    shared_ptr<Expr> object;
    shared_ptr<Token> name;
    shared_ptr<Expr> value;
    Set_Expr(shared_ptr<Expr> object, shared_ptr<Token> name, shared_ptr<Expr> value);
    void accept(Visitor* v) override;
};

class This_Expr : public Expr/*, enable_shared_from_this<This_Expr>*/ {
public:
    shared_ptr<Token> keyword;
    explicit This_Expr(shared_ptr<Token> keyword);
    void accept(Visitor* v) override;
};

class Super_Expr : public Expr/*, enable_shared_from_this<Super_Expr>*/ {
public:
    shared_ptr<Token> keyword, method;
    Super_Expr(shared_ptr<Token> keyword, shared_ptr<Token> method);
    void accept(Visitor* v) override;
};


class Stmt : public AST_Node, public enable_shared_from_this<Stmt> {
public:
    Stmt() = default;
    ~Stmt() override = default;
};

class Expression_Stmt : public Stmt {
public:
    shared_ptr<Expr> expr;
    explicit Expression_Stmt(shared_ptr<Expr> expr);
    void accept(Visitor* v) override;
};

class Print_Stmt : public Stmt/*, private enable_shared_from_this<Print_Stmt>*/ {
public:
    shared_ptr<Expr> expr;
    explicit Print_Stmt(shared_ptr<Expr> expr);
    void accept(Visitor* v) override;
};

class Var_Stmt : public Stmt {
public:
    shared_ptr<Token> name;
    shared_ptr<Expr> initializer;
    Var_Stmt(shared_ptr<Token> name, shared_ptr<Expr> initializer);
    void accept(Visitor* v) override;
};

class Block_Stmt : public Stmt/*, enable_shared_from_this<Block_Stmt>*/ {
public:
    shared_ptr<vector<shared_ptr<Stmt>>> stmts;
    explicit Block_Stmt(shared_ptr<vector<shared_ptr<Stmt>>> stmts);
    void accept(Visitor* v) override;
};

class If_Stmt : public Stmt/*, enable_shared_from_this<If_Stmt>*/ {
public:
    shared_ptr<Expr> condition;
    shared_ptr<Stmt> then_branch, else_branch;
    If_Stmt(shared_ptr<Expr> c, shared_ptr<Stmt> t, shared_ptr<Stmt> e);
    void accept(Visitor* v) override;
};

class While_Stmt : public Stmt/*, enable_shared_from_this<While_Stmt>*/ {
public:
    shared_ptr<Expr> condition;
    shared_ptr<Stmt> body;
    While_Stmt(shared_ptr<Expr> condition, shared_ptr<Stmt> body);
    void accept(Visitor* v) override;
};

class Function_Stmt : public Stmt/*, enable_shared_from_this<Function_Stmt>*/ {
public:
    shared_ptr<Token> name;
    shared_ptr<vector<shared_ptr<Token>>> params;
    shared_ptr<vector<shared_ptr<Stmt>>> body;
    Function_Stmt(shared_ptr<Token> name, shared_ptr<vector<shared_ptr<Token>>> params, shared_ptr<vector<shared_ptr<Stmt>>> body);
    void accept(Visitor* v) override;
};

class Return_Stmt : public Stmt/*, enable_shared_from_this<Return_Stmt>*/ {
public:
    shared_ptr<Token> keyword;
    shared_ptr<Expr> value;
    Return_Stmt(shared_ptr<Token> keyword, shared_ptr<Expr> value);
    void accept(Visitor* v) override;
};

class Class_Stmt : public Stmt/*, enable_shared_from_this<Class_Stmt>*/ {
public:
    shared_ptr<Token> name;
    shared_ptr<Variable_Expr> super_class;
    shared_ptr<vector<shared_ptr<Function_Stmt>>> methods;
    Class_Stmt(shared_ptr<Token> name, shared_ptr<Variable_Expr> super_class, shared_ptr<vector<shared_ptr<Function_Stmt>>> methods);
    void accept(Visitor* v) override;
};
