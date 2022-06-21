//
// Created by 吕孝焱 on 2022/6/10.
//

#include "environment.h"

void environment::define(const string &name, lox_object* l)
{
    if(values.find(name) != values.end())
        delete values[name];

    values[name] = l;
}

lox_object* environment::get(const Token &name)
{
    if(values.find(name.lexeme) != values.end())
    {
        if(auto* callee = dynamic_cast<lox_callable*>(values[name.lexeme]))
        {
            return callee;
        }
        else
            return new lox_object(*values[name.lexeme]);
    }

    if(enclosing != nullptr)
        return enclosing->get(name);

    throw interpreter_runtime_error(new Token(name),  "Undefined variable '" + name.lexeme + "'.");
}

void environment::assign(const Token &name, lox_object* l)
{
    if(values.find(name.lexeme) != values.end())
    {
        delete values[name.lexeme];
        values[name.lexeme] = l;
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

