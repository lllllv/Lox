//
// Created by 吕孝焱 on 2022/6/18.
//

#ifndef LOX_LOX_CALLABLE_H
#define LOX_LOX_CALLABLE_H
#include "AST.h"
#include "lox_object.h"
#include "lox_instance.h"

#include "interpreter_exceptions.h"


class interpreter;
class environment;

class lox_callable : public lox_object {
public:
    virtual int arity() = 0;
    virtual lox_object* call(interpreter& i, vector<lox_object*>& arguments) = 0;
    virtual string to_string() = 0;
    ~lox_callable() override = default;
};

class lox_function : public lox_callable {
private:
    Function_Stmt* declaration;
    environment* closure;
    bool is_initializer;
public:
    lox_function(Function_Stmt* declaration, environment* closure, bool is_initializer);
    lox_function* bind(lox_instance* instance);
    lox_object* call(interpreter& i, vector<lox_object*>& arguments) override;
    int arity() override;
    string to_string() override;
};






#endif //LOX_LOX_CALLABLE_H
