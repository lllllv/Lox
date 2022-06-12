//
// Created by lvxia on 2022/6/7.
//

#ifndef LOX_INTERPRETER_H
#define LOX_INTERPRETER_H
#include <stack>
#include <exception>
#include "AST.h"
#include "visitor.h"
#include "lox_object.h"
#include "interpreter_exceptions.h"
#include "environment.h"

using namespace std;



class interpreter : public Visitor{
private:
    //Expr* expr;
    environment env;
    stack<lox_object> im_results;
    static bool is_truthy(const lox_object&);
    static bool is_equal(const lox_object&, const lox_object&);

    void Visit_Literal_Expr(Literal_Expr* l) override;
    void Visit_Grouping_Expr(Grouping_Expr* g) override;
    void Visit_Unary_Expr(Unary_Expr* u) override;
    void Visit_Binary_Expr(Binary_Expr* b) override;
    void Visit_Variable_Expr(Variable_Expr*) override;

    void Visit_Expression_Stmt(Expression*) override;
    void Visit_Print_Stmt(Print*) override;
    void Visit_Var_Stmt(Var*) override;

    void _evaluate(Expr* exp);
    void _execute(Stmt* stmt);
    static void _print_lox_object(const lox_object&);
public:
    ~interpreter() override = default;
    explicit interpreter() = default;
    void eval(Expr* exp);
    void interpret(const vector<Stmt*>& stmts);
};


#endif //LOX_INTERPRETER_H
