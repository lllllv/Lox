#include "AST_Printer.h"

void AST_Printer::parenthesize(const string& name, initializer_list<shared_ptr<Expr>> exprs) {
    cout << "(" << name;
    for(const auto& i : exprs)
    {
        cout << " ";
        i->accept(this);
    }
    cout << ")";
}

void AST_Printer::Visit_Literal_Expr(shared_ptr<Literal_Expr> l) {
    cout << l->t->lexeme;
}

void AST_Printer::Visit_Unary_Expr(shared_ptr<Unary_Expr> u) {
    parenthesize(u->op->lexeme, {u->operand});
}

void AST_Printer::Visit_Binary_Expr(shared_ptr<Binary_Expr> b) {
    parenthesize(b->op->lexeme, {b->lhs, b->rhs});
}

void AST_Printer::Visit_Grouping_Expr(shared_ptr<Grouping_Expr> g) {
    parenthesize("group", {g->exp});
}

void AST_Printer::print(const shared_ptr<Expr>& exp) {
    if(exp != nullptr)
        exp->accept(this);
}

void AST_Printer::Visit_Expression_Stmt(shared_ptr<Expression_Stmt> expression) {

}

void AST_Printer::Visit_Print_Stmt(shared_ptr<Print_Stmt> print) {

}

void AST_Printer::Visit_Var_Stmt(shared_ptr<Var_Stmt>)
{

}

void AST_Printer::Visit_Variable_Expr(shared_ptr<Variable_Expr> expr)
{
    cout << expr->name->lexeme;
}

void AST_Printer::Visit_Assignment_Expr(shared_ptr<Assignment_Expr> expr)
{
    cout << "(Assignment " << expr->name->lexeme << " ";
    print(expr->expr);
    cout << ")";
}

void AST_Printer::print(vector<shared_ptr<Stmt>> &stmts)
{
    for(const auto& stmt : stmts)
    {
        if(typeid(stmt) == typeid(Print_Stmt))
        {
            auto tmp = dynamic_pointer_cast<Print_Stmt>(stmt);
            cout << "(print ";
            print(tmp->expr);
            cout << " )" << endl;
        }
        else if(typeid(stmt) == typeid(Var_Stmt))
        {
            auto tmp = dynamic_pointer_cast<Var_Stmt>(stmt);
            cout << "(_LET_ " << tmp->name->lexeme << " ";
            print(tmp->initializer);
            cout << ")" << endl;
        }
        else if(typeid(stmt) == typeid(Expression_Stmt))
        {
            auto tmp = dynamic_pointer_cast<Expression_Stmt>(stmt);
            print(tmp->expr);
            cout << endl;
        }
    }
}

void AST_Printer::Visit_Block_Stmt(shared_ptr<Block_Stmt>)
{

}

void AST_Printer::Visit_If_Stmt(shared_ptr<If_Stmt>)
{

}

void AST_Printer::Visit_Logical_Expr(shared_ptr<Logical_Expr>)
{

}

void AST_Printer::Visit_While_Stmt(shared_ptr<While_Stmt>)
{

}

void AST_Printer::Visit_Call_Expr(shared_ptr<Call_Expr>)
{

}

void AST_Printer::Visit_Function_Stmt(shared_ptr<Function_Stmt>)
{

}

void AST_Printer::Visit_Return_Stmt(shared_ptr<Return_Stmt>)
{

}


