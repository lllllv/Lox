#include "resolver.h"

extern bool had_error;

void resolver::Visit_Block_Stmt(shared_ptr<Block_Stmt> stmt)
{
    begin_scope();
    resolve(*stmt->stmts);
    end_scope();
}

void resolver::resolve(vector<shared_ptr<Stmt>>& stmts)
{
    for(const auto& stmt : stmts)
        resolve(stmt);
}

void resolver::resolve(const shared_ptr<Stmt>& stmt)
{
    stmt->accept(this);
}

void resolver::resolve(const shared_ptr<Expr>& expr)
{
    expr->accept(this);
}

void resolver::begin_scope()
{
    scopes.emplace_back();
}

void resolver::end_scope()
{
    scopes.pop_back();
}

void resolver::Visit_Var_Stmt(shared_ptr<Var_Stmt> stmt)
{
    declare(stmt->name);
    if(stmt->initializer != nullptr)
        resolve(stmt->initializer);
    define(stmt->name);
}

void resolver::declare(const shared_ptr<Token>& name)
{
    if(!scopes.empty() &&
        scopes.back().find(name->lexeme) != scopes.back().end())
    {
        error(*name, "Already a variable with this name in this scope.");
    }

    if(!scopes.empty())
        scopes.back()[name->lexeme] = false;
}

void resolver::define(const shared_ptr<Token>& name)
{
    if(!scopes.empty())
        scopes.back()[name->lexeme] = true;
}

void resolver::Visit_Variable_Expr(shared_ptr<Variable_Expr> expr)
{
    if(!scopes.empty() &&
        scopes.back().find(expr->name->lexeme) != scopes.back().end() &&
        !scopes.back()[expr->name->lexeme])
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

void resolver::resolve_local(const shared_ptr<Expr>& expr, const shared_ptr<Token>& name)
{
    for(int i = scopes.size() - 1; i >= 0; i--)
    {
        if(scopes[i].find(name->lexeme) != scopes[i].end())
        {
            inter.resolve(expr, scopes.size() - 1 - i);
            return;
        }
    }
}

void resolver::Visit_Assignment_Expr(shared_ptr<Assignment_Expr> expr)
{
    resolve(expr->expr);
    resolve_local(expr, expr->name);
}

void resolver::Visit_Function_Stmt(shared_ptr<Function_Stmt> stmt)
{
    declare(stmt->name);
    define(stmt->name);

    resolve_function(stmt, FUNCTION);
}

void resolver::resolve_function(const shared_ptr<Function_Stmt>& function, function_type type)
{
    function_type enclosing_function = current_function;
    current_function = type;
    begin_scope();
    for(const auto& param : *function->params)
    {
        declare(param);
        define(param);
    }

    resolve(*function->body);
    end_scope();
    current_function = enclosing_function;
}

void resolver::Visit_Expression_Stmt(shared_ptr<Expression_Stmt> stmt)
{
    resolve(stmt->expr);
}

void resolver::Visit_If_Stmt(shared_ptr<If_Stmt> stmt)
{
    resolve(stmt->condition);
    resolve(stmt->then_branch);
    if(stmt->else_branch != nullptr)
        resolve(stmt->else_branch);
}

void resolver::Visit_Print_Stmt(shared_ptr<Print_Stmt> stmt)
{
    resolve(stmt->expr);
}

void resolver::Visit_Return_Stmt(shared_ptr<Return_Stmt> stmt)
{
    if(current_function == NONE_FUNCTION)
        error(*stmt->keyword, "Can't return from top-level code.");
    else if(stmt->value != nullptr)
    {
        if(current_function == INITIALIZER)
            error(*stmt->keyword, "Can't return a value from an initializer.");
        else
            resolve(stmt->value);
    }

}

void resolver::Visit_While_Stmt(shared_ptr<While_Stmt> stmt)
{
    resolve(stmt->condition);
    resolve(stmt->body);
}

void resolver::Visit_Binary_Expr(shared_ptr<Binary_Expr> expr)
{
    resolve(expr->lhs);
    resolve(expr->rhs);
}

void resolver::Visit_Call_Expr(shared_ptr<Call_Expr> expr)
{
    resolve(expr->callee);
    for(const auto& argument : *expr->arguments)
        resolve(argument);
}

void resolver::Visit_Grouping_Expr(shared_ptr<Grouping_Expr> expr)
{
    resolve(expr->exp);
}

void resolver::Visit_Literal_Expr(shared_ptr<Literal_Expr>)
{

}

void resolver::Visit_Logical_Expr(shared_ptr<Logical_Expr> expr)
{
    resolve(expr->left);
    resolve(expr->right);
}

void resolver::Visit_Unary_Expr(shared_ptr<Unary_Expr> expr)
{
    resolve(expr->operand);
}

void resolver::Visit_Class_Stmt(shared_ptr<Class_Stmt> stmt)
{
    class_type enclosing_class = current_class;
    current_class = CLASS_TYPE;
    declare(stmt->name);
    define(stmt->name);

    if(stmt->super_class != nullptr &&
        stmt->super_class->name->lexeme == stmt->name->lexeme)
        error(*stmt->super_class->name, "A class can't inherit from itself.");

    if(stmt->super_class != nullptr)
    {
        current_class = SUBCLASS_TYPE;
        resolve(stmt->super_class);
    }


    if(stmt->super_class != nullptr)
    {
        begin_scope();
        scopes.back()["super"] = true;
    }


    begin_scope();
    scopes.back()["this"] = true;

    for(const auto& method : *stmt->methods)
        resolve_function(method, METHOD);

    end_scope();

    if(stmt->super_class != nullptr)
        end_scope();

    current_class = enclosing_class;
}

void resolver::Visit_Get_Expr(shared_ptr<Get_Expr> expr)
{
    resolve(expr->object);
}

void resolver::Visit_Set_Expr(shared_ptr<Set_Expr> expr)
{
    resolve(expr->value);
    resolve(expr->object);
}

void resolver::Visit_This_Expr(shared_ptr<This_Expr> expr)
{
    if(current_class == NONE_CLASS_TYPE)
        error(*expr->keyword, "Can't use 'this' outside of a class.");
    else
        resolve_local(expr, expr->keyword);
}

void resolver::Visit_Super_Expr(shared_ptr<Super_Expr> expr)
{
    if(current_class == NONE_CLASS_TYPE)
        error(*expr->keyword, "Can't use 'super' outside of a class.");
    else if(current_class != SUBCLASS_TYPE)
        error(*expr->keyword, "Can't use 'super' in a class with no superclass.");
    resolve_local(expr, expr->keyword);
}

resolver::resolver(interpreter& i) : inter(i), current_function(FUNCTION), current_class(NONE_CLASS_TYPE)
{

}














