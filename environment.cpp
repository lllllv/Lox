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

