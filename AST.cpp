#include "AST.h"

#include <utility>


void Literal_Expr::accept(Visitor *v) {
    v->Visit_Literal_Expr(static_pointer_cast<Literal_Expr>(shared_from_this()));
}

Literal_Expr::Literal_Expr(shared_ptr<Token> t) : t(move(t))
{

}

void Unary_Expr::accept(Visitor *v) {
    v->Visit_Unary_Expr(static_pointer_cast<Unary_Expr>(shared_from_this()));
}

Unary_Expr::Unary_Expr(shared_ptr<Token> op, shared_ptr<Expr> operand) : op(move(op)), operand(std::move(operand))
{

}

void Binary_Expr::accept(Visitor *v) {
    v->Visit_Binary_Expr(static_pointer_cast<Binary_Expr>(shared_from_this()));
}

Binary_Expr::Binary_Expr(shared_ptr<Token> op, shared_ptr<Expr> lhs, shared_ptr<Expr> rhs)
                    : op(move(op)), lhs(move(lhs)), rhs(move(rhs))
{

}

void Grouping_Expr::accept(Visitor *v) {
    v->Visit_Grouping_Expr(static_pointer_cast<Grouping_Expr>(shared_from_this()));
}

Grouping_Expr::Grouping_Expr(shared_ptr<Expr> exp) : exp(move(exp))
{

}

Expression_Stmt::Expression_Stmt(shared_ptr<Expr> expr) : expr(move(expr))
{

}

void Expression_Stmt::accept(Visitor *v)
{
    v->Visit_Expression_Stmt(static_pointer_cast<Expression_Stmt>(shared_from_this()));
}


Print_Stmt::Print_Stmt(shared_ptr<Expr> expr) : expr(move(expr))
{

}

void Print_Stmt::accept(Visitor *v)
{
    v->Visit_Print_Stmt(static_pointer_cast<Print_Stmt>(shared_from_this()));
}

Var_Stmt::Var_Stmt(shared_ptr<Token> name, shared_ptr<Expr> initializer)
                    : name(move(name)), initializer(move(initializer))
{

}

void Var_Stmt::accept(Visitor *v)
{
    v->Visit_Var_Stmt(static_pointer_cast<Var_Stmt>(shared_from_this()));
}

Variable_Expr::Variable_Expr(shared_ptr<Token> t) : name(move(t))
{

}

void Variable_Expr::accept(Visitor *v)
{
    v->Visit_Variable_Expr(static_pointer_cast<Variable_Expr>(shared_from_this()));
}


void Assignment_Expr::accept(Visitor *v)
{
    v->Visit_Assignment_Expr(static_pointer_cast<Assignment_Expr>(shared_from_this()));
}

Assignment_Expr::Assignment_Expr(shared_ptr<Token> name, shared_ptr<Expr> expr)
                    : name(move(name)), expr(move(expr))
{

}

void Block_Stmt::accept(Visitor *v)
{
    v->Visit_Block_Stmt(static_pointer_cast<Block_Stmt>(shared_from_this()));
}

Block_Stmt::Block_Stmt(shared_ptr<vector<shared_ptr<Stmt>>> stmts) : stmts(move(stmts))
{

}

void If_Stmt::accept(Visitor *v)
{
    v->Visit_If_Stmt(static_pointer_cast<If_Stmt>(shared_from_this()));
}

If_Stmt::If_Stmt(shared_ptr<Expr> c, shared_ptr<Stmt> t, shared_ptr<Stmt> e)
                : condition(move(c)), then_branch(move(t)), else_branch(move(e))
{

}

void Logical_Expr::accept(Visitor *v)
{
    v->Visit_Logical_Expr(static_pointer_cast<Logical_Expr>(shared_from_this()));
}

Logical_Expr::Logical_Expr(shared_ptr<Expr> left, shared_ptr<Token> op, shared_ptr<Expr> right)
                            : left(move(left)), op(move(op)), right(move(right))
{

}

void While_Stmt::accept(Visitor *v)
{
    v->Visit_While_Stmt(static_pointer_cast<While_Stmt>(shared_from_this()));
}

While_Stmt::While_Stmt(shared_ptr<Expr> condition, shared_ptr<Stmt> body) : condition(move(condition)), body(move(body))
{

}

void Call_Expr::accept(Visitor *v)
{
    v->Visit_Call_Expr(static_pointer_cast<Call_Expr>(shared_from_this()));
}

Call_Expr::Call_Expr(shared_ptr<Expr> callee, shared_ptr<Token> paren, shared_ptr<vector<shared_ptr<Expr>>>arguments)
                        : callee(move(callee)), paren(move(paren)), arguments(std::move(arguments))
{

}

void Function_Stmt::accept(Visitor *v)
{
    v->Visit_Function_Stmt(static_pointer_cast<Function_Stmt>(shared_from_this()));
}

Function_Stmt::Function_Stmt(shared_ptr<Token> name, shared_ptr<vector<shared_ptr<Token>>> params,
                             shared_ptr<vector<shared_ptr<Stmt>>> body)
                                : name(move(name)), params(move(params)), body(move(body))
{

}

void Return_Stmt::accept(Visitor *v)
{
    v->Visit_Return_Stmt(static_pointer_cast<Return_Stmt>(shared_from_this()));
}

Return_Stmt::Return_Stmt(shared_ptr<Token> keyword, shared_ptr<Expr> value)
                            : keyword(move(keyword)), value(move(value))
{

}

void Class_Stmt::accept(Visitor *v)
{
    v->Visit_Class_Stmt(static_pointer_cast<Class_Stmt>(shared_from_this()));
}

Class_Stmt::Class_Stmt(shared_ptr<Token> name, shared_ptr<Variable_Expr> super_class,
                       shared_ptr<vector<shared_ptr<Function_Stmt>>> methods)
                       : name(move(name)), methods(move(methods)), super_class(move(super_class))
{

}

void Get_Expr::accept(Visitor *v)
{
    v->Visit_Get_Expr(static_pointer_cast<Get_Expr>(shared_from_this()));
}

Get_Expr::Get_Expr(shared_ptr<Expr> object, shared_ptr<Token> name) : object(move(object)), name(move(name))
{

}

void Set_Expr::accept(Visitor *v)
{
    v->Visit_Set_Expr(static_pointer_cast<Set_Expr>(shared_from_this()));
}

Set_Expr::Set_Expr(shared_ptr<Expr> object, shared_ptr<Token> name, shared_ptr<Expr> value)
                    : object(move(object)), name(move(name)), value(move(value))
{

}

void This_Expr::accept(Visitor *v)
{
    v->Visit_This_Expr(static_pointer_cast<This_Expr>(shared_from_this()));
}

This_Expr::This_Expr(shared_ptr<Token> keyword) : keyword(move(keyword))
{

}

void Super_Expr::accept(Visitor *v)
{
    v->Visit_Super_Expr(static_pointer_cast<Super_Expr>(shared_from_this()));
}

Super_Expr::Super_Expr(shared_ptr<Token> keyword, shared_ptr<Token> method)
                        : keyword(move(keyword)), method(move(method))
{

}
