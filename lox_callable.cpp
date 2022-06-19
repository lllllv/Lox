//
// Created by 吕孝焱 on 2022/6/18.
//

#include "lox_callable.h"
#include "interpreter.h"

lox_object *lox_function::call(interpreter& i, vector<lox_object *> &arguments)
{
    auto* new_env = new environment(i.globals);
    for(int j = 0; j < declaration->params->size(); j++)
        new_env->define((*declaration->params)[j]->lexeme, arguments[j]);

    i._execute_Block(declaration->body, new_env);
    delete new_env;
    return nullptr;
}

int lox_function::arity()
{
    return declaration->params->size();
}

string lox_function::to_string()
{
    return "<fn " + declaration->name->lexeme + ">";
}
