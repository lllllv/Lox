#include "interpreter.h"

#include <utility>


void interpreter::Visit_Literal_Expr(shared_ptr<Literal_Expr> l) {

    switch(l->t->type)
    {
        case NUMBER:
            this->im_results.push(make_shared<lox_object>(l->t->it.val));
            break;
        case STRING:
            this->im_results.push(make_shared<lox_object>(l->t->it.str));
            break;
        case NIL:
            this->im_results.push(make_shared<lox_object>());
            break;
        case TRUE:
            this->im_results.push(make_shared<lox_object>(true));
            break;
        case FALSE:
            this->im_results.push(make_shared<lox_object>(false));
            break;
        default:
            cout << "Unexpected Literal value!" << endl;
            exit(255);
    }
}

void interpreter::Visit_Grouping_Expr(shared_ptr<Grouping_Expr> g) {
    _evaluate(g->exp);
}

void interpreter::_evaluate(const shared_ptr<Expr>& exp) {
    exp->accept(this);
}

void interpreter::Visit_Unary_Expr(shared_ptr<Unary_Expr> u) {
    _evaluate(u->operand);

    switch(u->op->type)
    {
        case MINUS:
        {
            auto tmp = im_results.top();
            im_results.pop();
            tmp->num = -tmp->num;
            im_results.push(tmp);
            break;
        }
        case BANG:
        {
            auto tmp = im_results.top();
            im_results.pop();
            im_results.push(make_shared<lox_object>(is_truthy(*tmp)));
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

void interpreter::Visit_Binary_Expr(shared_ptr<Binary_Expr> b) {
    _evaluate(b->lhs);
    _evaluate(b->rhs);

    auto rhs = im_results.top();
    im_results.pop();
    auto lhs = im_results.top();
    im_results.pop();

    switch(b->op->type)
    {
        case PLUS:
            if(lhs->type == NUMBER && rhs->type == NUMBER)
                im_results.push(make_shared<lox_object>((double)(lhs->num + rhs->num)));
            if(lhs->type == STRING && rhs->type == STRING)
                im_results.push(make_shared<lox_object>(lhs->str + rhs->str));
            break;
        case MINUS:
            im_results.push(make_shared<lox_object>((double)(lhs->num - rhs->num)));
            break;
        case STAR:
            im_results.push(make_shared<lox_object>((double)(lhs->num * rhs->num)));
            break;
        case SLASH:
            im_results.push(make_shared<lox_object>((double)(lhs->num / rhs->num)));
            break;


        case GREATER:
            im_results.push(make_shared<lox_object>(lhs->num > rhs->num));
            break;
        case GREATER_EQUAL:
            im_results.push(make_shared<lox_object>(lhs->num >= rhs->num));
            break;
        case LESS:
            im_results.push(make_shared<lox_object>(lhs->num < rhs->num));
            break;
        case LESS_EQUAL:
            im_results.push(make_shared<lox_object>(lhs->num <= rhs->num));
            break;

        case EQUAL_EQUAL:
            im_results.push(make_shared<lox_object>(is_equal(*lhs, *rhs)));
            break;
        case BANG_EQUAL:
            im_results.push(make_shared<lox_object>(!is_equal(*lhs, *rhs)));
            break;
        default:
            break;
    }
}

void interpreter::_print_lox_object(const shared_ptr<lox_object>& l) {
    if(auto tmp = dynamic_pointer_cast<lox_callable>(l))
        cout << tmp->to_string();
    else
    {
        if(auto instance = dynamic_pointer_cast<lox_instance>(l))
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

void interpreter::eval(const shared_ptr<Expr>& expr) {
    _evaluate(expr);
    auto res = im_results.top();
    im_results.pop();
    _print_lox_object(res);
}

// Expression_Stmt like :  "a = 2;"  no need to pop???
// Expression_Stmt like : "1+1;" need to pop; ?????
void interpreter::Visit_Expression_Stmt(shared_ptr<Expression_Stmt> expression) {
    _evaluate(expression->expr);
    im_results.pop();
    //im_results.top().print();
}

void interpreter::Visit_Print_Stmt(shared_ptr<Print_Stmt> p) {
    _evaluate(p->expr);
    auto tmp = im_results.top();
    im_results.pop();
    _print_lox_object(tmp);
    cout << endl;
}

void interpreter::interpret(const vector<shared_ptr<Stmt>>& stmts)
{
    try {
        for(const auto& stmt : stmts)
            _execute(stmt);
    } catch(interpreter_runtime_error& r)
    {
        cout << r.what() << endl;
        cout << "Terminated." << endl;
    }
}

void interpreter::_execute(const shared_ptr<Stmt>& stmt)
{
    stmt->accept(this);
}

void interpreter::Visit_Var_Stmt(shared_ptr<Var_Stmt> v)
{
    auto val = make_shared<lox_object>();
    if(v->initializer != nullptr)
    {
        _evaluate(v->initializer);
        val = im_results.top();
        im_results.pop();
    }
    //val.print();
    env->define(v->name->lexeme, val);
}

void interpreter::Visit_Variable_Expr(shared_ptr<Variable_Expr> expr)
{
    //im_results.push(env->get(*expr->name));
    im_results.push(lookup_variable(expr->name, expr));
}

//  evaluate an Assignment_Expr produces
//  the evaluation result of the corresponding expression
void interpreter::Visit_Assignment_Expr(shared_ptr<Assignment_Expr> expr)
{
    _evaluate(expr->expr);
    auto l = im_results.top();
    // env->assign(*expr->name, l);

    if(locals.find(expr) != locals.end())
    {
        int dist = locals[expr];
        env->assign_at(dist, *expr->name, l);
    }
    else
        globals->assign(*expr->name, l);


}

void interpreter::Visit_Block_Stmt(shared_ptr<Block_Stmt> stmt)
{
    auto new_env = make_shared<environment>(this->env);
    _execute_Block(stmt->stmts, new_env);
}

void interpreter::_execute_Block(const shared_ptr<vector<shared_ptr<Stmt>>>& stmts, shared_ptr<environment> new_env)
{
    auto previous = this->env;
    try {
        this->env = move(new_env);
        for(const auto& stmt : *stmts)
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
    this->globals = make_shared<environment>();
    this->globals->define("clock", make_shared<native_clock>());
    this->env = globals;
}

void interpreter::Visit_If_Stmt(shared_ptr<If_Stmt> if_stmt)
{
    /*_evaluate(if_stmt->condition);
    lox_object tmp = im_results.top();
    im_results.pop();*/

    if(_evaluate_cond(if_stmt->condition))
        _execute(if_stmt->then_branch);
    else if(if_stmt->else_branch != nullptr)
        _execute(if_stmt->else_branch);
}

void interpreter::Visit_Logical_Expr(shared_ptr<Logical_Expr> expr)
{
    _evaluate(expr->left);
    auto tmp_l = im_results.top();
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

void interpreter::Visit_While_Stmt(shared_ptr<While_Stmt> stmt)
{
    while(_evaluate_cond(stmt->condition))
        _execute(stmt->body);
}

bool interpreter::_evaluate_cond(const shared_ptr<Expr>& expr)
{
    _evaluate(expr);
    auto tmp = im_results.top();
    im_results.pop();
    return is_truthy(*tmp);
}

void interpreter::Visit_Call_Expr(shared_ptr<Call_Expr> expr)
{
    _evaluate(expr->callee);
    auto callee = im_results.top();
    im_results.pop();
    auto arguments = make_shared<vector<shared_ptr<lox_object>>>();
    for(const auto& argument : *expr->arguments)
    {
        _evaluate(argument);
        arguments->push_back(im_results.top());
        im_results.pop();
    }

    if(auto function = dynamic_pointer_cast<lox_callable>(callee))
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

void interpreter::Visit_Function_Stmt(shared_ptr<Function_Stmt> stmt)
{
    auto fun = make_shared<lox_function>(stmt, env, false);
    env->define(stmt->name->lexeme, fun);
}

void interpreter::Visit_Return_Stmt(shared_ptr<Return_Stmt> stmt)
{
    shared_ptr<lox_object> value;
    if(stmt->value != nullptr)
    {
        _evaluate(stmt->value);
        value = im_results.top();
        im_results.pop();
    }
    else
        value = make_shared<lox_object>();
    throw return_control_flow_exception("using exception to clear call stack and return a value", value);
}

void interpreter::resolve(const shared_ptr<Expr>& expr, int depth)
{
    locals[expr] = depth;
}

shared_ptr<lox_object> interpreter::lookup_variable(const shared_ptr<Token>& name, const shared_ptr<Expr>& expr)
{
    if(locals.find(expr) != locals.end())
    {
        int dist = locals[expr];
        return env->get_at(dist, name);
    }
    else
        return globals->get(*name);
}

void interpreter::Visit_Class_Stmt(shared_ptr<Class_Stmt> stmt)
{
    shared_ptr<lox_object> tmp;
    shared_ptr<lox_class> super_class = nullptr;

    if(stmt->super_class != nullptr)
    {
        _evaluate(stmt->super_class);
        tmp = im_results.top();
        im_results.pop();

        super_class = dynamic_pointer_cast<lox_class>(tmp);
        if(super_class == nullptr)
            throw interpreter_runtime_error(stmt->super_class->name, "Superclass must be a class.");
    }

    env->define(stmt->name->lexeme, nullptr);

    if(stmt->super_class != nullptr)
    {
        env = make_shared<environment>(env);
        env->define("super", super_class);
    }

    auto methods = make_shared<unordered_map<string, shared_ptr<lox_function>>>();
    for(const auto& method : *stmt->methods)
    {
        auto function = make_shared<lox_function>(method, this->env, method->name->lexeme == "init");
        (*methods)[method->name->lexeme] = function;
    }
    auto new_lox_class = make_shared<lox_class>(stmt->name->lexeme, super_class, methods);

    if(stmt->super_class != nullptr)
        env = env->enclosing;

    env->assign(*stmt->name, new_lox_class);
}

void interpreter::Visit_Get_Expr(shared_ptr<Get_Expr> expr)
{
    _evaluate(expr->object);
    auto tmp = im_results.top();
    im_results.pop();
    if(auto instance = dynamic_pointer_cast<lox_instance>(tmp))
        im_results.push(instance->get(expr->name));
    else
        throw  interpreter_runtime_error(expr->name, "Only instances have properties.");
}

void interpreter::Visit_Set_Expr(shared_ptr<Set_Expr> expr)
{
    _evaluate(expr->object);
    auto obj = im_results.top();
    im_results.pop();

    if(auto object = dynamic_pointer_cast<lox_instance>(obj))
    {
        _evaluate(expr->value);
        auto value = im_results.top();

        object->set(expr->name, value);
    }
    else
        throw interpreter_runtime_error(expr->name, "Only instances have fields.");
}

void interpreter::Visit_This_Expr(shared_ptr<This_Expr> expr)
{
    im_results.push(lookup_variable(expr->keyword, expr));
}

void interpreter::Visit_Super_Expr(shared_ptr<Super_Expr> expr)
{
    int dist = locals[expr];
    auto super_class = dynamic_pointer_cast<lox_class>(env->get_at(dist, "super"));
    auto instance = dynamic_pointer_cast<lox_instance>(env->get_at(dist - 1, "this"));
    auto method = super_class->find_method(expr->method->lexeme);
    if(method == nullptr)
        throw interpreter_runtime_error(expr->method, "Undefined property '" + expr->method->lexeme + "'.");
    im_results.push(method->bind(instance));
}
