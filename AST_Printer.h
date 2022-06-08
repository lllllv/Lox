//
// Created by lvxia on 2022/6/1.
//

#ifndef LOX_AST_PRINTER_H
#define LOX_AST_PRINTER_H
#include <initializer_list>
#include <string>
#include <iostream>
#include "visitor.h"
#include "AST.h"

using namespace std;

class AST_Printer : public Visitor {
public:
    ~AST_Printer() override = default;
    void Visit_Literal_Expr(Literal_Expr* l) override;
    void Visit_Unary_Expr(Unary_Expr* u) override;
    void Visit_Binary_Expr(Binary_Expr* b) override;
    void Visit_Grouping_Expr(Grouping_Expr* g) override;
    void parenthesize(const string& name, initializer_list<Expr*> exprs);
    void print(Expr* exp);

    void Visit_Expression(Expression*) override;
    void Visit_Print(Print*) override;
};




#endif //LOX_AST_PRINTER_H
