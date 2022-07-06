//
// Created by lvxia on 2022/6/7.
//

#include "interpreter.h"


void interpreter::Visit_Literal_Expr(Literal_Expr *l) {

    switch(l->t->type)
    {
        case NUMBER:
            this->im_results.push(new lox_object(l->t->it.val));
            break;
        case STRING:
            this->im_results.push(new lox_object(l->t->it.str));
            break;
        case NIL:
            this->im_results.push(new lox_object());
            break;
        case TRUE:
            this->im_results.push(new lox_object(true));
            break;
        case FALSE:
            this->im_results.push(new lox_object(false));
            break;
        default:
            cout << "Unexpected Literal value!" << endl;
            exit(255);
    }
}

void interpreter::Visit_Grouping_Expr(Grouping_Expr *g) {
    _evaluate(g->exp);
}

void interpreter::_evaluate(Expr *exp) {
    exp->accept(this);
}

void interpreter::Visit_Unary_Expr(Unary_Expr *u) {
    _evaluate(u->operand);

    switch(u->op->type)
    {
        case MINUS:
        {
            lox_object* tmp = im_results.top();
            im_results.pop();
            tmp->num = -tmp->num;
            im_results.push(tmp);
            break;
        }
        case BANG:
        {
            lox_object* tmp = im_results.top();
            im_results.pop();
            im_results.push(new lox_object(is_truthy(*tmp)));
            break;
        }
        default:
            cout << "Unexpected Unary operator type!" << endl;
            exit(255);
    }
}

bool interpreter::is_truthy(const lox_object & l) {
    if(l.type == NIL)
        return false;
    if(l.type == TRUE)
        return true;
    if(l.type == FALSE)
        return false;
    return true;
}

bool interpreter::is_equal(const lox_object &l1, const lox_object &l2) {
    if(l1.type == NIL && l2.type == NIL)
        return true;
    else if(l1.type == NIL || l2.type == NIL)
        return false;

    if(l1.type != l2.type)
        return false;

    if(l1.type == NUMBER)
        return l1.num == l2.num;
    else if(l1.type == STRING)
        return l1.str == l2.str;
    else
        return l1.boolean == l2.boolean;
}

void interpreter::Visit_Binary_Expr(Binary_Expr *b) {
    _evaluate(b->lhs);
    _evaluate(b->rhs);

    lox_object* rhs = im_results.top();
    im_results.pop();
    lox_object* lhs = im_results.top();
    im_results.pop();

    switch(b->op->type)
    {
        case PLUS:
            if(lhs->type == NUMBER && rhs->type == NUMBER)
                im_results.push(new lox_object((double)(lhs->num + rhs->num)));
            if(lhs->type == STRING && rhs->type == STRING)
                im_results.push(new lox_object(lhs->str + rhs->str));
            break;
        case MINUS:
            im_results.push(new lox_object((double)(lhs->num - rhs->num)));
            break;
        case STAR:
            im_results.push(new lox_object((double)(lhs->num * rhs->num)));
            break;
        case SLASH:
            im_results.push(new lox_object((double)(lhs->num / rhs->num)));
            break;


        case GREATER:
            im_results.push(new lox_object(lhs->num > rhs->num));
            break;
        case GREATER_EQUAL:
            im_results.push(new lox_object(lhs->num >= rhs->num));
            break;
        case LESS:
            im_results.push(new lox_object(lhs->num < rhs->num));
            break;
        case LESS_EQUAL:
            im_results.push(new lox_object(lhs->num <= rhs->num));
            break;

        case EQUAL_EQUAL:
            im_results.push(new lox_object(is_equal(*lhs, *rhs)));
            break;
        case BANG_EQUAL:
            im_results.push(new lox_object(!is_equal(*lhs, *rhs)));
            break;

    }
}

void interpreter::_print_lox_object(lox_object* l) {
    if(auto* tmp = dynamic_cast<lox_callable*>(l))
        cout << tmp->to_string();
    else
    {
        if(auto* instance = dynamic_cast<lox_instance*>(l))
        {
            cout << instance->to_string();
        }
        else
        {
            switch(l->type)
            {
                case NUMBER:
                    cout << l->num;
                    break;
                case STRING:
                    cout << l->str;
                    break;
                case NIL:
                    cout << "nil";
                    break;
                case TRUE:
                    cout << "true";
                    break;
                case FALSE:
                    cout << "false";
                    break;

                default:
                    cout << "Unknown result!";
                    break;
            }
        }

    }


}

