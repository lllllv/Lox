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

lox_object environment::get(const Token &name)
{
    if(values.find(name.lexeme) != values.end())
        return {*values[name.lexeme]};
    if(enclosing != nullptr)
        return enclosing->get(name);

    throw interpreter_runtime_error(new Token(name),  "Undefined variable '" + name.lexeme + "'.");
}

void environment::assign(const Token &name, const lox_object &l)
{
    if(values.find(name.lexeme) != values.end())
    {
        delete values[name.lexeme];
        values[name.lexeme] = new lox_object(l);
    }
    else if(enclosing != nullptr)
        enclosing->assign(name, l);
    else
        throw interpreter_runtime_error(new Token(name),  "Undefined variable '" + name.lexeme + "'.");
}

environment::environment()
{
    enclosing = nullptr;
}

environment::environment(environment *enclosing) : enclosing(enclosing)
{

}

