#ifndef LOX_AST_PRINTER_H
#define LOX_AST_PRINTER_H
#include <initializer_list>
#include <string>
#include <iostream>
#include <memory>

#include "visitor.h"
#include "AST.h"

using namespace std;

class AST_Printer : public Visitor {
public:
    ~AST_Printer() override = default;
    void Visit_Literal_Expr(shared_ptr<Literal_Expr> l) override;
    void Visit_Unary_Expr(shared_ptr<Unary_Expr> u) override;
    void Visit_Binary_Expr(shared_ptr<Binary_Expr> b) override;
    void Visit_Grouping_Expr(shared_ptr<Grouping_Expr> g) override;
    void Visit_Variable_Expr(shared_ptr<Variable_Expr>) override;
    void Visit_Assignment_Expr(shared_ptr<Assignment_Expr>) override;
    void Visit_Logical_Expr(shared_ptr<Logical_Expr>) override;
    void Visit_Call_Expr(shared_ptr<Call_Expr>) override;



    void parenthesize(const string& name, initializer_list<shared_ptr<Expr>> exprs);
    void print(const shared_ptr<Expr>& exp);
    void print(vector<shared_ptr<Stmt>>& stmts);

    void Visit_Expression_Stmt(shared_ptr<Expression_Stmt>) override;
    void Visit_Print_Stmt(shared_ptr<Print_Stmt>) override;
    void Visit_Var_Stmt(shared_ptr<Var_Stmt>) override;
    void Visit_Block_Stmt(shared_ptr<Block_Stmt>) override;
    void Visit_If_Stmt(shared_ptr<If_Stmt>) override;
    void Visit_While_Stmt(shared_ptr<While_Stmt>) override;
    void Visit_Function_Stmt(shared_ptr<Function_Stmt>) override;
    void Visit_Return_Stmt(shared_ptr<Return_Stmt>) override;
};



#endif //LOX_AST_PRINTER_H
