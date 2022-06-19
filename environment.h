//
// Created by 吕孝焱 on 2022/6/10.
//

#ifndef LOX_ENVIRONMENT_H
#define LOX_ENVIRONMENT_H

#include <unordered_map>
#include "token.h"
#include "lox_object.h"
#include "interpreter_exceptions.h"

class environment
{
private:
    unordered_map<string, lox_object*> values;
    environment* enclosing;
public:
    environment();
    explicit environment(environment* enclosing);
    void define(const string& name, lox_object* l);
    void assign(const Token& name, lox_object* l);
    lox_object* get(const Token& name);
};


#endif //LOX_ENVIRONMENT_H
