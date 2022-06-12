//
// Created by lvxia on 2022/6/1.
//

#include "AST.h"


void Literal_Expr::accept(Visitor *v) {
    v->Visit_Literal_Expr(this);
}

void Unary_Expr::accept(Visitor *v) {
    v->Visit_Unary_Expr(this);
}

void Binary_Expr::accept(Visitor *v) {
    v->Visit_Binary_Expr(this);
}

void Grouping_Expr::accept(Visitor *v) {
    v->Visit_Grouping_Expr(this);
}

Expression::Expression(Expr *expr) : expr(expr)
{

}

void Expression::accept(Visitor *v)
{
    v->Visit_Expression_Stmt(this);
}

Print::Print(Expr *expr) : expr(expr)
{

}

void Print::accept(Visitor *v)
{
    v->Visit_Print_Stmt(this);
}

Var::Var(Token *name, Expr *initializer) : name(name), initializer(initializer)
{

}

void Var::accept(Visitor *v)
{
    v->Visit_Var_Stmt(this);
}

Variable_Expr::Variable_Expr(Token *t) : name(t)
{

}

void Variable_Expr::accept(Visitor *v)
{
    v->Visit_Variable_Expr(this);
}
