#include "environment.h"

#include <utility>
#include "lox_instance.h"

void environment::define(const string &name, shared_ptr<lox_object> l)
{
    values[name] = move(l);
}

shared_ptr<lox_object> environment::get(const Token &name)
{
    if(values.find(name.lexeme) != values.end())
    {
        if(auto callee = dynamic_pointer_cast<lox_callable>(values[name.lexeme]))
            return callee;
        else if(auto instance = dynamic_pointer_cast<lox_instance>(values[name.lexeme]))
            return instance;
        else
            return make_shared<lox_object>(*values[name.lexeme]);
    }

    if(enclosing != nullptr)
        return enclosing->get(name);

    throw interpreter_runtime_error(make_shared<Token>(name),  "Undefined variable '" + name.lexeme + "'.");
}

void environment::assign(const Token &name, const shared_ptr<lox_object>& l)
{
    if(values.find(name.lexeme) != values.end())
    {
        values[name.lexeme] = l;
    }
    else if(enclosing != nullptr)
        enclosing->assign(name, l);
    else
        throw interpreter_runtime_error(make_shared<Token>(name),  "Undefined variable '" + name.lexeme + "'.");
}

environment::environment()
{
    enclosing = nullptr;
}

environment::environment(shared_ptr<environment> enclosing) : enclosing(move(enclosing))
{

}

shared_ptr<lox_object> environment::get_at(int dist, const shared_ptr<Token>& name)
{
    return ancestor(dist)->get(*name);
}

shared_ptr<environment> environment::ancestor(int dist)
{
    auto env = shared_from_this();
    for(int i = 0; i < dist; i++)
        env = env->enclosing;
    return env;
}

void environment::assign_at(int dist, const Token &name, const shared_ptr<lox_object>& l)
{
    ancestor(dist)->assign(name, l);
}

shared_ptr<lox_object> environment::get_at(int dist, const string &name)
{
    return ancestor(dist)->get(name);
}

shared_ptr<lox_object> environment::get(const string &name)
{
    auto t = make_shared<Token>(STRING, name, iteral{}, -1);
    return get(*t);
}

