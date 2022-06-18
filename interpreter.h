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
#include "lox_callable.h"
#include "interpreter_exceptions.h"
#include "environment.h"

using namespace std;



class interpreter : public Visitor{
private:
    //Expr* expr;
    environment* env;
    stack<lox_object*> im_results;
    static bool is_truthy(const lox_object&);
    static bool is_equal(const lox_object&, const lox_object&);

    void Visit_Literal_Expr(Literal_Expr* l) override;
    void Visit_Grouping_Expr(Grouping_Expr* g) override;
    void Visit_Unary_Expr(Unary_Expr* u) override;
    void Visit_Binary_Expr(Binary_Expr* b) override;
    void Visit_Variable_Expr(Variable_Expr*) override;
    void Visit_Assignment_Expr(Assignment_Expr*) override;
    void Visit_Logical_Expr(Logical_Expr*) override;
    void Visit_Call_Expr(Call_Expr*) override;

    void Visit_Expression_Stmt(Expression_Stmt*) override;
    void Visit_Print_Stmt(Print_Stmt*) override;
    void Visit_Var_Stmt(Var_Stmt*) override;
    void Visit_Block_Stmt(Block_Stmt*) override;
    void Visit_If_Stmt(If_Stmt*) override;
    void Visit_While_Stmt(While_Stmt*) override;
    void Visit_Function_Stmt(Function_Stmt*) override;


    void _evaluate(Expr* exp);
    bool _evaluate_cond(Expr* expr);
    void _execute(Stmt* stmt);
    void _execute_Block(vector<Stmt*>* stmts, environment* new_env);
    static void _print_lox_object(const lox_object&);
public:
    ~interpreter() override = default;
    interpreter();
    void eval(Expr* exp);
    void interpret(const vector<Stmt*>& stmts);
};


#endif //LOX_INTERPRETER_H
