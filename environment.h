//
// Created by 吕孝焱 on 2022/6/10.
//

#ifndef LOX_ENVIRONMENT_H
#define LOX_ENVIRONMENT_H

#include <unordered_map>
#include "token.h"
#include "lox_object.h"
#include "lox_callable.h"
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
    void assign_at(int dist, const Token& name, lox_object* l);
    lox_object* get(const Token& name);
    lox_object* get_at(int dist, Token* name);
    lox_object* get(const string& name);
    lox_object* get_at(int dist, const string& name);
    environment* ancestor(int dist);
};

#endif //LOX_ENVIRONMENT_H
