//
// Created by 吕孝焱 on 2022/6/18.
//

#include "lox_callable.h"
#include "interpreter.h"
#include "environment.h"

lox_object *lox_function::call(interpreter& i, vector<lox_object *> &arguments)
{
    auto* new_env = new environment(closure);
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

    delete new_env;
    return new lox_object();
}

int lox_function::arity()
{
    return declaration->params->size();
}

string lox_function::to_string()
{
    return "<fn " + declaration->name->lexeme + ">";
}

lox_function::lox_function(Function_Stmt *declaration, environment *closure, bool is_initializer)
    : declaration(declaration), closure(closure), is_initializer(is_initializer)
{

}

lox_function *lox_function::bind(lox_instance *instance)
{
    auto* new_env = new environment(closure);
    new_env->define("this", instance);
    return new lox_function(this->declaration, new_env, is_initializer);
}
