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
    cout << endl;
}

void AST_Printer::Visit_Expression_Stmt(Expression * expression) {

}

void AST_Printer::Visit_Print_Stmt(Print * print) {

}

void AST_Printer::Visit_Var_Stmt(Var *)
{

}

void AST_Printer::Visit_Variable_Expr(Variable_Expr *)
{

}

void AST_Printer::Visit_Assignment_Expr(Assignment_Expr *)
{

}


