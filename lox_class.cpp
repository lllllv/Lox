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
    lox_function* initializer = find_method("init");
    if(initializer != nullptr)
        initializer->bind(instance)->call(i, arguments);

    return instance;
}

int lox_class::arity()
{
    lox_function* initializer = find_method("init");
    if(initializer == nullptr)
        return 0;
    else
        return initializer->arity();
}

lox_class::lox_class(string name,lox_class* super_class, unordered_map<string, lox_function*>* methods) : name(std::move(name)), super_class(super_class), methods(methods)
{

}

lox_function *lox_class::find_method(const string &str) const
{
    if(methods->find(str) != methods->end())
        return (*methods)[str];

    if(super_class != nullptr)
        return super_class->find_method(str);

    return nullptr;
}
