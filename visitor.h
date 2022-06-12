//
// Created by lvxia on 2022/6/1.
//

#ifndef LOX_VISITOR_H
#define LOX_VISITOR_H

class Expr;
class Literal_Expr;
class Unary_Expr;
class Binary_Expr;
class Grouping_Expr;
class Variable_Expr;
class Assignment_Expr;

class Stmt;
class Expression;
class Print;
class Var;

class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void Visit_Literal_Expr(Literal_Expr*) = 0;
    virtual void Visit_Unary_Expr(Unary_Expr*) = 0;
    virtual void Visit_Binary_Expr(Binary_Expr*) = 0;
    virtual void Visit_Grouping_Expr(Grouping_Expr*) = 0;
    virtual void Visit_Variable_Expr(Variable_Expr*) = 0;
    virtual void Visit_Assignment_Expr(Assignment_Expr*) = 0;

    virtual void Visit_Expression_Stmt(Expression*) = 0;
    virtual void Visit_Print_Stmt(Print*) = 0;
    virtual void Visit_Var_Stmt(Var*) = 0;
};







#endif //LOX_VISITOR_H