void interpreter::eval(Expr* expr) {
    _evaluate(expr);
    lox_object* res = im_results.top();
    im_results.pop();
    _print_lox_object(res);
    //delete res;
}

// Expression_Stmt like :  "a = 2;"  no need to pop???
// Expression_Stmt like : "1+1;" need to pop; ?????
void interpreter::Visit_Expression_Stmt(Expression_Stmt * expression) {
    _evaluate(expression->expr);
    im_results.pop();
    //im_results.top().print();
}

void interpreter::Visit_Print_Stmt(Print_Stmt *p) {
    _evaluate(p->expr);
    lox_object* tmp = im_results.top();
    im_results.pop();
    _print_lox_object(tmp);
    cout << endl;
}

void interpreter::interpret(const vector<Stmt *>& stmts)
{
    try {
        for(auto* stmt : stmts)
            _execute(stmt);
    } catch(interpreter_runtime_error& r)
    {
        cout << r.what() << endl;
        cout << "Terminated." << endl;
    }


}

void interpreter::_execute(Stmt *stmt)
{
    stmt->accept(this);
}

void interpreter::Visit_Var_Stmt(Var_Stmt *v)
{
    auto* val = new lox_object();
    if(v->initializer != nullptr)
    {
        _evaluate(v->initializer);
        val = im_results.top();
        im_results.pop();
    }
    //val.print();
    env->define(v->name->lexeme, val);
}

void interpreter::Visit_Variable_Expr(Variable_Expr *expr)
{
    //im_results.push(env->get(*expr->name));
    im_results.push(lookup_variable(expr->name, expr));
}

//  evaluate an Assignment_Expr produces
//  the evaluation result of the corresponding expression
void interpreter::Visit_Assignment_Expr(Assignment_Expr *expr)
{
    _evaluate(expr->expr);
    lox_object* l = im_results.top();
    // env->assign(*expr->name, l);

    if(locals.find(expr) != locals.end())
    {
        int dist = locals[expr];
        env->assign_at(dist, *expr->name, l);
    }
    else
        globals->assign(*expr->name, l);


}

void interpreter::Visit_Block_Stmt(Block_Stmt * stmt)
{
    auto new_env = new environment(this->env);
    _execute_Block(stmt->stmts, new_env);
    //delete new_env;
}

void interpreter::_execute_Block(vector<Stmt*>* stmts, environment* new_env)
{
    environment* previous = this->env;
    try {
        this->env = new_env;
        for(auto* stmt : *stmts)
            _execute(stmt);
    } catch(interpreter_runtime_error& e) {
        cout << e.what() << endl;
    }
    catch (return_control_flow_exception& r)
    {
        this->env = previous;
        throw return_result_exception("using exception to return a value", r.value);
    }

    // 保证无论是block的return语句导致返回还是block执行完毕返回，原来的环境都会被恢复
    this->env = previous;


}

interpreter::interpreter()
{
    this->globals = new environment();
    this->globals->define("clock", new class clock());
    this->env = globals;
}

void interpreter::Visit_If_Stmt(If_Stmt * if_stmt)
{
    /*_evaluate(if_stmt->condition);
    lox_object tmp = im_results.top();
    im_results.pop();*/

    if(_evaluate_cond(if_stmt->condition))
        _execute(if_stmt->then_branch);
    else if(if_stmt->else_branch != nullptr)
        _execute(if_stmt->else_branch);
}

void interpreter::Visit_Logical_Expr(Logical_Expr * expr)
{
    _evaluate(expr->left);
    lox_object* tmp_l = im_results.top();
    im_results.pop();

    if(expr->op->type == OR)
    {
        if(is_truthy(*tmp_l))
        {
            im_results.push(tmp_l);
            return;
        }

    } else
    {
        if(!is_truthy(*tmp_l))
        {
            im_results.push(tmp_l);
            return;
        }
    }

    _evaluate(expr->right);
}

void interpreter::Visit_While_Stmt(While_Stmt *stmt)
{
    while(_evaluate_cond(stmt->condition))
        _execute(stmt->body);
}

bool interpreter::_evaluate_cond(Expr *expr)
{
    _evaluate(expr);
    lox_object* tmp = im_results.top();
    im_results.pop();
    return is_truthy(*tmp);
}

