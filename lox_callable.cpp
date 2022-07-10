#include "lox_callable.h"

#include <utility>
#include "interpreter.h"
#include "environment.h"

shared_ptr<lox_object> lox_function::call(interpreter& i, vector<shared_ptr<lox_object>> &arguments)
{
    auto new_env = make_shared<environment>(closure);
    for(int j = 0; j < declaration->params->size(); j++)
        new_env->define((*declaration->params)[j]->lexeme, arguments[j]);

    try {
        i._execute_Block(declaration->body, new_env);
    } catch (return_result_exception& r)
    {
        if(is_initializer)
            return closure->get_at(0, "this");
        return r.value;
    }

    return make_shared<lox_object>();
}

int lox_function::arity()
{
    return declaration->params->size();
}

string lox_function::to_string()
{
    return "<fn " + declaration->name->lexeme + ">";
}

lox_function::lox_function(shared_ptr<Function_Stmt> declaration, shared_ptr<environment> closure, bool is_initializer)
    : declaration(std::move(declaration)), closure(std::move(closure)), is_initializer(is_initializer)
{

}

shared_ptr<lox_function> lox_function::bind(const shared_ptr<lox_instance>& instance)
{
    auto new_env = make_shared<environment>(closure);
    new_env->define("this", instance);
    return make_shared<lox_function>(this->declaration, new_env, is_initializer);
}
