//
// Created by 吕孝焱 on 2022/6/10.
//

#include "environment.h"

void environment::define(const string &name, const lox_object &l)
{
    if(values.find(name) != values.end())
        delete values[name];

    values[name] = new lox_object(l);
}

lox_object *environment::get(const Token &name)
{
    if(values.find(name.lexeme) != values.end())
        return values[name.lexeme];

    throw interpreter_runtime_error(new Token(name),  "Undefined variable '" + name.lexeme + "'.");
}