void interpreter::Visit_Call_Expr(Call_Expr * expr)
{
    _evaluate(expr->callee);
    lox_object* callee = im_results.top();
    im_results.pop();
    auto* arguments = new vector<lox_object*>();
    for(auto* argument : *expr->arguments)
    {
        _evaluate(argument);
        arguments->push_back(im_results.top());
        im_results.pop();
    }

    if(auto* function = dynamic_cast<lox_callable*>(callee))
    {
        if(function->arity() == arguments->size())
            im_results.push(function->call(*this, *arguments));
        else
            throw  interpreter_runtime_error(expr->paren, "Expected " +
                                               to_string(function->arity()) + " arguments but got " +
                                               to_string(arguments->size()) + ".");
    }
    else
        throw interpreter_runtime_error(expr->paren,
                               "Can only call functions and classes.");
}

void interpreter::Visit_Function_Stmt(Function_Stmt *stmt)
{
    auto* fun = new lox_function(stmt, env, false);
    env->define(stmt->name->lexeme, fun);
}

void interpreter::Visit_Return_Stmt(Return_Stmt* stmt)
{
    lox_object* value;
    if(stmt->value != nullptr)
    {
        _evaluate(stmt->value);
        value = im_results.top();
        im_results.pop();
    }
    else
        value = new lox_object();
    throw return_control_flow_exception("using exception to clear call stack and return a value", value);
}

void interpreter::resolve(Expr *expr, int depth)
{
    locals[expr] = depth;
}

lox_object *interpreter::lookup_variable(Token *name, Expr *expr)
{
    if(locals.find(expr) != locals.end())
    {
        int dist = locals[expr];
        return env->get_at(dist, name);
    }
    else
        return globals->get(*name);
}

void interpreter::Visit_Class_Stmt(Class_Stmt * stmt)
{
    lox_object* tmp;
    lox_class* super_class = nullptr;

    if(stmt->super_class != nullptr)
    {
        _evaluate(stmt->super_class);
        tmp = im_results.top();
        im_results.pop();

        super_class = dynamic_cast<lox_class*>(tmp);
        if(super_class == nullptr)
            throw interpreter_runtime_error(stmt->super_class->name, "Superclass must be a class.");
    }

    env->define(stmt->name->lexeme, nullptr);

    if(stmt->super_class != nullptr)
    {
        env = new environment(env);
        env->define("super", super_class);
    }

    auto* methods = new unordered_map<string, lox_function*>();
    for(auto* method : *stmt->methods)
    {
        auto* function = new lox_function(method, this->env, method->name->lexeme == "init");
        (*methods)[method->name->lexeme] = function;
    }
    auto* new_lox_class = new lox_class(stmt->name->lexeme, super_class, methods);

    if(stmt->super_class != nullptr)
        env = env->enclosing;

    env->assign(*stmt->name, new_lox_class);
}

void interpreter::Visit_Get_Expr(Get_Expr* expr)
{
    _evaluate(expr->object);
    auto* tmp = im_results.top();
    im_results.pop();
    if(auto* instance = dynamic_cast<lox_instance*>(tmp))
        im_results.push(instance->get(expr->name));
    else
        throw  interpreter_runtime_error(expr->name, "Only instances have properties.");
}

void interpreter::Visit_Set_Expr(Set_Expr * expr)
{
    _evaluate(expr->object);
    auto* obj = im_results.top();
    im_results.pop();

    if(auto* object = dynamic_cast<lox_instance*>(obj))
    {
        _evaluate(expr->value);
        auto* value = im_results.top();

        object->set(expr->name, value);
    }
    else
        throw interpreter_runtime_error(expr->name, "Only instances have fields.");
}

void interpreter::Visit_This_Expr(This_Expr * expr)
{
    im_results.push(lookup_variable(expr->keyword, expr));
}

void interpreter::Visit_Super_Expr(Super_Expr* expr)
{
    int dist = locals[expr];
    lox_class* super_class = dynamic_cast<lox_class*>(env->get_at(dist, "super"));
    lox_instance* instance = dynamic_cast<lox_instance*>(env->get_at(dist - 1, "this"));
    auto* method = super_class->find_method(expr->method->lexeme);
    if(method == nullptr)
        throw interpreter_runtime_error(expr->method, "Undefined property '" + expr->method->lexeme + "'.");
    im_results.push(method->bind(instance));
}
