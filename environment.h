#ifndef LOX_ENVIRONMENT_H
#define LOX_ENVIRONMENT_H

#include <unordered_map>
#include "token.h"
#include "lox_object.h"
#include "lox_callable.h"
#include "interpreter_exceptions.h"

using namespace std;

class environment : public enable_shared_from_this<environment>
{
private:
    unordered_map<string, shared_ptr<lox_object>> values;

public:
    shared_ptr<environment> enclosing;

    environment();
    explicit environment(shared_ptr<environment> enclosing);
    void define(const string& name, shared_ptr<lox_object> l);
    void assign(const Token& name, const shared_ptr<lox_object>& l);
    void assign_at(int dist, const Token& name, const shared_ptr<lox_object>& l);
    shared_ptr<lox_object> get(const Token& name);
    shared_ptr<lox_object> get_at(int dist, const shared_ptr<Token>& name);
    shared_ptr<lox_object> get(const string& name);
    shared_ptr<lox_object> get_at(int dist, const string& name);
    shared_ptr<environment> ancestor(int dist);
};

#endif //LOX_ENVIRONMENT_H
