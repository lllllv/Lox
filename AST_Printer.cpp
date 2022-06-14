//
// Created by lvxia on 2022/6/1.
//

#include "AST_Printer.h"

void AST_Printer::parenthesize(const string& name, initializer_list<Expr *> exprs) {
    cout << "(" << name;
    for(auto i : exprs)
    {
        cout << " ";
        i->accept(this);
    }
    cout << ")";
}

void AST_Printer::Visit_Literal_Expr(Literal_Expr *l) {
    cout << l->t->lexeme;
}

void AST_Printer::Visit_Unary_Expr(Unary_Expr *u) {
    parenthesize(u->op->lexeme, {u->operand});
}

void AST_Printer::Visit_Binary_Expr(Binary_Expr *b) {
    parenthesize(b->op->lexeme, {b->lhs, b->rhs});
}

void AST_Printer::Visit_Grouping_Expr(Grouping_Expr *g) {
    parenthesize("group", {g->exp});
}

void AST_Printer::print(Expr *exp) {
    exp->accept(this);
    // cout << endl;
}

void AST_Printer::Visit_Expression_Stmt(Expression_Stmt * expression) {

}

void AST_Printer::Visit_Print_Stmt(Print_Stmt * print) {

}

void AST_Printer::Visit_Var_Stmt(Var_Stmt *)
{

}

void AST_Printer::Visit_Variable_Expr(Variable_Expr * expr)
{
    cout << expr->name->lexeme;
}

void AST_Printer::Visit_Assignment_Expr(Assignment_Expr * expr)
{
    cout << "(Assignment " << expr->name->lexeme << " ";
    print(expr->expr);
    cout << ")";
}

void AST_Printer::print(vector<Stmt *> &stmts)
{
    for(auto* stmt : stmts)
    {
        if(typeid(*stmt) == typeid(Print_Stmt))
        {
            Print_Stmt* tmp = dynamic_cast<Print_Stmt*>(stmt);
            cout << "(print ";
            print(tmp->expr);
            cout << " )" << endl;
        }
        else if(typeid(*stmt) == typeid(Var_Stmt))
        {
            Var_Stmt* tmp = dynamic_cast<Var_Stmt*>(stmt);
            cout << "(_LET_ " << tmp->name->lexeme << " ";
            print(tmp->initializer);
            cout << ")" << endl;
        }
        else if(typeid(*stmt) == typeid(Expression_Stmt))
        {
            Expression_Stmt* tmp = dynamic_cast<Expression_Stmt*>(stmt);
            print(tmp->expr);
            cout << endl;
        }
    }
}

void AST_Printer::Visit_Block_Stmt(Block_Stmt *)
{

}

void AST_Printer::Visit_If_Stmt(If_Stmt *)
{

}

void AST_Printer::Visit_Logical_Expr(Logical_Expr *)
{

}



