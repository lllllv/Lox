//
// Created by 吕孝焱 on 2022/6/26.
//

#include "lox_instance.h"
#include "lox_class.h"

string lox_instance::to_string()
{
    return c->name + " instance";
}

lox_object *lox_instance::get(Token *name)
{
    if(fields.find(name->lexeme) != fields.end())
        return fields[name->lexeme];

    auto* method = c->find_method(name->lexeme);
    if(method != nullptr)
        return method->bind(this);

    throw interpreter_runtime_error(name, "Undefined property '" + name->lexeme + "'.");
}

void lox_instance::set(Token *name, lox_object *value)
{
    fields[name->lexeme] = value;
}
