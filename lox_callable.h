#ifndef LOX_LOX_CALLABLE_H
#define LOX_LOX_CALLABLE_H
#include "AST.h"
#include "lox_object.h"
#include "lox_instance.h"

#include "interpreter_exceptions.h"


class interpreter;
class environment;

class lox_callable : public lox_object/*, public enable_shared_from_this<lox_callable> */{
public:
    virtual int arity() = 0;
    virtual shared_ptr<lox_object> call(interpreter& i, vector<shared_ptr<lox_object>>& arguments) = 0;
    virtual string to_string() = 0;
    ~lox_callable() override = default;
};

class lox_function : public lox_callable {
private:
    shared_ptr<Function_Stmt> declaration;
    shared_ptr<environment> closure;
    bool is_initializer;
public:
    lox_function(shared_ptr<Function_Stmt> declaration, shared_ptr<environment> closure, bool is_initializer);
    shared_ptr<lox_function> bind(const shared_ptr<lox_instance>& instance);
    shared_ptr<lox_object> call(interpreter& i, vector<shared_ptr<lox_object>>& arguments) override;
    int arity() override;
    string to_string() override;
};






#endif //LOX_LOX_CALLABLE_H
