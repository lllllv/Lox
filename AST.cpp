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

Expression_Stmt::Expression_Stmt(Expr *expr) : expr(expr)
{

}

void Expression_Stmt::accept(Visitor *v)
{
    v->Visit_Expression_Stmt(this);
}

Print_Stmt::Print_Stmt(Expr *expr) : expr(expr)
{

}

void Print_Stmt::accept(Visitor *v)
{
    v->Visit_Print_Stmt(this);
}

Var_Stmt::Var_Stmt(Token *name, Expr *initializer) : name(name), initializer(initializer)
{

}

void Var_Stmt::accept(Visitor *v)
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


void Assignment_Expr::accept(Visitor *v)
{
    v->Visit_Assignment_Expr(this);
}

void Block_Stmt::accept(Visitor *v)
{
    v->Visit_Block_Stmt(this);
}

void If_Stmt::accept(Visitor *v)
{
    v->Visit_If_Stmt(this);
}

void Logical_Expr::accept(Visitor *v)
{
    v->Visit_Logical_Expr(this);
}

void While_Stmt::accept(Visitor *v)
{
    v->Visit_While_Stmt(this);
}

void Call_Expr::accept(Visitor *v)
{
    v->Visit_Call_Expr(this);
}

void Function_Stmt::accept(Visitor *v)
{
    v->Visit_Function_Stmt(this);
}

void Return_Stmt::accept(Visitor *v)
{
    v->Visit_Return_Stmt(this);
}

void Class_Stmt::accept(Visitor *v)
{
    v->Visit_Class_Stmt(this);
}

void Get_Expr::accept(Visitor *v)
{
    v->Visit_Get_Expr(this);
}

void Set_Expr::accept(Visitor *v)
{
    v->Visit_Set_Expr(this);
}
