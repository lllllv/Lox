//
// Created by 吕孝焱 on 2022/6/25.
//

#ifndef LOX_RESOLVER_H
#define LOX_RESOLVER_H
#include <vector>
#include <unordered_map>
#include <string>
#include "visitor.h"
#include "interpreter.h"

class resolver : public Visitor
{
private:
    enum function_type {
        NONE_FUNCTION,
        FUNCTION,
        METHOD,
        INITIALIZER
    };

    enum class_type {
        NONE_CLASS,
        CLASS
    };

    // Works kind like 'flag'. When entering corresponding scope, set the 'flag' to
    // right value and when exiting the scope, restore the previous state.
    // In 'resolve_function' and  'Visit_Class_Stmt'.
    function_type current_function;
    class_type current_class;


    interpreter* inter;
    vector<unordered_map<string, bool>*> scopes;

    void begin_scope();
    void end_scope();
    void declare(Token* name);
    void define(Token* name);
public:
    explicit resolver(interpreter* i) : inter(i), current_function(FUNCTION), current_class(NONE_CLASS){};
    void resolve(vector<Stmt*>* stmts);
    void resolve(Stmt* stmt);
    void resolve(Expr* expr);
    void resolve_local(Expr* expr, Token* name);
    void resolve_function(Function_Stmt* function, function_type type);



    void Visit_Block_Stmt(Block_Stmt*) override;
    void Visit_Var_Stmt(Var_Stmt*) override;
    void Visit_Function_Stmt(Function_Stmt*) override;
    void Visit_Expression_Stmt(Expression_Stmt*) override;
    void Visit_If_Stmt(If_Stmt*) override;
    void Visit_Print_Stmt(Print_Stmt*) override;
    void Visit_Return_Stmt(Return_Stmt*) override;
    void Visit_While_Stmt(While_Stmt*) override;
    void Visit_Class_Stmt(Class_Stmt*) override;


    void Visit_Variable_Expr(Variable_Expr*) override;
    void Visit_Assignment_Expr(Assignment_Expr*) override;
    void Visit_Binary_Expr(Binary_Expr*) override;
    void Visit_Call_Expr(Call_Expr*) override;
    void Visit_Grouping_Expr(Grouping_Expr*) override;
    void Visit_Literal_Expr(Literal_Expr*) override;
    void Visit_Logical_Expr(Logical_Expr*) override;
    void Visit_Unary_Expr(Unary_Expr*) override;
    void Visit_Get_Expr(Get_Expr*) override;
    void Visit_Set_Expr(Set_Expr*) override;
    void Visit_This_Expr(This_Expr*) override;

    static void report(int line, const string& where, const string& msg);
    static void error(const Token& t, const string& msg);
};


#endif //LOX_RESOLVER_H
