//
// Created by 吕孝焱 on 2022/6/26.
//

#include "lox_class.h"

string lox_class::to_string()
{
    return name;
}

lox_object *lox_class::call(interpreter &i, vector<lox_object *> &arguments)
{
    auto* instance = new lox_instance(this);
    return instance;
}

int lox_class::arity()
{
    return 0;
}

lox_class::lox_class(string name) : name(std::move(name))
{

}
