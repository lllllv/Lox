#include "lox_instance.h"

#include <utility>
#include "lox_class.h"

string lox_instance::to_string()
{
    return c->name + " instance";
}

lox_instance::lox_instance(const shared_ptr<lox_class>& c) : c(c)
{

}

shared_ptr<lox_object> lox_instance::get(const shared_ptr<Token>& name)
{
    if(fields.find(name->lexeme) != fields.end())
        return fields[name->lexeme];

    auto method = c->find_method(name->lexeme);
    if(method != nullptr)
        return method->bind(static_pointer_cast<lox_instance>(shared_from_this()));

    throw interpreter_runtime_error(name, "Undefined property '" + name->lexeme + "'.");
}

void lox_instance::set(const shared_ptr<Token>& name, shared_ptr<lox_object> value)
{
    fields[name->lexeme] = move(value);
}
