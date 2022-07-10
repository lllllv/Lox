#include "lox_class.h"

#include <utility>

string lox_class::to_string()
{
    return name;
}

shared_ptr<lox_object> lox_class::call(interpreter &i, vector<shared_ptr<lox_object>> &arguments)
{
    auto instance = make_shared<lox_instance>(static_pointer_cast<lox_class>(shared_from_this()));
    auto initializer = find_method("init");
    if(initializer != nullptr)
        initializer->bind(instance)->call(i, arguments);

    return instance;
}

int lox_class::arity()
{
    auto initializer = find_method("init");
    if(initializer == nullptr)
        return 0;
    else
        return initializer->arity();
}

lox_class::lox_class(string name, shared_ptr<lox_class> super_class, shared_ptr<unordered_map<string, shared_ptr<lox_function>>> methods) : name(std::move(name)), super_class(std::move(super_class)), methods(std::move(methods))
{

}

shared_ptr<lox_function> lox_class::find_method(const string &str) const
{
    if(methods->find(str) != methods->end())
        return (*methods)[str];

    if(super_class != nullptr)
        return super_class->find_method(str);

    return nullptr;
}
