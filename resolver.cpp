//
// Created by 吕孝焱 on 2022/6/25.
//

#include "resolver.h"

extern bool had_error;

void resolver::Visit_Block_Stmt(Block_Stmt* stmt)
{
    begin_scope();
    resolve(stmt->stmts);
    end_scope();
}

void resolver::resolve(vector<Stmt *>* stmts)
{
    for(auto* stmt : *stmts)
        resolve(stmt);
}

void resolver::resolve(Stmt *stmt)
{
    stmt->accept(this);
}

void resolver::resolve(Expr *expr)
{
    expr->accept(this);
}

void resolver::begin_scope()
{
    auto* tmp = new unordered_map<string, bool>();
    scopes.push_back(tmp);
}

void resolver::end_scope()
{
    scopes.pop_back();
}

void resolver::Visit_Var_Stmt(Var_Stmt* stmt)
{
    declare(stmt->name);
    if(stmt->initializer != nullptr)
        resolve(stmt->initializer);
    define(stmt->name);
}

void resolver::declare(Token *name)
{
    if(!scopes.empty() &&
        (*scopes.back()).find(name->lexeme) != (*scopes.back()).end())
    {
        error(*name, "Already a variable with this name in this scope.");
    }

    if(!scopes.empty())
        (*scopes.back())[name->lexeme] = false;
}

void resolver::define(Token *name)
{
    if(!scopes.empty())
        (*scopes.back())[name->lexeme] = true;
}

void resolver::Visit_Variable_Expr(Variable_Expr * expr)
{
    if(!scopes.empty() &&
        scopes.back()->find(expr->name->lexeme) != scopes.back()->end() &&
        !(*scopes.back())[expr->name->lexeme])
        resolver::error(*expr->name,
                  "Can't read local variable in its own initializer.");
    resolve_local(expr, expr->name);
}

void resolver::report(int line, const string &where, const string &msg)
{
    cout <<  "[line " + to_string(line) + "] Error" + where + ": " + msg;
}

void resolver::error(const Token &t, const string &msg)
{
    had_error = true;
    if(t.type == ENDOFFILE)
        report(t.line, " at end.", msg);
    else
        report(t.line, " at '" + t.lexeme + "'", msg);
}

void resolver::resolve_local(Expr *expr, Token *name)
{
    for(int i = scopes.size() - 1; i >= 0; i--)
    {
        if(scopes[i]->find(name->lexeme) != scopes[i]->end())
        {
            inter->resolve(expr, scopes.size() - 1 - i);
            return;
        }
    }
}

void resolver::Visit_Assignment_Expr(Assignment_Expr * expr)
{
    resolve(expr->expr);
    resolve_local(expr, expr->name);
}

void resolver::Visit_Function_Stmt(Function_Stmt * stmt)
{
    declare(stmt->name);
    define(stmt->name);

    resolve_function(stmt, FUNCTION);
}

void resolver::resolve_function(Function_Stmt *function, function_type type)
{
    function_type enclosing_function = current_function;
    current_function = type;
    begin_scope();
    for(auto* param : *function->params)
    {
        declare(param);
        define(param);
    }

    resolve(function->body);
    end_scope();
    current_function = enclosing_function;
}

void resolver::Visit_Expression_Stmt(Expression_Stmt * stmt)
{
    resolve(stmt->expr);
}

void resolver::Visit_If_Stmt(If_Stmt * stmt)
{
    resolve(stmt->condition);
    resolve(stmt->then_branch);
    if(stmt->else_branch != nullptr)
        resolve(stmt->else_branch);
}

void resolver::Visit_Print_Stmt(Print_Stmt * stmt)
{
    resolve(stmt->expr);
}

void resolver::Visit_Return_Stmt(Return_Stmt *stmt)
{
    if(current_function != FUNCTION)
        error(*stmt->keyword, "Can't return from top-level code.");
    else if(stmt->value != nullptr)
        resolve(stmt->value);
}

void resolver::Visit_While_Stmt(While_Stmt * stmt)
{
    resolve(stmt->condition);
    resolve(stmt->body);
}

void resolver::Visit_Binary_Expr(Binary_Expr * expr)
{
    resolve(expr->lhs);
    resolve(expr->rhs);
}

void resolver::Visit_Call_Expr(Call_Expr * expr)
{
    resolve(expr->callee);
    for(auto* argument : *expr->arguments)
        resolve(argument);
}

void resolver::Visit_Grouping_Expr(Grouping_Expr * expr)
{
    resolve(expr->exp);
}

void resolver::Visit_Literal_Expr(Literal_Expr *)
{

}

void resolver::Visit_Logical_Expr(Logical_Expr * expr)
{
    resolve(expr->left);
    resolve(expr->right);
}

void resolver::Visit_Unary_Expr(Unary_Expr * expr)
{
    resolve(expr->operand);
}

void resolver::Visit_Class_Stmt(Class_Stmt * stmt)
{
    declare(stmt->name);
    define(stmt->name);
}

void resolver::Visit_Get_Expr(Get_Expr * expr)
{
    resolve(expr->object);
}

void resolver::Visit_Set_Expr(Set_Expr * expr)
{
    resolve(expr->value);
    resolve(expr->object);
}














