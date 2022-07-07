//
// Created by lvxia on 2022/6/1.
//

#include "AST.h"


void Literal_Expr::accept(Visitor *v) {
    v->Visit_Literal_Expr(this);
}

Literal_Expr::Literal_Expr(unique_ptr<Token> t) : t(move(t))
{

}

void Unary_Expr::accept(Visitor *v) {
    v->Visit_Unary_Expr(this);
}

Unary_Expr::Unary_Expr(unique_ptr<Token> op, unique_ptr<Expr> operand) : op(move(op)), operand(move(operand))
{

}

void Binary_Expr::accept(Visitor *v) {
    v->Visit_Binary_Expr(this);
}

Binary_Expr::Binary_Expr(unique_ptr<Token> op, unique_ptr<Expr> lhs, unique_ptr<Expr> rhs)
                    : op(move(op)), lhs(move(lhs)), rhs(move(rhs))
{

}

void Grouping_Expr::accept(Visitor *v) {
    v->Visit_Grouping_Expr(this);
}

Grouping_Expr::Grouping_Expr(unique_ptr<Expr> exp) : exp(move(exp))
{

}

Expression_Stmt::Expression_Stmt(unique_ptr<Expr> expr) : expr(move(expr))
{

}

void Expression_Stmt::accept(Visitor *v)
{
    v->Visit_Expression_Stmt(this);
}


Print_Stmt::Print_Stmt(unique_ptr<Expr> expr) : expr(move(expr))
{

}

void Print_Stmt::accept(Visitor *v)
{
    v->Visit_Print_Stmt(this);
}

Var_Stmt::Var_Stmt(unique_ptr<Token> name, unique_ptr<Expr> initializer)
                    : name(move(name)), initializer(move(initializer))
{

}

void Var_Stmt::accept(Visitor *v)
{
    v->Visit_Var_Stmt(this);
}

Variable_Expr::Variable_Expr(unique_ptr<Token> t) : name(move(t))
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

Assignment_Expr::Assignment_Expr(unique_ptr<Token> name, unique_ptr<Expr> expr)
                    : name(move(name)), expr(move(expr))
{

}

void Block_Stmt::accept(Visitor *v)
{
    v->Visit_Block_Stmt(this);
}

Block_Stmt::Block_Stmt(unique_ptr<vector<Stmt *>> stmts) : stmts(move(stmts))
{

}

void If_Stmt::accept(Visitor *v)
{
    v->Visit_If_Stmt(this);
}

If_Stmt::If_Stmt(unique_ptr<Expr> c, unique_ptr<Stmt> t, unique_ptr<Stmt> e)
                : condition(move(c)), then_branch(move(t)), else_branch(move(e))
{

}

void Logical_Expr::accept(Visitor *v)
{
    v->Visit_Logical_Expr(this);
}

Logical_Expr::Logical_Expr(unique_ptr<Expr> left, unique_ptr<Token> op, unique_ptr<Expr> right)
                            : left(move(left)), op(move(op)), right(move(right))
{

}

void While_Stmt::accept(Visitor *v)
{
    v->Visit_While_Stmt(this);
}

While_Stmt::While_Stmt(unique_ptr<Expr> condition, unique_ptr<Stmt> body) : condition(move(condition)), body(move(body))
{

}

void Call_Expr::accept(Visitor *v)
{
    v->Visit_Call_Expr(this);
}

Call_Expr::Call_Expr(unique_ptr<Expr> callee, unique_ptr<Token> paren, vector<Expr *> *arguments)
                        : callee(move(callee)), paren(move(paren)), arguments(arguments)
{

}

void Function_Stmt::accept(Visitor *v)
{
    v->Visit_Function_Stmt(this);
}

Function_Stmt::Function_Stmt(unique_ptr<Token> name, unique_ptr<vector<Token *>> params,
                             unique_ptr<vector<Stmt *>> body)
                                : name(move(name)), params(move(params)), body(move(body))
{

}

void Return_Stmt::accept(Visitor *v)
{
    v->Visit_Return_Stmt(this);
}

Return_Stmt::Return_Stmt(unique_ptr<Token> keyword, unique_ptr<Expr> value)
                            : keyword(move(keyword)), value(move(value))
{

}

void Class_Stmt::accept(Visitor *v)
{
    v->Visit_Class_Stmt(this);
}

Class_Stmt::Class_Stmt(unique_ptr<Token> name, unique_ptr<Variable_Expr> super_class,
                       unique_ptr<vector<Function_Stmt *>> methods)
                       : name(move(name)), methods(move(methods)), super_class(move(super_class))
{

}

void Get_Expr::accept(Visitor *v)
{
    v->Visit_Get_Expr(this);
}

Get_Expr::Get_Expr(unique_ptr<Expr> object, unique_ptr<Token> name) : object(move(object)), name(move(name))
{

}

void Set_Expr::accept(Visitor *v)
{
    v->Visit_Set_Expr(this);
}

Set_Expr::Set_Expr(unique_ptr<Expr> object, unique_ptr<Token> name, unique_ptr<Expr> value)
                    : object(move(object)), name(move(name)), value(move(value))
{

}

void This_Expr::accept(Visitor *v)
{
    v->Visit_This_Expr(this);
}

This_Expr::This_Expr(unique_ptr<Token> keyword) : keyword(move(keyword))
{

}

void Super_Expr::accept(Visitor *v)
{
    v->Visit_Super_Expr(this);
}

Super_Expr::Super_Expr(unique_ptr<Token> keyword, unique_ptr<Token> method)
                        : keyword(move(keyword)), method(move(method))
{

}
